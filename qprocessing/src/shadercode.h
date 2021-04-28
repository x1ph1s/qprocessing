#pragma once

const char* vertexShaderSourceString =
	"#version 300 es\n"
	"precision mediump float;\n"
	"layout(location = 0) in vec3 a_position;\n"
	"layout(location=1) in vec4 a_color;\n"

	"out vec4 v_color;\n"

	"void main(){\n"
	"    gl_Position = vec4(a_position,1);\n"
	"    v_color=a_color;\n"
	"}\0";

const char* fragmantShaderSourceString =
	"#version 300 es\n"
	"precision mediump float;\n"
	"layout(location=0)out vec4 f_color;\n"

	"in vec4 v_color;\n"

	"void main(){\n"
	"	f_color=v_color;\n"
	"}\0";
