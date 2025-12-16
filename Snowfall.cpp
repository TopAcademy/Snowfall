// Snowfall.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Landscape.h"


int main()
{
    Landscape screen;
    Snowflake flake(4, 5, 0.02);
    flake.fall();
}

