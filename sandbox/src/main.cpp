#include <iostream>

#include "qprocessing.h"
using namespace qprocessing;

void setup() {
	size(500, 500);
}
float pos = 0;
void draw() {
	background(0, 0, 0);
	color c = color(77, 102, 204, 255);
	fill(c);
	constexpr size_t sqquads = 100;
	constexpr float spacing	 = 2.0f / sqquads;
	for(float x = -1; x < 1; x += spacing) {
		for(float y = -1; y < 1; y += spacing) {
			float r = (x + 1) * 255.0f / 2.0f, b = (y + 1) * 255.0f / 2.0f;
			fill(r, b, 0);
			rect(x, y, spacing * 0.9, spacing * 0.9);
		}
	}
	ellipse(0, 0, 0.2, 0.1);
}
