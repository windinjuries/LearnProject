from loguru import logger
import os
import shlex
import sys
import time
import subprocess

import sh
from sh import rsync

from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

ignore_list = ['backend/*']


class BufferedEventHandler(FileSystemEventHandler):

    def __init__(self, *args, ignore, **kwargs):
        super().__init__(*args, **kwargs)

        self.events = []
        self.ignore = ignore or []

    def add_event(self, change_type, what, src_path, dest_path=None):
        event = {
            'change_type': change_type,
            'what': what,
            'src_path': src_path,
            'dest_path': dest_path,
        }

        self.events.append(event)
        logger.info(event)

    def is_ignored(self, src_path) -> bool:
        if src_path.startswith('./'):
            src_path = src_path[2:]

        for item in self.ignore:
            if src_path.startswith(item):
                return True

        return False

    def on_moved(self, event):
        src_path = event.src_path
        if self.is_ignored(src_path):
            return

        super().on_moved(event)

        change_type = 'Moved'
        what = 'directory' if event.is_directory else 'file'
        dest_path = event.dest_path

        self.add_event(change_type, what, src_path, dest_path=dest_path)

    def on_created(self, event):
        src_path = event.src_path
        if self.is_ignored(src_path):
            return

        super().on_created(event)

        change_type = 'Created'
        what = 'directory' if event.is_directory else 'file'

        self.add_event(change_type, what, src_path)

    def on_deleted(self, event):
        src_path = event.src_path
        if self.is_ignored(src_path):
            return

        super().on_deleted(event)

        change_type = 'Deleted'
        what = 'directory' if event.is_directory else 'file'

        self.add_event(change_type, what, src_path)

    def on_modified(self, event):
        src_path = event.src_path
        if self.is_ignored(src_path):
            return

        super().on_modified(event)

        change_type = 'Modified'
        what = 'directory' if event.is_directory else 'file'

        self.add_event(change_type, what, src_path)


def run_command(command: str):
    command_split = shlex.split(command)
    logger.debug(command_split)
    proc_fn = getattr(sh, command_split[0])
    return proc_fn(*command_split[1:], _fg=True)

if __name__ == "__main__":
    


    username = sys.argv[1]
    host = sys.argv[2]
    src_dir = sys.argv[3]
    dest_dir = sys.argv[4]
    exclude_file = sys.argv[5]
    event_handler = BufferedEventHandler(ignore = ignore_list)

    rsync_delete_arg = '--delete'

    observer = Observer()
    observer.schedule(event_handler, src_dir, recursive=True)
    observer.start()
    count = 0

    try:
        while True:
            _count = len(event_handler.events)
            if _count != count:
                event_handler.events = []
                _count = len(event_handler.events)

                try:
                    run_command(f"rsync -av --exclude-from={exclude_file} {rsync_delete_arg} {src_dir} {username}@{host}:{dest_dir}")
                except Exception as exc:
                    logger.warning(f'command failed with error {exc}')
            count = _count
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()
