#pragma once
#include <windows.h>
#include <vector>
#include <mutex>
#include <chrono>
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

	
	// Create falling down snowflake in random position
	std::thread run_snowflake(Snowflake& flake) {
		std::thread t(&Snowflake::fall, &flake);
		return t;
	}


	// Запуск снегопада
	// Параметры:
	// - rate:  частота снежинок (пауза в мс)
	// - count: общее число запускаемых снежинок
	void run_snowfall(USHORT rate, USHORT count) {
		std::vector<Snowflake> flakes;
		flakes.reserve(count);
		std::vector<std::thread> threads;
		threads.reserve(count);
		for (USHORT i = 0; i < count; i++) {
			USHORT pos = double(rand()) / RAND_MAX * cols;	            // start position: (0; pos)
			double speed = 1.0 - (double(rand()) / (RAND_MAX * 2));		// random speed
			flakes.push_back(Snowflake(0, pos, speed));
			threads.push_back(run_snowflake(flakes[i]));
			std::this_thread::sleep_for(std::chrono::milliseconds(rate));
		}
		for (std::thread& t : threads) {
			t.join();
		}
	}

};

