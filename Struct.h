#include "mylib.h"
#pragma once
struct MonHoc 
{
	string MaMH; string TenMH;
	int STCLT, STCTH;
};
struct nodeMonHoc 
{
	MonHoc mh;
	struct nodeMonHoc *left;
	struct nodeMonHoc *right;
};
typedef nodeMonHoc *PTRMH;
// dang ki LTC - lk don
struct DangKy 
{
	string MaSV;
	int TrangThai = 1;
	float Diem;
};
struct nodeDangKy 
{
	DangKy dk;
	nodeDangKy *next;
};
typedef nodeDangKy *PTRDK;
// Danh sach LTC - danh sach tuyen tinh
struct LopTinChi 
{
	int MaLopTC;
	string MaMH;
	string NienKhoa;
	int HocKy, Nhom, SoSVMin, SoSVMax;
	int TrangThaiLTC = 1;
	PTRDK FirstDK = NULL;
};
const int MaxLTC = 10000;
struct DSLTC 
{
	LopTinChi *nodes[MaxLTC];
	int n = 0;
};
// Danh sach SV - danh sach tuyen tinh
struct SinhVien 
{
	string MaSV;
	string Ho;
	string Ten;
	string Phai;
	string SoDT;
	string MaLop;
};
const int MaxSV = 5000;
struct DSSV 
{
	SinhVien nodes[MaxSV];
	int n = 0;
};

struct nodeMonHocTheoTen {
	MonHoc mh;
	nodeMonHocTheoTen* left;
	nodeMonHocTheoTen* right;
};

typedef nodeMonHocTheoTen* PTRMHTheoTen;
// int main () {
// 	PTRMH tree_mh = NULL;
// 	DSLTC dsltc;
// 	DSSV dssv;
// }

