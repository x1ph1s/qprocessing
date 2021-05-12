#pragma once

namespace {
	const char* vertexShaderSource = R"~(
#version 330 core

precision mediump float;
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

out vec4 v_color;

void main() {
	gl_Position = vec4(a_position,1);
	v_color=a_color;
}
	)~";

	const char* fragmentShaderSource = R"~(
#version 330 core

precision mediump float;
layout(location = 0) out vec4 f_color;

in vec4 v_color;

void main() {
	f_color=v_color;
}
	)~";
}
