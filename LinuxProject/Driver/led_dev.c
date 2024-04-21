#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>


#define GPIO_BASE   0x0300B000
#define PC_CFG0     2*0x0024+0x00
#define PC_CFG1     2*0x0024+0x04
#define PC_CFG2     2*0x0024+0x08
#define PC_CFG3     2*0x0024+0x0C

#define PC_DAT     2*0x0024+0x10
#define PC_DRV0    2*0x0024+0x14
#define PC_DRV1    2*0x0024+0x18

#define DEV_NAME "led_chrdev"
#define DEV_CNT (3)

static dev_t devno;
struct class *led_chrdev_class;

struct led_chrdev {
    struct cdev dev;
    unsigned int __iomem *pc_cfg;  // port controller config register
    unsigned int __iomem *pc_dat;
    unsigned int __iomem *pc_pull;

    unsigned int led_pin;
};

static int led_chrdev_open(struct inode *inode, struct file *filp)
{

    unsigned int val = 0;
    struct led_chrdev *led_cdev = (struct led_chrdev *)container_of(inode->i_cdev, struct led_chrdev, dev);
    filp->private_data = container_of(inode->i_cdev, struct led_chrdev, dev);
    printk("open\n");
    val |= (0x43); // 开启a、b、g的时钟
    writel(val, va_clkaddr);

    // 设置模式寄存器：输出模式
    val = readl(led_cdev->va_moder);
    val &= ~((unsigned int)0X3 << (2 * led_cdev->led_pin));
    val |= ((unsigned int)0X1 << (2 * led_cdev->led_pin));
    writel(val,led_cdev->va_moder);
    // 设置输出类型寄存器：推挽模式
    val = readl(led_cdev->va_otyper);
    val &= ~((unsigned int)0X1 << led_cdev->led_pin);
    writel(val, led_cdev->va_otyper);
    // 设置输出速度寄存器：高速
    val = readl(led_cdev->va_ospeedr);
    val &= ~((unsigned int)0X3 << (2 * led_cdev->led_pin));
    val |= ((unsigned int)0x2 << (2 * led_cdev->led_pin));
    writel(val, led_cdev->va_ospeedr);
    // 设置上下拉寄存器：上拉
    val = readl(led_cdev->va_pupdr);
    val &= ~((unsigned int)0X3 << (2*led_cdev->led_pin));
    val |= ((unsigned int)0x1 << (2*led_cdev->led_pin));
    writel(val,led_cdev->va_pupdr);
    // 设置置位寄存器：默认输出低电平
    val = readl(led_cdev->va_bsrr);
    val |= ((unsigned int)0x1 << (led_cdev->led_pin + 16));
    writel(val, led_cdev->va_bsrr);

    return 0;
}

static int led_chrdev_release(struct inode *inode, struct file *filp)
{
    struct led_chrdev *led_cdev =
        (struct led_chrdev *)container_of(inode->i_cdev, struct led_chrdev,
                                          dev);
    iounmap(led_cdev->va_dr);
    iounmap(led_cdev->va_gdir);
    iounmap(led_cdev->va_iomuxc_mux);
    iounmap(led_cdev->va_ccm_ccgrx);
    iounmap(led_cdev->va_iomux_pad);
    return 0;
}

static ssize_t led_chrdev_write(struct file *filp, const char __user * buf, size_t count, loff_t * ppos)
{
    unsigned long val = 0;
    unsigned long ret = 0;

    int tmp = count;

    kstrtoul_from_user(buf, tmp, 10, &ret);
    struct led_chrdev *led_cdev = (struct led_chrdev *)filp->private_data;

    val = ioread32(led_cdev->va_dr);
    if (ret == 0)
            val &= ~(0x01 << led_cdev->led_pin);
    else
            val |= (0x01 << led_cdev->led_pin);

    iowrite32(val, led_cdev->va_dr);
    *ppos += tmp;
    return tmp;
}

static struct file_operations led_chrdev_fops = {
    .owner = THIS_MODULE,
    .open = led_chrdev_open,
    .release = led_chrdev_release,
    .write = led_chrdev_write,
};

static struct led_chrdev led_cdev[DEV_CNT] = {
    {.pa_dr = 0x0209C000,.pa_gdir = 0x0209C004,.pa_iomuxc_mux =
     0x20E006C,.pa_ccm_ccgrx = 0x20C406C,.pa_iomux_pad =
     0x20E02F8,.led_pin = 4,.clock_offset = 26},
    {.pa_dr = 0x20A8000,.pa_gdir = 0x20A8004,.pa_iomuxc_mux =
     0x20E01E0,.pa_ccm_ccgrx = 0x20C4074,.pa_iomux_pad =
     0x20E046C,.led_pin = 20,.clock_offset = 12},
    {.pa_dr = 0x20A8000,.pa_gdir = 0x20A8004,.pa_iomuxc_mux =
     0x20E01DC,.pa_ccm_ccgrx = 0x20C4074,.pa_iomux_pad =
     0x20E0468,.led_pin = 19,.clock_offset = 12},
};

static __init int led_chrdev_init(void)
{
    int i = 0;
    dev_t cur_dev;
    printk("led chrdev init\n");
    alloc_chrdev_region(&devno, 0, DEV_CNT, DEV_NAME);
    led_chrdev_class = class_create(THIS_MODULE, "led_chrdev");
    for (; i < DEV_CNT; i++) {
            cdev_init(&led_cdev[i].dev, &led_chrdev_fops);
            led_cdev[i].dev.owner = THIS_MODULE;
            cur_dev = MKDEV(MAJOR(devno), MINOR(devno) + i);
            cdev_add(&led_cdev[i].dev, cur_dev, 1);
            device_create(led_chrdev_class, NULL, cur_dev, NULL,
                          DEV_NAME "%d", i);
    }

    return 0;
}

module_init(led_chrdev_init);

static __exit void led_chrdev_exit(void)
{
    int i;
    dev_t cur_dev;
    printk("led chrdev exit\n");

    for (i = 0; i < DEV_CNT; i++) {

            cur_dev = MKDEV(MAJOR(devno), MINOR(devno) + i);

            device_destroy(led_chrdev_class, cur_dev);

            cdev_del(&led_cdev[i].dev);

    }
    unregister_chrdev_region(devno, DEV_CNT);
    class_destroy(led_chrdev_class);
}

module_exit(led_chrdev_exit);

MODULE_AUTHOR("embedfire");
MODULE_LICENSE("GPL");