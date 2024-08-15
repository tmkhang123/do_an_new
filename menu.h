
using namespace std;

#pragma once

int currentMaLopTC;
DSSV DanhSach_SinhVien;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_border(int x, int y, int width, int height)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoxy(x, y);
    cout << char(201);
    for (int i = 0; i < width - 2; ++i)
    {
        cout << char(205);
    }
    cout << char(187);

    for (int i = 1; i < height - 1; ++i)
    {
        gotoxy(x, y + i);
        cout << char(186);
        gotoxy(x + width - 1, y + i);
        cout << char(186);
    }

    gotoxy(x, y + height - 1);
    cout << char(200);
    for (int i = 0; i < width - 2; ++i)
    {
        cout << char(205);
    }
    cout << char(188);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void moveByArrow(int& highlight, int& option, int& haveEntered, int menu_size)
{
    int key = _getch();
    switch (key)
    {
    case 72:
        highlight = (highlight - 1 + menu_size) % menu_size;
        break;
    case 80:
        highlight = (highlight + 1) % menu_size;
        break;
    case 13:
        option = highlight;
        haveEntered = 1;
        break;
    }
}

void get_highlight(int highlight, const string which_Menu[], int menu_size)
{
    int x = 5;
    int y = 2;
    int width = 40;
    int height = 3;

    for (int i = 0; i < menu_size; ++i)
    {
        draw_border(x, y + i * (height - 1), width, height);
        gotoxy(x + 1, y + 1 + i * (height - 1));

        if (i == highlight)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << which_Menu[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void SINHVIEN_menu(int& highlight, int option)
{
    system("cls");
    string option_menu_MONHOC[]
    {
        "1. Them sinh vien",
        "2. In danh sach sinh vien",
        "3. Sua thong tin sinh vien",
        "4. Xoa sinh vien",
        "5. Thoat chuc nang"
    };
    while (true)
    {
        int haveEntered = 0;
        get_highlight(highlight, option_menu_MONHOC, size(option_menu_MONHOC));
        moveByArrow(highlight, option, haveEntered, size(option_menu_MONHOC));
        if (haveEntered == 0)
        {
            continue;
        }
        switch (option)
        {
        case 0:
            system("cls");
            cout << "Them sinh vien" << endl;
            (DanhSach_SinhVien);
            nhapSinhVien(DanhSach_SinhVien);
            system("cls");
            break;
        case 1:
            system("cls");
            cout << "In Danh Sach Sinh Vien \n";
            inDanhSachSinhVien(DanhSach_SinhVien);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            cout << "Sua thong tin sinh vien" << endl;
            inDanhSachSinhVien(DanhSach_SinhVien);
            suaThongTin_SinhVien(DanhSach_SinhVien);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            inDanhSachSinhVien(DanhSach_SinhVien);
            xoa_SinhVien(DanhSach_SinhVien);
            cout << "Xoa sinh vien" << endl;
            system("pause");
            system("cls");
            break;
        case 4:
            return;
        }
    }
}

void MonHoc_Menu(int& highlight, int option, PTRMH& root, PTRMHTheoTen rootTheoTen)
{
    system("cls");
    saoChepCay(root, rootTheoTen);
    string option_menu_MONHOC[] = {
        "1. Them mon hoc",
        "2. In danh sach mon hoc",
        "3. Sua thong tin mon hoc",
        "4. Xoa mon hoc",
        "5. Thoat chuc nang"
    };

    while (true)
    {
        int haveEntered = 0;
        get_highlight(highlight, option_menu_MONHOC, static_cast<int>(size(option_menu_MONHOC)));
        moveByArrow(highlight, option, haveEntered, static_cast<int>(size(option_menu_MONHOC)));
        if (haveEntered == 0)
        {
            continue;
        }
        string maMHToDelete;
        switch (option)
        {
        case 0:
            system("cls");
            cout << "Them mon hoc" << endl;
            nhapMonHoc(root);
            system("pause");
            system("cls");
            break;
        case 1:
            system("cls");
            cout << "In danh sach mon hoc" << endl;
            inDanhSachMonHocTheoTen(rootTheoTen);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            cout << "Sua thong tin mon hoc" << endl;
            inDanhSachMonHoc(root);
            suaMonHoc(root);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            inDanhSachMonHoc(root);
            cout << "Nhap Ma Mon Hoc can xoa: ";
            getline(cin, maMHToDelete);
            root = xoaMonHoc(root, maMHToDelete);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            ghiDanhSachMonHoc(rootTheoTen, "list_MonHoc.txt");
            return;
        }
    }
}

void LTC_menu(int& highlight, int option, DSLTC& DSLTC, PTRMH& root)
{
    system("cls");
    string option_menu_LTC[] =
    {
        "1. Xem danh sach Lop Tin Chi",
        "2. Them Lop Tin Chi",
        "3. Xoa Lop Tin Chi",
        "4. Sua Lop Tin Chi",
        "5. Huy Lop Tin Chi",
        "6. Dang Ky Lop Tin Chi",
        "7. Thoat chuc nang"
    };

    while (true)
    {
        int haveEntered = 0;
        get_highlight(highlight, option_menu_LTC, size(option_menu_LTC));
        moveByArrow(highlight, option, haveEntered, size(option_menu_LTC));

        if (haveEntered == 0)
        {
            continue;
        }
        string nienKhoa;
        string hocKy;
        switch (option)
        {
        case 0:
            system("cls");
            cout << "Nhap nien khoa: "; getNumber_dash(nienKhoa, 9);
            cout << endl;
            cout << "Hoc ky: "; batHocKy(hocKy, 1);
            cout << endl;
            InDanhSachLopTinChi(DSLTC, root, nienKhoa, stoi(hocKy));
            system("pause");
            system("cls");
            break;
        case 1:
            system("cls");
            cout << "Them Lop Tin Chi" << endl;
            ThemLopTinChi(DSLTC, currentMaLopTC, root);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            cout << "Xoa Lop Tin Chi" << endl;
            XoaLopTinChi(DSLTC, root);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            cout << "Sua Lop Tin Chi" << endl;
            HieuChinhLopTinChi(DSLTC, root);
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            cout << "Huy Lop Tin Chi" << endl;
            HuyLopTinChi(DSLTC);
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            cout << "Dang Ky Lop Tin Chi" << endl;
            DangKyLopTinChi(DSLTC, root, DanhSach_SinhVien);
            system("pause");
            system("cls");
            break;
        case 6:
            return;
        }
    }
}

void main_menu(int& highlight, int option, PTRMH& root, DSLTC& dsLTC, PTRMHTheoTen& rootTheoTen)
{
    system("cls");
    string mainMenuItems[]
    {
        "1. Danh sach sinh vien",
        "2. Lop tin chi",
        "3. Danh sach Mon Hoc",
        "4. Nhap diem cho mon hoc",
        "5. Ket thuc chuong trinh"
    };
    while (true)
    {
        int haveEntered = 0;
        get_highlight(highlight, mainMenuItems, size(mainMenuItems));
        moveByArrow(highlight, option, haveEntered, size(mainMenuItems));
        if (haveEntered == 0)
        {
            continue;
        }
        switch (option)
        {
        case 0:
            system("cls");
            cout << "Danh sach sinh vien" << endl;
            SINHVIEN_menu(highlight, option);
            system("cls");
            break;
        case 1:
            system("cls");
            cout << "Nhap Lop tin chi" << endl;
            LTC_menu(highlight, option, dsLTC, root);
            system("cls");
            break;
        case 2:
            system("cls");
            cout << "Danh sach Mon Hoc" << endl;
            MonHoc_Menu(highlight, option, root, rootTheoTen);
            system("cls");
            break;
        case 3:
            system("cls");
            cout << "Nhap diem cho mon hoc" << endl;
            system("cls");
            break;
        case 4:
            return;
        }
    }
}