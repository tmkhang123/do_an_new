#pragma once

void moveByArrow(int& highlight, int& option, int& haveEntered, int menu_size)
{
    int key = _getch();
    switch (key) 
    {
        case 72: // Mũi tên lên
            highlight = (highlight - 1 + menu_size) % menu_size;
            break;
        case 80: // Mũi tên xuống
            highlight = (highlight + 1) % menu_size;
            break;
        case 13: // Phím Enter
            option = highlight;
            haveEntered = 1;
            break;
    }
}