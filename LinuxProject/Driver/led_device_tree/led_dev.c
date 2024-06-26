#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define GPIO_BASE 0x0300B000
#define PC_CFG0 2 * 0x0024 + 0x00
#define PC_CFG1 2 * 0x0024 + 0x04

#define PC_DAT 2 * 0x0024 + 0x10

#define DEV_NAME "led_dev"
#define DEV_CNT (2)

static dev_t devno;
struct class *led_chrdev_class;

/*
    Description: LED Driver 
    Pin: PC12 PC13
*/ 
struct led_chrdev
{
    struct cdev dev;
    unsigned int __iomem *va_cfg; 
    unsigned int __iomem *va_dat;
    unsigned int __iomem *va_pull;

    unsigned int pa_cfg;
    unsigned int pa_dat;
    unsigned int pa_pull;

    unsigned int led_pin;
};

static struct led_chrdev led_cdev[DEV_CNT] = {
    {   
        .pa_cfg = GPIO_BASE + PC_CFG1, 
        .pa_dat = GPIO_BASE + PC_DAT, 
        .led_pin = 12,
    },
    // PC12
    {   
        .pa_cfg = GPIO_BASE + PC_CFG1, 
        .pa_dat = GPIO_BASE + PC_DAT, 
        .led_pin = 13,
    },
    // PC13
};

static int led_chrdev_open(struct inode *inode, struct file *filp)
{
    unsigned int val = 0;
    struct led_chrdev *led_cdev = (struct led_chrdev *)container_of(inode->i_cdev, struct led_chrdev, dev);
    filp->private_data = container_of(inode->i_cdev, struct led_chrdev, dev);
    printk("open\n");
    led_cdev->va_cfg = ioremap(led_cdev->pa_cfg, 4);
    led_cdev->va_dat = ioremap(led_cdev->pa_dat, 4);
    led_cdev->va_pull = ioremap(led_cdev->pa_pull, 4);

    val = readl(led_cdev->va_cfg);
    printk("cfg: %d", val);
    val |= ((unsigned int)0x01 << ((led_cdev->led_pin - 12) * 4 + 16));
    writel(val, led_cdev->va_cfg);

    val &= ((unsigned int)0X0 << led_cdev->led_pin);
    printk("dat: %d", val);
    writel(val, led_cdev->va_dat);

    return 0;
}

static int led_chrdev_release(struct inode *inode, struct file *filp)
{
    struct led_chrdev *led_cdev =
        (struct led_chrdev *)container_of(inode->i_cdev, struct led_chrdev, dev);
    iounmap(led_cdev->va_cfg);
    iounmap(led_cdev->va_dat);
    iounmap(led_cdev->va_pull);
    return 0;
}

static ssize_t led_chrdev_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    unsigned long val = 0;
    unsigned long ret = 0;

    int tmp = count;

    kstrtoul_from_user(buf, tmp, 10, &ret);
    struct led_chrdev *led_cdev = (struct led_chrdev *)filp->private_data;

    val = ioread32(led_cdev->va_dat);
    if (ret == 0)
        val &= ~(0x01 << led_cdev->led_pin);
    else
        val |= (0x01 << led_cdev->led_pin);

    iowrite32(val, led_cdev->va_dat);
    *ppos += tmp;
    return tmp;
}

static struct file_operations led_chrdev_fops = {
    .owner = THIS_MODULE,
    .open = led_chrdev_open,
    .release = led_chrdev_release,
    .write = led_chrdev_write,
};


static __init int led_chrdev_init(void)
{
    int i = 0;
    dev_t cur_dev;
    printk("led chrdev init\n");
    alloc_chrdev_region(&devno, 0, DEV_CNT, DEV_NAME);
    led_chrdev_class = class_create(THIS_MODULE, "led_dev");
    for (; i < DEV_CNT; i++)
    {
        cdev_init(&led_cdev[i].dev, &led_chrdev_fops);
        led_cdev[i].dev.owner = THIS_MODULE;
        cur_dev = MKDEV(MAJOR(devno), MINOR(devno) + i);
        cdev_add(&led_cdev[i].dev, cur_dev, 1);
        device_create(led_chrdev_class, NULL, cur_dev, NULL, DEV_NAME "%d", i);
    }

    return 0;
}

module_init(led_chrdev_init);

static __exit void led_chrdev_exit(void)
{
    int i;
    dev_t cur_dev;
    printk("led chrdev exit\n");

    for (i = 0; i < DEV_CNT; i++)
    {

        cur_dev = MKDEV(MAJOR(devno), MINOR(devno) + i);

        device_destroy(led_chrdev_class, cur_dev);

        cdev_del(&led_cdev[i].dev);
    }
    unregister_chrdev_region(devno, DEV_CNT);
    class_destroy(led_chrdev_class);
}

module_exit(led_chrdev_exit);

MODULE_AUTHOR("wind");
MODULE_LICENSE("GPL");