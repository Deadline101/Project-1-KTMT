
// MFC Number ConverterDlg.h : header file
//

#pragma once

#include <stdio.h>
#include <string>
#include "HandleFileQInt.h"
#include "HandleFileQFloat.h"
#include "pch.h"
#include "QInt.h"
#include "QFloat.h"

// CMFCNumberConverterDlg dialog
class CMFCNumberConverterDlg : public CDialogEx
{
// Construction
public:
	CMFCNumberConverterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCNUMBERCONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OnOK();
	CString binNum;
	CString decNum;
	CString hexNum;
	QInt qIntNum;
	QInt qIntNum1; 
	QInt qIntNum2;
	QInt qIntNum3;
	QInt qIntNum4;
	QInt qIntNum5;
	Qfloat qFloat;

	int bitShiftLeft = 0, bitShiftRight = 0, bitROL = 0, bitROR = 0;
	int coeff1 = 0, coeff2 = 0, coeff3 = 0; 

	//QFloat qFloatNum;
	afx_msg void OnEnChangeEdit1(); //Không dùng
	CString IDC_Edit1; //Không dùng

	afx_msg void OnBnClickedConvert1(); //Nút Convert1, để đổi số QInt Bin sang Dec và Hex
	afx_msg void OnBnClickedConvert2(); //Nút Convert2, để đổi số QInt Dec sang Bin và Hex
	afx_msg void OnBnClickedConvert3(); //Nút Convert3, để lấy đường dẫn file txt, nạp vào xử lý rồi xuất ra ngay tại thư mục đó

	afx_msg void OnBnClickedConvert4(); //Nút Convert4, để đổi số QFloat Bin sang Dec
	afx_msg void OnBnClickedConvert5(); //Nút Convert5, để đổi số QFloat Dec sang Bin

	afx_msg void OnEnChangeNum1(); //Khi nhập số ở ô Num 1 thì sẽ thay đổi kết quả các phép tính, mặc định là 0
	afx_msg void OnEnChangeNum2(); //Khi nhập số ở ô Num 2 thì sẽ thay đổi kết quả các phép tính, mặc định là 0

	afx_msg void OnEnChangeNum3(); //Khi nhập số ở ô Num 1 thì sẽ thay đổi kết quả các toán tử, mặc định là 0
	afx_msg void OnEnChangeNum4(); //Khi nhập số ở ô Num 1 thì sẽ thay đổi kết quả các toán tử, mặc định là 0

	//Còn 4 nút các phép dịch bit
	afx_msg void OnEnChangeNum5(); //Khi nhập số ở ô thì thay đổi kết quả các phép dịch bit
	afx_msg void OnEnChangeBitShiftLeft(); //Nhập số bit cần dịch
	afx_msg void OnEnChangeBitShiftRight(); 
	afx_msg void OnEnChangeBitRol(); //Nhập số bit cần xoay
	afx_msg void OnEnChangeBitRor(); //Nhập số bit cần xoay

	CComboBox IDC_SELECT_COEFFICIENT_1; //Biến điều khiển combo box1
	CComboBox IDC_SELECT_COEFFICIENT_2; //Biến điều khiển combo box2
	CComboBox IDC_SELECT_COEFFICIENT_3; //Biến điều khiển combo box3
	afx_msg void OnCbnSelchangeSelectCoefficent1(); //Khi chọn trong combobox1, do something
	afx_msg void OnCbnSelchangeSelectCoefficent2(); //Khi chọn trong combobox2, do something
	afx_msg void OnCbnSelchangeSelectCoefficent3(); //Khi chọn trong combobox3, do something
	
};

//Các biến coeff là giá trị hệ số lấy từ 3 combobox, mặc định là 0
//Sử dụng nó cho đống switch...case của ông
//Đống switch...case thì sẽ nằm trong 5 hàm OnEnChangeNum