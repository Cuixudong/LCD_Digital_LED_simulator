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
    uint8_t (*IF_DrawLine)(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye);    //IO��ʼ������
    void (*Digital_Draw_Point)(uint16_t xs,uint16_t ys,uint16_t color);
    void (*Digital_Draw_Line)(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint16_t color);
} _Draw_Str;

extern uint16_t Color_Point;
extern _Draw_Str draw_str;

#define PARA_DRAW_EXTE  (0x01<<6) //��ʾδ�������ְ�ɫ
#define PARA_FILL_MAIN  (0x01<<7) //��������
#define PARA_AUTO_SIZE  (0x01<<5) //�Զ���������ܼ�϶
#define PARA_OVER_DRAW  (0x01<<4) //ǿ�Ƹ��Ǳ���
#define PARA_SHOW_POINT (0x01<<3) //��ʾС����
#define PARA_NUM_TYPE   (0x01<<2) //����Ϊԭʼ����

void Draw_Digital_num(uint16_t x,uint16_t y,uint8_t lw,uint16_t w,uint16_t h,uint8_t num,uint8_t fill);
/**

                   ��ʼ����
                   (x,y)___________________________________________
                       /                     A                     \      <-------------���ߵĿ��lw ֵԽС�����Խϸ��    ^
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
                      / \____________________G____________________/ \                                                  ����ܸ߶�h
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

                     <---------------����ܿ��w--------------------->

  ������ʾ����1����B��C��Ϊ��ʾ����Ч�Σ�����Ϊ��Ч�Σ�mode������λ5Ϊ1ʱ����Ч������ʾ�Ĳ�Ȼ������ʾ�ɱ���ɫ�Ͳ���ʾһ����
  ���������ʾ��ͬʱλ6ҲΪ1����ô��ʾ����Ч�ξ�������ʵ�ĵģ���Ȼ���ǿ��ĵ�ֻ�б߿�
  ����ʾ��Ҳ������Ч����һֱ��ʾ�ģ�����ͨ��λ7������Ч������ǿ��Ļ���ʵ�ģ�Ϊ1��ʵ�ģ��������

 *��ʼ����XY������ܶ��߿���ʾ��С��ߣ���ʾ������
 *mode ��bit7 �Ƿ��������ʾ�Σ�bit6 �Ƿ���丱��ʾ�Σ�bit5 �Ƿ���ʾ����ʾ��
 */
void Digital_Draw_num(uint16_t x,uint16_t y,uint8_t lw,uint16_t w,uint16_t h,uint8_t num,uint8_t mode);

#endif
