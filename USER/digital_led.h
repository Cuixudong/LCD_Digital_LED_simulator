#ifndef __DIGITAL_LED_H
#define __DIGITAL_LED_H

#ifndef uint8_t
#define uint8_t unsigned char
#endif
#ifndef uint16_t
#define uint16_t unsigned short
#endif
#ifndef uint32_t
#define uint32_t unsigned int
#endif

typedef struct
{
    uint16_t Color_Front;
    uint16_t Color_Front_Emp;
    uint16_t Color_Back;
    uint16_t Draw_Pen_Size;
    uint8_t Auto_Size_Scal;
    uint8_t (*IF_DrawLine)(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye);    //IO初始化函数
    void (*Digital_Draw_Point)(uint16_t xs,uint16_t ys,uint16_t color);
    void (*Digital_Draw_Line)(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint16_t color);
} _Draw_Str;

extern uint16_t Color_Point;
extern _Draw_Str draw_str;

#define PARA_DRAW_EXTE  (0x01<<6) //显示未点亮部分白色
#define PARA_FILL_MAIN  (0x01<<7) //填充数码管
#define PARA_AUTO_SIZE  (0x01<<5) //自动控制数码管间隙
#define PARA_OVER_DRAW  (0x01<<4) //强制覆盖背景
#define PARA_SHOW_POINT (0x01<<3) //显示小数点
#define PARA_NUM_TYPE   (0x01<<2) //类型为原始段码

void Draw_Digital_num(uint16_t x,uint16_t y,uint8_t lw,uint16_t w,uint16_t h,uint8_t num,uint8_t fill);
/**

                   起始坐标
                   (x,y)___________________________________________
                       /                     A                     \      <-------------横线的宽度lw 值越小数码管越细长    ^
                      /\___________________________________________/\                                                      |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     | F|                                         |  |                                                     |
                     |  |                                         | B|                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |_________________________________________|  |                                                     |
                      \ /                                         \ /                                                      |
                      / \____________________G____________________/ \                                                  数码管高度h
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     | E|                                         | C|                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |                                         |  |                                                     |
                     |  |_________________________________________|  |                                                     |
                      \/                                           \/                                                      |
                       \_____________________D_____________________/                                                       |

                     <---------------数码管宽度w--------------------->

  例如显示数字1，则B，C段为显示的有效段，其余为无效段，mode参数的位5为1时则无效段是显示的不然就是显示成背景色和不显示一样，
  如果另其显示的同时位6也为1，那么显示的无效段就是填充成实心的，不然就是空心的只有边框
  主显示段也就是有效段是一直显示的，可以通过位7设置有效的这段是空心还是实心，为1是实心，否则空心

 *起始坐标XY，数码管段线宽，显示大小宽高，显示的数字
 *mode ：bit7 是否填充主显示段，bit6 是否填充副显示段，bit5 是否显示副显示段
 */
void Digital_Draw_num(uint16_t x,uint16_t y,uint8_t lw,uint16_t w,uint16_t h,uint8_t num,uint8_t mode);

#endif
