
void HienThiLopTinChiTrongHocKy(const DSLTC& dsltc, PTRMH root, const string& nienKhoa, int hocKy) {
    cout << "Danh sach lop tin chi trong nien khoa " << nienKhoa << " va hoc ky " << hocKy << ":" << endl;
    bool found = false;
    for (int i = 0; i < dsltc.n; ++i) {
        if (dsltc.nodes[i]->NienKhoa == nienKhoa && dsltc.nodes[i]->HocKy == hocKy) {
            PTRMH mhNode = timKiemMonHoc(root, dsltc.nodes[i]->MaMH);
            string tenMH;
            if (mhNode != nullptr) {
                tenMH = mhNode->mh.TenMH;
            } else {
                tenMH = "Khong tim thay";
            }
            cout << "Ma Lop TC: " << dsltc.nodes[i]->MaLopTC << endl;
            cout << "Ma MH: " << dsltc.nodes[i]->MaMH << endl;
            cout << "Ten MH: " << tenMH << endl;
            cout << "Nhom: " << dsltc.nodes[i]->Nhom << endl;
            int countSV = 0;
            PTRDK p = dsltc.nodes[i]->FirstDK;
            while (p != nullptr) {
                if (p->dk.TrangThai == 1) {
                    countSV++;
                }
                p = p->next;
            }

            cout << "So SV da dang ky: " << countSV << endl;
            cout << "So slot con trong: " << (dsltc.nodes[i]->SoSVMax - countSV) << endl;
            cout << "-----------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay lop tin chi nao trong nien khoa " << nienKhoa << " va hoc ky " << hocKy << "." << endl;
    }
}


bool InThongTinSinhVien(const DSSV& dssv, const string& maSV) {
    for (int i = 0; i < dssv.n; ++i) {
        if (dssv.nodes[i].MaSV == maSV) {
            cout << "Thong tin sinh vien: " << endl;
            cout << "Ma SV: " << dssv.nodes[i].MaSV << endl;
            cout << "Ho: " << dssv.nodes[i].Ho << endl;
            cout << "Ten: " << dssv.nodes[i].Ten << endl;
            cout << "Phai: " << dssv.nodes[i].Phai << endl;
            cout << "So DT: " << dssv.nodes[i].SoDT << endl;
            cout << "Ma Lop: " << dssv.nodes[i].MaLop << endl;
            return true;
        }
    }
    cout << "Khong tim thay sinh vien voi Ma SV: " << maSV << endl;
    return false;
}
void DangKyLopTinChi(DSLTC& dsltc, PTRMH root, const DSSV& dssv) {
    string maSV;
    string maLopTC;
    string nienKhoa;
    string hocKy;
    bool foundLopTC = false;
    cout << "Nhap ma sinh vien can dang ky: ";
    cin >> maSV;
    bool foundSV = false;
    for (int i = 0; i < dssv.n; ++i) {
        if (dssv.nodes[i].MaSV == maSV) {
            foundSV = true;
            InThongTinSinhVien(dssv, maSV); 
            break;
        }
    }

    if (!foundSV) {
        cout << "Khong tim thay sinh vien voi ma: " << maSV << endl;
        return;
    }
    cout << "Nhap nien khoa: ";
    getNumber_dash(nienKhoa, 9);
    cout << "Nhap hoc ky: ";
    batHocKy(hocKy, 1);
    HienThiLopTinChiTrongHocKy(dsltc, root, nienKhoa, stoi(hocKy));
    do {
        cout << "Nhap ma lop tin chi can dang ky: ";
        cin >> maLopTC;

        for (int i = 0; i < dsltc.n; ++i) {
            if (dsltc.nodes[i]->MaLopTC == stoi(maLopTC)) {
                LopTinChi* ltc = dsltc.nodes[i];
                foundLopTC = true;
                if (ltc->NienKhoa != nienKhoa || ltc->HocKy != stoi(hocKy)) {
                    cout << "Lop tin chi khong phu hop voi nien khoa va hoc ky da chon." << endl;
                    return;
                }
                int countSV = 0;
                PTRDK p = ltc->FirstDK;
                while (p != nullptr) {
                    if (p->dk.TrangThai == 1) {
                        countSV++;
                    }
                    p = p->next;
                }
                if (countSV >= ltc->SoSVMax) {
                    cout << "Lop tin chi da day. Khong the dang ky." << endl;
                    return;
                }
                PTRDK newDK = new nodeDangKy;
                newDK->dk.MaSV = maSV;
                newDK->dk.TrangThai = 1;
                newDK->dk.Diem = 0; 
                newDK->next = ltc->FirstDK;
                ltc->FirstDK = newDK;
                cout << "Dang ky thanh cong!" << endl;
                LuuVaoFile("DSLTC.txt", dsltc);
                return;
            }
        }
    } while (!foundLopTC);
    if (!foundLopTC) {
        cout << "Khong tim thay lop tin chi voi ma " << maLopTC << endl;
    }
}

void HuyDangKyLopTinChi(DSLTC& dsltc, const string& masv, const string& maMH, const string& nienkhoa, int hocky, int nhom) {
    for (int i = 0; i < dsltc.n; i++) {
        LopTinChi* lop = dsltc.nodes[i];
        if (lop->MaMH == maMH && lop->NienKhoa == nienkhoa && lop->HocKy == hocky && lop->Nhom == nhom) {
            PTRDK prev = nullptr;
            PTRDK curr = lop->FirstDK;

            while (curr != nullptr) {
                if (curr->dk.MaSV == masv) {
                    curr->dk.TrangThai = 0; // 0 (hủy đăng ký)
                    std::cout << "Sinh viên " << masv << " đã hủy đăng ký lớp tín chỉ thành công.\n";
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
            cout << "Không tìm thấy sinh viên " << masv << " trong danh sách đăng ký lớp tín chỉ.\n";
            return;
        }
    }
    cout << "Không tìm thấy lớp tín chỉ với thông tin đã nhập.\n";
}