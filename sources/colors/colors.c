#include <stdio.h>


#define ALPHA(rgba) ((rgba>>24)&0xFF)
#define RED(rgba)   ((rgba>>16)&0xFF)
#define GREEN(rgba) ((rgba>> 8)&0xFF)
#define BLUE(rgba)  ((rgba    )&0xFF)

#define INT(r,g,b,a) (((a&0xFF)<<24)|((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF))

#define MIX(n1,n2,k) ((n1*k)+(n2*(1-k))) 


int addRGB (int rgb1, int rgb2){
    float r = MIX(RED(rgb1),RED(rgb2),0.5);
    float g = MIX(GREEN(rgb1),GREEN(rgb2),0.5);
    float b = MIX(BLUE(rgb1),BLUE(rgb2),0.5);
   return 0;
}
