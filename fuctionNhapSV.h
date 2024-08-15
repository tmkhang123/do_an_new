#include <iomanip>
bool compareSinhVien(const SinhVien &a, const SinhVien &b) /*Ham Dung De so sanh Ten va Ho, so sanh thong tin cua 
sinh vien A va B*/
{
    if (a.MaLop != b.MaLop)
    {
        return a.MaLop < b.MaLop;
    }
    if (a.Ten != b.Ten) 
    {
        return a.Ten < b.Ten;
    }
    return a.Ho < b.Ho;
}

// void insertSorted(DSSV &DanhSach, const SinhVien &sv)
// {
//     int i = DanhSach.n - 1;
//     while (i >= 0 && compareSinhVien(sv, DanhSach.nodes[i]) == true)
//     {
//         DanhSach.nodes[i + 1] = DanhSach.nodes[i];
//         i--;
//     }
//     DanhSach.nodes[i + 1] = sv;
//     DanhSach.n++;
// }

bool check_TrungMaSV(DSSV &DanhSach, const string &maSV)
{
    for (int i = 0; i < DanhSach.n; ++i)
    {
        if (DanhSach.nodes[i].MaSV == maSV)
        {
            return true;
        }
    }
    return false;
}

//Doc thong tin SV tu File
void docList_SinhVien(const string& tenFile, DSSV &DanhSach)
{
    ifstream file(tenFile);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }

    while (!file.eof())
    {
        SinhVien sv;
        string line;

        // Doc thong tin MaLop & MaSV & Ho tren mot dong 
        getline(file, line);
        istringstream iss(line);
        iss >> sv.MaLop >> sv.MaSV;
        // Doc ho tren mot dong
        getline(file, sv.Ho);
        // Doc ten tren mot dong
        getline(file, sv.Ten);

        // Doc gioi tinh và SDT trên một dòng
        getline(file, line);
        istringstream iss2(line);
        iss2 >> sv.Phai >> sv.SoDT;

        // Lay khoan trong trong file
        getline(file, line);
        if (DanhSach.n < MaxSV)
        {
            DanhSach.nodes[DanhSach.n++] = sv;
        }
        else
        {
            cout << "Danh sach sinh vien da day.\n";
            break;
        }
    }

    file.close();
}

void sortDanhSachSinhVien(DSSV &DanhSach) 
{
    for (int i = 0; i < DanhSach.n - 1; ++i) 
    {
        for (int j = i + 1; j < DanhSach.n; ++j) 
        {
            if (!compareSinhVien(DanhSach.nodes[i], DanhSach.nodes[j])) 
            {
                // Hoán đổi vị trí của hai sinh viên
                SinhVien temp = DanhSach.nodes[i];
                DanhSach.nodes[i] = DanhSach.nodes[j];
                DanhSach.nodes[j] = temp;
            }
        }
    }
}

//ghi Thong Tin Vao File
void ghiThongTinVaoFile(const string& tenFile, DSSV& DanhSach)
{
    ofstream file(tenFile);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }

    for (int i = 0; i < DanhSach.n; ++i)
    {
        if (i > 0) // Chỉ thêm dòng trống nếu không phải sinh viên đầu tiên
        {
            file << endl << endl;
        }
        file << DanhSach.nodes[i].MaLop << " " << DanhSach.nodes[i].MaSV << endl;
        file << DanhSach.nodes[i].Ho << endl;
        file << DanhSach.nodes[i].Ten << endl;
        file << DanhSach.nodes[i].Phai << " " << DanhSach.nodes[i].SoDT;
    }
    sortDanhSachSinhVien(DanhSach);
    file.close();
}

// void sortDanhSachSinhVien(DSSV &DanhSach) 
// {
//     for (int i = 0; i < DanhSach.n - 1; ++i) 
//     {
//         for (int j = i + 1; j < DanhSach.n; ++j) 
//         {
//             if (!compareSinhVien(DanhSach.nodes[i], DanhSach.nodes[j])) 
//             {
//                 // Hoán đổi vị trí của hai sinh viên
//                 SinhVien temp = DanhSach.nodes[i];
//                 DanhSach.nodes[i] = DanhSach.nodes[j];
//                 DanhSach.nodes[j] = temp;
//             }
//         }
//     }
//     ghiThongTinVaoFile("list_SinhVien.txt", DanhSach);
// }

void nhapSinhVien(DSSV &DanhSach)
{   
    SinhVien sv;
    // string maLopChung;
    cout << "Nhap Ma Lop chung cho tat ca sinh vien: ";
    getOnlyWord_Number_forMaSV(sv.MaLop, 15);
    cout << endl;

    while (true)
    {
        // sv.MaLop = sv.MaLop;  // Gán mã lớp chung cho sinh viên mới

        cout << "Nhap MSSV: ";
        getOnlyWord_Number_forMaSV(sv.MaSV, 15);
        cout << endl;
        if (sv.MaSV.empty())
        {
            break;
        }
        if (check_TrungMaSV(DanhSach, sv.MaSV) == true)
        {
            cout << "Da Trung Ma Sinh Vien\n";
            continue;
        }
        cout << "Nhap ho: ";
        getOnlyWord_Space(sv.Ho, 50);
        cout << endl;
        cout << "Nhap ten: ";
        getOnlyWord(sv.Ten, 10);
        cout << endl;
        cout << "Nhap gioi tinh: ";
        getOnlyWord(sv.Phai, 4);
        cout << endl;
        cout << "Nhap so DT: ";
        getOnlyNumber(sv.SoDT, 10);
        cout << endl;
        if (DanhSach.n < MaxSV)
        {
            DanhSach.nodes[DanhSach.n++] = sv;
        }
        else
        {
            cout << "Danh sach sinh vien da day.\n";
            break;
        }
    }
    ghiThongTinVaoFile("list_SinhVien.txt", DanhSach);
}

void xoa_SinhVien(DSSV &DanhSach)
{
    string MSSV;
    cout << "Nhap MSSV: ";
    getOnlyWord_Number_forMaSV(MSSV, 15, false);
    for(int i = 0; i < DanhSach.n; i++)
    {
        if (DanhSach.nodes[i].MaSV == MSSV)
        {
            for (int j = i; j < DanhSach.n - 1; ++j)
            {
                DanhSach.nodes[j] = DanhSach.nodes[j + 1];
            }
            --DanhSach.n;
            cout << "Da xoa sinh vien co MSSV: " << MSSV << endl;
            system("cls");
            return;
        }
        ghiThongTinVaoFile("list_SinhVien.txt", DanhSach);
    }
    cout << "Khong tim thay sinh vien co MSSV: " << MSSV << endl;
}

void suaThongTin_SinhVien(DSSV &DanhSach)
{
    while (true) 
    {
        string MSSV;
        cout << "Nhap MSSV: ";
        getOnlyWord_Number(MSSV, 15);
        cout << endl;
        // Kiểm tra MSSV có trong danh sách không
        bool found = false;
        for (int i = 0; i < DanhSach.n; i++) 
        {
            if (DanhSach.nodes[i].MaSV == MSSV) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            cout << "Khong co thong tin MSSV trong danh sach. Vui long nhap lai.\n";
            continue;
        }

        // Sửa thông tin sinh viên nếu MSSV tồn tại
        for (int i = 0; i < DanhSach.n; i++) 
        {
            if (DanhSach.nodes[i].MaSV == MSSV) 
            {
                SinhVien &sv = DanhSach.nodes[i];
                cout << "Nhap thong tin moi cho sinh vien (de trong neu khong thay doi):\n";

                cout << "Nhap Ma Lop (" << sv.MaLop << "): ";
                string newMaLop = sv.MaLop;
                getOnlyWord_Number(newMaLop, 15, false);
                cout << endl;
                if (!newMaLop.empty()) sv.MaLop = newMaLop;

                cout << "Nhap MSSV (" << sv.MaSV << "): ";
                string newMaSV = sv.MaSV;
                sv.MaSV = "";
                getOnlyWord_Number(newMaSV, 15, false);
                cout << endl;
                // if (!newMaSV.empty()) sv.MaSV = newMaSV;
                if (check_TrungMaSV(DanhSach, newMaSV) == true)
                {
                    cout << "Trung ma voi sinh vien khac. Vui long nhap lai MSSV.\n";
                    continue;
                }
                if (!newMaSV.empty()) sv.MaSV = newMaSV;

                cout << "Nhap ho (" << sv.Ho << "): ";
                string newHo = sv.Ho;
                getOnlyWord_Space(newHo, 50, false);
                cout << endl;
                if (!newHo.empty()) sv.Ho = newHo;

                cout << "Nhap ten (" << sv.Ten << "): ";
                string newTen = sv.Ten;
                getOnlyWord(newTen, 10, false);
                cout << endl;
                if (!newTen.empty()) sv.Ten = newTen;

                cout << "Nhap gioi tinh (" << sv.Phai << "): ";
                string newPhai = sv.Phai;
                getOnlyWord(newPhai, 4, false);
                cout << endl;
                if (!newPhai.empty()) sv.Phai = newPhai;

                cout << "Nhap so DT (" << sv.SoDT << "): ";
                string newSoDT = sv.SoDT;
                getOnlyWord_Number(newSoDT, 10, false);
                cout << endl;
                if (!newSoDT.empty()) sv.SoDT = newSoDT;

                ghiThongTinVaoFile("list_SinhVien.txt", DanhSach);
                cout << "Thong tin sinh vien da duoc cap nhat.\n";
                return;
            }
        }
    }
}

void inDanhSachSinhVien(const DSSV& DanhSach)
{
    // Đặt chiều rộng cột
    const int width = 20;

    // In tiêu đề bảng
    cout << setw(width) << left << "MSSV"
        << setw(width) << left << "Ho"
        << setw(width) << left << "Ten"
        << setw(width) << left << "Gioi tinh"
        << setw(width) << left << "So DT"
        << setw(width) << left << "Ma Lop"
        << endl;

    // In đường viền dưới tiêu đề
    cout << setfill('-')
        << setw(width) << "-"
        << setw(width) << "-"
        << setw(width) << "-"
        << setw(width) << "-"
        << setw(width) << "-"
        << setw(width) << "-"
        << setfill(' ')
        << endl;

    // In thông tin sinh viên
    for (int i = 0; i < DanhSach.n; ++i)
    {
        cout << setw(width) << left << DanhSach.nodes[i].MaSV
            << setw(width) << left << DanhSach.nodes[i].Ho
            << setw(width) << left << DanhSach.nodes[i].Ten
            << setw(width) << left << DanhSach.nodes[i].Phai
            << setw(width) << left << DanhSach.nodes[i].SoDT
            << setw(width) << left << DanhSach.nodes[i].MaLop
            << endl;
    }
}