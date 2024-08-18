#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "flashdb.h"
#define LOG_TAG "main"
#include "elog.h"

int boot_count = 0;
int boot_time = 0;
/* default KV nodes */
static struct fdb_default_kv_node default_kv_table[] = {
        {"username", "armink", 0}, /* string KV */
        {"password", "123456", 0}, /* string KV */
        {"boot_count", &boot_count, sizeof(boot_count)}, /* int type KV */
        {"boot_time", &boot_time, sizeof(boot_time)},    /* int array type KV */
};
/* KVDB object */
static struct fdb_kvdb kvdb = { 0 };
/* TSDB object */
struct fdb_tsdb tsdb = { 0 };
/* counts for simulated timestamp */
static int counts = 0;
static int sec_size = 4096;
static int max_size = 4096 * 8;
static bool flag = true;

int main(int argc, char *argv[])
{
    int res;
    /* close printf buffer */
    setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    /* start EasyLogger */
    elog_start();

    struct fdb_blob blob;
    int boot_count = 0;

    struct fdb_default_kv default_kv;

    default_kv.kvs = default_kv_table;
    default_kv.num = sizeof(default_kv_table) / sizeof(default_kv_table[0]);
    /* set the lock and unlock function if you want */
    /* set the sector and database max size */
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_SEC_SIZE, &sec_size);
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_MAX_SIZE, &max_size);
    /* enable file mode */
    // fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_FILE_MODE, &flag);
    // /* create database directory */
    // mkdir("fdb_kvdb1", 0777);

    res = fdb_kvdb_init(&kvdb, "env", "easyflash", &default_kv, NULL);
    if (res != FDB_NO_ERR)
    {
        return -1;
    }
    fdb_kv_get_blob(&kvdb, "boot_count", fdb_blob_make(&blob, &boot_count, sizeof(boot_count)));
    if (blob.saved.len > 0)
    {
        log_i("get the 'boot_count' value is %d\n", boot_count);
        boot_count +=1;
    }
    else
    {
        log_i("get the 'boot_count' failed\n");
    }

    /* change the "boot_count" KV's value */
    fdb_kv_set_blob(&kvdb, "boot_count", fdb_blob_make(&blob, &boot_count, sizeof(boot_count)));
    log_i("set the 'boot_count' value to %d\n", boot_count);


    while(1)
    {
        fdb_kv_get_blob(&kvdb, "boot_count", fdb_blob_make(&blob, &boot_count, sizeof(boot_count)));
        if (blob.saved.len > 0)
        {
            log_i("get the 'boot_count' value is %d\n", boot_count);
        }
        else
        {
            log_i("get the 'boot_count' failed\n");
        }
        sleep(1);
    }
    return 0;
}