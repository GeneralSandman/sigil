#include <stdio.h>
#include <conio.h>

int main_()
{
    int ch1 = 0;
    int ch2 = 0;
    while (1)
    {
        if (ch1 = getch())
        {
            ch2 = getch(); //第一次调用getch()，返回值224
            switch (ch2)   //第二次调用getch()
            {
            case 72:
                printf("The key you Pressed is : ↑ \n");
                break;
            case 80:
                printf("The key you Pressed is : ↓ \n");
                break;
            case 75:
                printf("The key you Pressed is : ← \n");
                break;
            case 77:
                printf("The key you Pressed is : → \n");
                break;
            default:
                printf("No direction keys detected \n");
                break;
                break;
            }
        }
    }
    return 0;
}