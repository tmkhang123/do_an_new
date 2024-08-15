#include <iomanip>

void ghiMonHocRaFile(const string& tenFile, PTRMH root);
void docMonHocTuFile(const string& tenFile, PTRMH& root);
PTRMH xoaMonHoc(PTRMH root, const string& maMH);
PTRMH xoaNode(PTRMH root, const string& maMH);
// In-order traversal để in cây
void inCay(PTRMH root) {
    if (root) { // Kiểm tra nếu root không phải là nullptr
        inCay(root->left); // Duyệt cây con trái
        cout << "Ma Mon Hoc: " << root->mh.MaMH << endl;
        cout << "Ten Mon Hoc: " << root->mh.TenMH << endl;
        cout << "STCLT: " << root->mh.STCLT << endl;
        cout << "STCTH: " << root->mh.STCTH << endl;
        cout << "-----------------------" << endl;
        inCay(root->right); // Duyệt cây con phải
    }
}
void inDanhSachMonHoc(PTRMH root) {
    if (!root) {
        cout << "Danh sach mon hoc trong." << endl;
    }
    else {
        inCay(root);
    }
}
void themMonHocTheoTen(PTRMHTheoTen& root, MonHoc mh) {
    if (root == nullptr) {
        root = new nodeMonHocTheoTen{ mh, nullptr, nullptr };
        return;
    }
    if (mh.TenMH < root->mh.TenMH) {
        themMonHocTheoTen(root->left, mh);
    }
    else if (mh.TenMH > root->mh.TenMH) {
        themMonHocTheoTen(root->right, mh);
    }
}
void saoChepCay(PTRMH root, PTRMHTheoTen& rootTheoTen) {
    if (root == nullptr) return;

    saoChepCay(root->left, rootTheoTen);
    themMonHocTheoTen(rootTheoTen, root->mh);
    saoChepCay(root->right, rootTheoTen);
}
#include <iomanip>

void inDanhSachMonHocTheoTen(PTRMHTheoTen root) {
    const int width = 20;
    const int longWidth = 40;

    auto printRow = [](const string& maMH, const string& tenMH, int stclt, int stcth) {
        cout << setw(width) << left << maMH
            << setw(longWidth) << left << tenMH
            << setw(width) << left << stclt
            << setw(width) << left << stcth
            << endl;
        };

    cout << setw(width) << left << "Ma Mon Hoc"
        << setw(longWidth) << left << "Ten Mon Hoc"
        << setw(width) << left << "STCLT"
        << setw(width) << left << "STCTH"
        << endl;

    cout << setfill('-')
        << setw(width) << "-"
        << setw(longWidth) << "-"
        << setw(width) << "-"
        << setw(width) << "-"
        << setfill(' ')
        << endl;

    function<void(PTRMHTheoTen)> printTree = [&](PTRMHTheoTen node) {
        if (node) {
            printTree(node->left);
            printRow(node->mh.MaMH, node->mh.TenMH, node->mh.STCLT, node->mh.STCTH);
            printTree(node->right);
        }
        };

    printTree(root);
}
// Hàm kiểm tra mã môn học đã tồn tại trong cây chưa
bool checkTrungMaMH(PTRMH root, const string& maMH) {
    if (root == nullptr) return false;
    if (root->mh.MaMH == maMH) return true;
    if (maMH < root->mh.MaMH) return checkTrungMaMH(root->left, maMH);
    return checkTrungMaMH(root->right, maMH);
}
// Hàm thêm môn học vào cây nhị phân theo mã môn học
void themMonHoc(PTRMH& root, MonHoc mh) {
    if (root == nullptr) {
        root = new nodeMonHoc{ mh, nullptr, nullptr };
        return;
    }
    if (mh.MaMH < root->mh.MaMH) {
        themMonHoc(root->left, mh);
    }
    else if (mh.MaMH > root->mh.MaMH) {
        themMonHoc(root->right, mh);
    }
    // Nếu mh.MaMH == root->mh.MaMH, bạn có thể quyết định không thêm hoặc xử lý cập nhật dữ liệu ở đây nếu cần.
}
// Hàm tìm kiếm môn học trong cây nhị phân
PTRMH timKiemMonHoc(PTRMH root, const string& maMH) {
    if (root == nullptr || root->mh.MaMH == maMH) {
        return root;
    }

    if (maMH < root->mh.MaMH) {
        return timKiemMonHoc(root->left, maMH);
    }
    else {
        return timKiemMonHoc(root->right, maMH);
    }
}
 
// Hàm sửa thông tin môn học trong cây nhị phân
// Hàm sửa thông tin môn học trong cây nhị phân
void suaMonHoc(PTRMH& root) {
    string maMH;
    cout << "Nhap ma mon hoc can sua : ";
    getline(cin, maMH);

    // Tìm kiếm nút chứa môn học
    PTRMH node = timKiemMonHoc(root, maMH);

    if (node) {
        MonHoc mh = node->mh; // Lưu thông tin hiện tại để sử dụng khi thêm lại

        cout << "Nhap thong tin moi cho mon hoc (de trong neu khong thay doi):\n";

        // Cập nhật mã môn học
        string newMaMH;
        while (true) {
            cout << "Nhap Ma Mon Hoc (" << mh.MaMH << "): ";
            getline(cin, newMaMH);

            if (newMaMH.empty()) {
                newMaMH = mh.MaMH; // Giữ nguyên mã môn học nếu không nhập gì
            }

            // Kiểm tra mã môn học mới có bị trùng không
            if (newMaMH == mh.MaMH || !checkTrungMaMH(root, newMaMH)) {
                break; // Mã môn học hợp lệ
            }
            else {
                cout << "Ma mon hoc da ton tai. Vui long nhap lai.\n";
            }
        }

        // Cập nhật tên môn học
        cout << "Nhap Ten Mon Hoc (" << mh.TenMH << "): ";
        string newTenMH;
        getline(cin, newTenMH);
        if (!newTenMH.empty()) mh.TenMH = newTenMH;

        // Cập nhật số tín chỉ lý thuyết
        cout << "Nhap So Tin Chi Ly Thuyet (" << mh.STCLT << "): ";
        string newSTCLT;
        getline(cin, newSTCLT);
        try {
            if (!newSTCLT.empty()) mh.STCLT = stoi(newSTCLT);
        }
        catch (const invalid_argument& e) {
            cout << "Gia tri khong hop le cho So Tin Chi Ly Thuyet. Gia tri cu duoc giu lai.\n";
        }

        // Cập nhật số tín chỉ thực hành
        cout << "Nhap So Tin Chi Thuc Hanh (" << mh.STCTH << "): ";
        string newSTCTH;
        getline(cin, newSTCTH);
        try {
            if (!newSTCTH.empty()) mh.STCTH = stoi(newSTCTH);
        }
        catch (const invalid_argument& e) {
            cout << "Gia tri khong hop le cho So Tin Chi Thuc Hanh. Gia tri cu duoc giu lai.\n";
        }

        // Nếu mã môn học đã thay đổi, xóa nút cũ và thêm nút mới
        if (newMaMH != mh.MaMH) {
            // Xóa nút cũ
            root = xoaNode(root, mh.MaMH);

            // Cập nhật mã môn học
            mh.MaMH = newMaMH;

            // Thêm nút mới
            themMonHoc(root, mh);
        }
        else {
            // Nếu mã môn học không thay đổi, chỉ cần cập nhật thông tin
            node->mh = mh;
        }

        cout << "Thong tin mon hoc da duoc cap nhat.\n";
    }
    else {
        cout << "Khong tim thay mon hoc voi ma " << maMH << "\n";
    }
}
// Hàm đọc môn học từ file và lưu vào cây nhị phân
void docMonHocTuFile(const string& tenFile, PTRMH& root) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }

    MonHoc mh;
    string line;

    while (getline(file, mh.MaMH)) {
        // Xóa khoảng trắng đầu và cuối của MaMH
        mh.MaMH.erase(0, mh.MaMH.find_first_not_of(' '));
        mh.MaMH.erase(mh.MaMH.find_last_not_of(' ') + 1);

        if (!getline(file, mh.TenMH)) break; // Đọc dòng tiếp theo
        // Xóa khoảng trắng đầu và cuối của TenMH
        mh.TenMH.erase(0, mh.TenMH.find_first_not_of(' '));
        mh.TenMH.erase(mh.TenMH.find_last_not_of(' ') + 1);

        if (!getline(file, line)) break; // Đọc dòng tiếp theo
        istringstream iss(line);

        int stclt, stcth;
        if (!(iss >> stclt >> stcth)) {
            cerr << "Loi: Du lieu STCLT va STCTH khong hop le" << endl;
            continue; // Bỏ qua dòng này và tiếp tục với dòng tiếp theo
        }

        mh.STCLT = stclt;
        mh.STCTH = stcth;

        themMonHoc(root, mh); // Thêm môn học vào cây
    }

    file.close(); // Đóng tệp sau khi đã đọc xong
}
void ghiDanhSach(PTRMH node, ofstream& file) 
{
    if (node) {
        ghiDanhSach(node->left, file);
        file << node->mh.MaMH << endl;
        file << node->mh.TenMH << endl;
        file << node->mh.STCLT << " " << node->mh.STCTH;
        ghiDanhSach(node->right, file);
    }
}
// Hàm ghi môn học ra file mà không xóa dữ liệu cũ và không chèn lên dữ liệu cũ
void ghiMonHocRaFile(const string& tenFile, PTRMH root) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }

    ghiDanhSach(root, file);
    file.close();
}
// Hàm nhập môn học và ghi dữ liệu vào file
void nhapMonHoc(PTRMH& root) {
    MonHoc mh;
    while (true) {
        // Nhập mã môn học và kiểm tra trùng lặp
        while (true) {
            cout << "Nhap Ma Mon Hoc : ";
            getline(cin, mh.MaMH);
            if (mh.MaMH.empty()) return; // Kết thúc nếu người dùng nhập chuỗi rỗng

            if (timKiemMonHoc(root, mh.MaMH)) {
                cout << "Ma mon hoc da ton tai. Vui long nhap lai. \n ";
            }
            else {
                break; // Mã môn học hợp lệ
            }
        }

        // Nhập tên môn học và số tín chỉ
        cout << "Nhap Ten Mon Hoc : ";

        getline(cin, mh.TenMH);
        cout << "Nhap So Tin Chi Li Thuyet : ";
        cin >> mh.STCLT;
        cout << "Nhap So Tin Chi Thuc Hanh : ";
        cin >> mh.STCTH;
        cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số

        themMonHoc(root, mh);

      
    }
}
// Hàm ghi cây nhị phân vào file theo thứ tự trung tố
void ghiMonHocTheoThuTu(PTRMHTheoTen node, ofstream& file) {
    if (node != nullptr) 
    {
        ghiMonHocTheoThuTu(node->left, file); // Duyệt trái
        file << node->mh.MaMH << endl;
        file << node->mh.TenMH << endl;
        file << node->mh.STCLT << " " << node->mh.STCTH << endl;
        ghiMonHocTheoThuTu(node->right, file); // Duyệt phải
    }
}

// Hàm ghi toàn bộ cây nhị phân vào file
void ghiDanhSachMonHoc(PTRMHTheoTen root, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        ghiMonHocTheoThuTu(root, file);
        file.close();
    }
    else {
        cout << "Khong the mo file de ghi du lieu.\n";
    }
}
// Hàm tìm kiếm nút nhỏ nhất trong cây con bên phải
PTRMH timNhoNhat(PTRMH node) {
    PTRMH current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Hàm xóa một nút khỏi cây nhị phân tìm kiếm
PTRMH xoaNode(PTRMH root, const string& maMH) {
    if (root == nullptr) return nullptr;
    if (maMH < root->mh.MaMH) {
        root->left = xoaMonHoc(root->left, maMH);
    }
    else if (maMH > root->mh.MaMH) {
        root->right = xoaMonHoc(root->right, maMH);
    }
    else {
        if (root->left == nullptr) {
            PTRMH temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            PTRMH temp = root->left;
            delete root;
            return temp;
        }
        PTRMH temp = root->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }
        root->mh = temp->mh;
        root->right = xoaMonHoc(root->right, root->mh.MaMH);
    }
    return root;
}
// Hàm xóa môn học với xác nhận từ người dùng
PTRMH xoaMonHoc(PTRMH root, const string& maMH) {
    if (root == nullptr) {
        cout << "Mon hoc voi ma " << maMH << " khong ton tai.\n";
        return nullptr;
    }

    // Tìm nút cần xóa
    if (maMH < root->mh.MaMH) {
        root->left = xoaMonHoc(root->left, maMH);
    }
    else if (maMH > root->mh.MaMH) {
        root->right = xoaMonHoc(root->right, maMH);
    }
    else {
        // Xác nhận từ người dùng trước khi xóa
        char confirm;
        cout << "Ban co chac chan muon xoa mon hoc voi ma " << maMH << " khong? (y/n): ";
        cin >> confirm;
        cin.ignore(); // Bỏ qua ký tự newline

        if (confirm == 'y' || confirm == 'Y') {
            // Xóa nút
            if (root->left == nullptr) {
                PTRMH temp = root->right;
                delete root;
                cout << "Xoa mon hoc thanh cong.\n"; // Thông báo thành công
                return temp;
            }
            else if (root->right == nullptr) {
                PTRMH temp = root->left;
                delete root;
                cout << "Xoa mon hoc thanh cong.\n"; // Thông báo thành công
                return temp;
            }

            PTRMH temp = timNhoNhat(root->right);
            root->mh = temp->mh;
            root->right = xoaMonHoc(root->right, root->mh.MaMH);
            cout << "Xoa mon hoc thanh cong.\n"; // Thông báo thành công
        }
        else {
            cout << "Xoa mon hoc bi huy.\n";
        }
    }
    return root;
}