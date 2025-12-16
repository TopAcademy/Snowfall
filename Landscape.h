#pragma once
#include <windows.h>
#include "Snowflake.h"


class Landscape
{
	USHORT rows;	// Высота экрана в строках
	USHORT cols;	// Ширина экрана в символах

public:

	// Constructor
	Landscape() {
		// Get and save console size
		HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO cinfo;
		GetConsoleScreenBufferInfo(cons, &cinfo);
		this->rows = cinfo.srWindow.Bottom - cinfo.srWindow.Top + 1;
		this->cols = cinfo.srWindow.Right - cinfo.srWindow.Left + 1;
		// Clear console screen and remove cursor
		std::cout << "\x1b[2J\x1b[?25l";
		// Init Snowflake static option
		Snowflake::max_row = rows;
	}

};