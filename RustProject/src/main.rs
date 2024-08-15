use libc::sleep;
use nix::fcntl::*;
use std::os::fd::RawFd;
use nix::sys::stat::Mode;

use nix::*;
fn main() {
    let result: Result<i32>;
    let mut fd = 0;
    let num:i32 = 1;
    result = open("/sys/class/leds/green_led/brightness", OFlag::O_RDWR, Mode::S_IRWXO);
    match result {
        Ok(n)  => {
            fd = n;
            println!("fd is {}", fd);
        },
        Err(e) => {
            println!("Error: {}", e); 
            return; 
        }
    }
    let fd_int: nix::libc::c_int;
    unsafe {
        ioctl_write_int_bad(fd, 1);
    }
}



