#include <stdio.h>
#include <gpiod.h>

int main()
{
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int val;

    // 打开GPIO设备
    chip = gpiod_chip_open_by_number(0);  // 0是设备编号，根据实际情况修改

    // 获取GPIO引脚
    line = gpiod_chip_get_line(chip, X);  // 替换X为引脚编号

    // 设置GPIO引脚的方向
    gpiod_line_request_output(line, "gpio-example", GPIOD_LINE_ACTIVE_STATE_HIGH);

    // 设置GPIO引脚的值
    gpiod_line_set_value(line, 1);  // 设置为高电平

    // 读取GPIO引脚的值
    val = gpiod_line_get_value(line);
    printf("GPIO value: %d\n", val);

    // 关闭GPIO设备
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}