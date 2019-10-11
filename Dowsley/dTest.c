#include <stdio.h>
#include <stdlib.h>   // Para gerenciamento de memória
#include <conio.h>   // para gerenciamento de input e output direto do console.
#include <windows.h> // Para funções relacionadas ao windows
#include <string.h>  // Operações de string
#include <unistd.h>  // Para sleep functions


/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


int main()
{
	

	return 0;
}