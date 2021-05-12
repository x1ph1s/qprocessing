#include "qprocessing.h"

namespace qprocessing{
	color::color(int gray,int v4){
		int a = v4 << 24;
		int r = gray << 16;
		int g = gray << 8;
		int b = gray;
		colorValue = a + r + g + b;
	}
	color::color(int v1,int v2,int v3,int v4){
		int a = v4 << 24;
		int r = v1 << 16;
		int g = v2 << 8;
		int b = v3;
		colorValue = a + r + g + b;
	}

	float alpha(color c){
		int a_c = c.colorValue >> 24;
		return a_c;
	}
	float red(color c){
		int r_c = c.colorValue >> 16;
		r_c &= 0x000000FF;
		return r_c;
	}
	float green(color c){
		int g_c = c.colorValue >> 8;
		g_c &= 0x000000FF;
		return g_c;
	}
	float blue(color c){
		int b_c = c.colorValue & 0x000000FF;
		return b_c;
	}
	color::operator int(){
		return colorValue & 0x00FFFFFF;
	}
}
