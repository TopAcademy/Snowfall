#pragma once
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

using USHORT = unsigned short;
using UCHAR = unsigned char;

class Snowflake
{
	USHORT row;		// Текущая позиция: строка и
	USHORT col;		// колонка
	float speed;	// Скорость падения: от 0 до 1: где 0 - статичная, 1 - макс.скорость
	UCHAR melt;		// Уровень целостности (нерастаянности): от 0 (полностью растаяла) до 255 (полностью целая)

public:
	static USHORT max_row;		// высота экрана (задается объектом Landscape при объявлении)
	static float speed_base;	// базовая константа для расчета скорости

	// Constructor
	Snowflake(USHORT row, USHORT col, float speed) {
		if (Snowflake::max_row == 0) {
			throw std::runtime_error("Landscape didn't set the max row value");
		}
		this->row = row;
		this->col = col;
		this->speed = speed;
		this->melt = 255;
	}

	
	// Draw snowflake on the screen
	void draw() {
		// Set cursor position
		std::cout << "\x1b[" << row << ";" << col << "H";
		// Set color
		std::cout << "\x1b[38;2;" << (short)melt << ";" << (short)melt << ";" << (short)melt << "m";
		// Print star
		std::cout << '*';
	}


	// Hide snowflake from screen
	void erase() {
		// Set cursor position
		std::cout << "\x1b[" << row << ";" << col << "H";
		// Print space
		std::cout << ' ';
	}


	// Fall from current R position to max_row (bottom of the screen)
	void fall() {
		while (this->row <= Snowflake::max_row) {
			erase();
			row++;
			draw();
			std::this_thread::sleep_for(std::chrono::milliseconds(int(speed_base/speed)));
		}
	}

};

USHORT Snowflake::max_row = 0;
float Snowflake::speed_base = 20;
