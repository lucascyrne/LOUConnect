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
	char middlefinger[] = "        _____\n       |    ||\n       |\\___/|\n       |     |\n       |     |\n       |     |\n       |     |\n       |     |\n       |     |\n   ____||____|____\n  /    |     |     \\\n /     |     |    | \\\n|      |     |    |  |\n|      |     |    |  |\n|                 |  |\n|                 |  |\n|                    /\n|                   /\n \\                 /\n  \\               /\n   |             |\n   |             |\n";
	int size = sizeof (middlefinger) / sizeof(char);

	char c;
	int y;
	int x_padrao = 0;
	int x;

	system("cls");
	for (int i = 0; i < 69; i++)
	{
		x = x_padrao;
		y = 0;
	    for (int j = 0; j < size; j++)
	    {
	    	c = middlefinger[j];

	    	if (c == '\n'){
	    		y++;
	    		x = x_padrao;
	    	}

	        gotoxy(x,y);
	        printf("%c", c);
	        Sleep(1);
	        x++;
	    }
	    x_padrao += 23;
	}
	return 0;
}