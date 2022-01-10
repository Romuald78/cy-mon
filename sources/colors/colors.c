#include <stdio.h>


#define ALPHA(rgba) ((rgba>>24)&0xFF)
#define RED(rgba)   ((rgba>>16)&0xFF)
#define GREEN(rgba) ((rgba>> 8)&0xFF)
#define BLUE(rgba)  ((rgba    )&0xFF)

#define INT(r,g,b,a) (((a&0xFF)<<24)|((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF))

#define MIX(n1,n2,k1,k2) (((n1*(k1))+(n2*(k2)))/(0xFF)) 

unsigned char mixBytes(unsigned char v1, unsigned char v2, unsigned char k1, unsigned char k2){
    int tmp;
    tmp  = (v1*k1)+(v2*k2);
    tmp /= (k1+k2);
    tmp &= 0xFF;
    return tmp;
}

// rgb1 is the back color
// rgb2 is the front color, so if rgb2 is opaque, rgb1 is not visible anymore
int addRGB (int rgb1, int rgb2){
    unsigned char a1 = ALPHA(rgb1);
    unsigned char a2 = ALPHA(rgb2);
    // Compute output rgb    
    unsigned char r = mixBytes( RED  (rgb1), RED  (rgb2), a1, a2 );
    unsigned char g = mixBytes( GREEN(rgb1), GREEN(rgb2), a1, a2 );
    unsigned char b = mixBytes( BLUE (rgb1), BLUE (rgb2), a1, a2 );
    // the return value is always full opaque
    return INT(r,g,b,0xFF);
}

