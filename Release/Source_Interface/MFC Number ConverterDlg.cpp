
// MFC Number ConverterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC Number Converter.h"
#include "MFC Number ConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCNumberConverterDlg dialog



CMFCNumberConverterDlg::CMFCNumberConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNUMBERCONVERTER_DIALOG, pParent)
	, IDC_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCNumberConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, IDC_Edit1);
	DDX_Control(pDX, IDC_SELECT_COEFFICENT_1, IDC_SELECT_COEFFICIENT_1);
	DDX_Control(pDX, IDC_SELECT_COEFFICENT_2, IDC_SELECT_COEFFICIENT_2);
	DDX_Control(pDX, IDC_SELECT_COEFFICENT_3, IDC_SELECT_COEFFICIENT_3);
}

BEGIN_MESSAGE_MAP(CMFCNumberConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCNumberConverterDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CONVERT1, &CMFCNumberConverterDlg::OnBnClickedConvert1)
	ON_BN_CLICKED(IDC_CONVERT2, &CMFCNumberConverterDlg::OnBnClickedConvert2)
	ON_BN_CLICKED(IDC_CONVERT3, &CMFCNumberConverterDlg::OnBnClickedConvert3)
	ON_BN_CLICKED(IDC_CONVERT4, &CMFCNumberConverterDlg::OnBnClickedConvert4)
	ON_BN_CLICKED(IDC_CONVERT5, &CMFCNumberConverterDlg::OnBnClickedConvert5)
	ON_EN_CHANGE(IDC_NUM1, &CMFCNumberConverterDlg::OnEnChangeNum1)
	ON_EN_CHANGE(IDC_NUM2, &CMFCNumberConverterDlg::OnEnChangeNum2)
	ON_EN_CHANGE(IDC_NUM3, &CMFCNumberConverterDlg::OnEnChangeNum3)
	ON_EN_CHANGE(IDC_NUM4, &CMFCNumberConverterDlg::OnEnChangeNum4)
	ON_EN_CHANGE(IDC_BIT_SHIFT_LEFT, &CMFCNumberConverterDlg::OnEnChangeBitShiftLeft)
	ON_EN_CHANGE(IDC_NUM5, &CMFCNumberConverterDlg::OnEnChangeNum5)
	//ON_EN_CHANGE(IDC_BIT_RIGHT, &CMFCNumberConverterDlg::OnEnChangeBitRight)
	ON_EN_CHANGE(IDC_BIT_ROL, &CMFCNumberConverterDlg::OnEnChangeBitRol)
	ON_EN_CHANGE(IDC_BIT_ROR, &CMFCNumberConverterDlg::OnEnChangeBitRor)
	ON_CBN_SELCHANGE(IDC_SELECT_COEFFICENT_1, &CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent1)
	ON_EN_CHANGE(IDC_BIT_SHIFT_RIGHT, &CMFCNumberConverterDlg::OnEnChangeBitShiftRight)
	ON_CBN_SELCHANGE(IDC_SELECT_COEFFICENT_2, &CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent2)
	ON_CBN_SELCHANGE(IDC_SELECT_COEFFICENT_3, &CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent3)
END_MESSAGE_MAP()


// CMFCNumberConverterDlg message handlers

BOOL CMFCNumberConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCNumberConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCNumberConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCNumberConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCNumberConverterDlg::OnOK()
{
	//do nothing
}



void CMFCNumberConverterDlg::OnEnChangeEdit1() //Nên đặt check spell ở đây
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
}


void CMFCNumberConverterDlg::OnBnClickedConvert1() //Nút Convert1, để đổi số QInt Bin sang Dec và Hex
{
	// TODO: Add your control notification handler code here
	
	GetDlgItemText(IDC_EDIT1, binNum); //lấy dữ liệu từ ô IDC_EDIT1 nạp vào binNum
	std::string STDbinNum(CW2A(binNum.GetString())); //Chuyển CString thành std::string để tiện xử lý
	//Có STDbinNum là string được lấy từ ô EDIT1
	//thôi xài phương án 2, xài hàm có throw, tự viết catch
	QInt temp;
	// decNum = CString(temp.mBinToDec(STDbinNum).c_str()); //Chuyển STDbinNum thành số hệ thập phân
	// hexNum = CString(temp.mBinToHex(STDbinNum).c_str()); //Chuyển STDbinNum thành số hệ thập phân
	try {
		temp = temp.BinToDec(STDbinNum);
		decNum = CString(temp.PrintQInt(temp).c_str());
		hexNum = CString(temp.BinToHex(STDbinNum).c_str());
	}
	catch (nERROR e) {
		catchError(e);
	}

	SetDlgItemText(IDC_EDIT2, decNum);//Hiển thị số dạng thập phân ở ô EDIT2
	SetDlgItemText(IDC_EDIT3, hexNum);//Hiển thị số dạng thập lục phân ở ô EDIT3
}


void CMFCNumberConverterDlg::OnBnClickedConvert2() //Nút Convert2, để đổi số QInt Dec sang Bin và Hex
{
	// TODO: Add your control notification handler code here
	
	GetDlgItemText(IDC_EDIT2, decNum); //lấy dữ liệu từ ô IDC_EDIT2 nạp vào decNum
	std::string STDdecNum(CW2A(decNum.GetString())); //Chuyển CString thành std::string để tiện xử lý
	//Có STDdecNum là string được lấy từ ô EDIT2, xử lý thành số

	QInt temp;
	try {
		temp.ScanQInt(temp, STDdecNum);
		binNum = CString(temp.DecToBin(temp).c_str());
		hexNum = CString(temp.BinToHex(temp.DecToBin(temp)).c_str());
	}
	catch (nERROR e) {
		catchError(e);
	}

	//
	// binNum = CString(STDdecNum.c_str()); //Chuyển chuỗi STDbinNum đã được xử lý, tính toán thành dạng số nhị phân, về dạng CString để hiển thị
	// hexNum = CString gì đó
	SetDlgItemText(IDC_EDIT1, binNum);//Hiển thị số dạng nhị phân ở ô EDIT1
	SetDlgItemText(IDC_EDIT3, hexNum);//Hiển thị số dạng thập lục phân ở ô EDIT3
}


void CMFCNumberConverterDlg::OnBnClickedConvert3() //Chọn file
{
	CFileDialog dlgFile(TRUE);
	CString fileName;
	const int c_cMaxFiles = 1;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cbBuffSize;

	dlgFile.DoModal(); //Hiện dialog chọn file
	std::string std_fileName(CW2A(fileName.GetString())); 

	//CString nFileName(std_fileName.c_str()); //Để test xem button trả về gì thoi
	//SetDlgItemText(IDC_EDIT3, nFileName);

	//Đặt code xử lý file ở đây
			



	//Hết code xử lý file
	fileName.ReleaseBuffer();

}


void CMFCNumberConverterDlg::OnBnClickedConvert4()
{
	// TODO: Add your control notification handler code here

	GetDlgItemText(IDC_EDIT4, binNum); //lấy dữ liệu từ ô IDC_EDIT nạp vào biNum
	std::string STDbinNum(CW2A(binNum.GetString())); //Chuyển CString thành std::string để tiện xử lý
	//Có STDbinNum là string được lấy từ ô EDIT4, xử lý thành số
	
	Qfloat res;
	res = res.BinToDec(STDbinNum);

	// cái strKq này là dec thì phải :)
	string strKq = res.Print(false);


	//
	decNum = CString(strKq.c_str()); //Chuyển chuỗi STDbinNum đã được xử lý, tính toán thành dạng số thập phân, về dạng CString để hiển thị
	SetDlgItemText(IDC_EDIT5, decNum);//Hiển thị số dạng thập phân ở ô EDIT5

}


void CMFCNumberConverterDlg::OnBnClickedConvert5()
{
	// TODO: Add your control notification handler code here

	GetDlgItemText(IDC_EDIT5, decNum); //lấy dữ liệu từ ô IDC_EDIT5 nạp vào biNum
	std::string STDdecNum(CW2A(decNum.GetString())); //Chuyển CString thành std::string để tiện xử lý
	//Có STDbinNum là string được lấy từ ô EDIT5, xử lý thành số

	Qfloat q(STDdecNum);
	string str = q.DecToBin(q);

	//
	binNum = CString(str.c_str()); //Chuyển chuỗi STDbinNum đã được xử lý, tính toán thành dạng số thập phân, về dạng CString để hiển thị
	SetDlgItemText(IDC_EDIT4, binNum);//Hiển thị số dạng thập phân ở ô EDIT4
}


void CMFCNumberConverterDlg::OnEnChangeNum1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_qIntNum1;
	GetDlgItemText(IDC_NUM1, cs_qIntNum1);
	std::string std_qIntNum1(CW2A(cs_qIntNum1.GetString()));

	switch (coeff1) {
	case 0: {
		try {
			if (std_qIntNum1 == "") {
				std_qIntNum1 = "0";
			}
			if (std_qIntNum1 == "-") {
				std_qIntNum1 = "-0";
			}
			qIntNum1.ScanQInt(qIntNum1, std_qIntNum1);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 1: {
		try {
			if (std_qIntNum1 == "") {
				std_qIntNum1 = "0";
			}
			if (std_qIntNum1 == "-") {
				std_qIntNum1 = "-0";
			}
			qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 2: {
		try {
			if (std_qIntNum1 == "") {
				std_qIntNum1 = "0";
			}
			if (std_qIntNum1 == "-") {
				std_qIntNum1 = "-0";
			}
			//qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
			qIntNum1.ScanHex(std_qIntNum1, qIntNum1);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;
	}

	QInt temp;
	//Mở comment này ra khi có QInt
	QInt add = qIntNum1 + qIntNum2; //Kết quả phép cộng
	QInt subtract = qIntNum1 - qIntNum2; //Kết quả phép trừ
	QInt multiply = qIntNum1 * qIntNum2; //Kết quả phép nhân
	QInt divide = qIntNum1 / qIntNum2; //Kết quả phép chia

	//Tính toán + - * /
	// mấy cái num1 num2 nhập vào từ đâu v phương 
	// làm cái box cho chọn hệ nhập vào đã :)))
	string s_Add;
	string s_Subtract;
	string s_Multiply;
	string s_Divine;
	switch (coeff1) {
	case 0: {
		s_Add      = temp.PrintQInt(add);
		s_Subtract = temp.PrintQInt(subtract);
		s_Multiply = temp.PrintQInt(multiply);
		s_Divine   = temp.PrintQInt(divide);
	} break;

	case 1: {
		s_Add      = temp.DecToBin(add);
		s_Subtract = temp.DecToBin(subtract);
		s_Multiply = temp.DecToBin(multiply);
		s_Divine   = temp.DecToBin(divide);
	} break;

	case 2: {
		s_Add      = temp.BinToHex(add.DecToBin(add));
		s_Subtract = temp.BinToHex(subtract.DecToBin(subtract));
		s_Multiply = temp.BinToHex(multiply.DecToBin(multiply));
		s_Divine   = temp.BinToHex(divide.DecToBin(divide));
	} break;
	}

	CString cs_Add(s_Add.c_str());
	CString cs_Subtract(s_Subtract.c_str());
	CString cs_Multiply(s_Multiply.c_str());
	CString cs_Divine(s_Divine.c_str());

	SetDlgItemText(IDC_RESULT_ADD, cs_Add);
	SetDlgItemText(IDC_RESULT_SUBTRACT, cs_Subtract);
	SetDlgItemText(IDC_RESULT_MULTIPLY, cs_Multiply);
	QInt zero;
	if (qIntNum2 == zero) {
		SetDlgItemText(IDC_RESULT_DIVINE, CString(_T("NaN")));
	}
	else {
		SetDlgItemText(IDC_RESULT_DIVINE, cs_Divine);
	}

}


void CMFCNumberConverterDlg::OnEnChangeNum2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString cs_qIntNum2;
	GetDlgItemText(IDC_NUM2, cs_qIntNum2);
	std::string std_qIntNum2(CW2A(cs_qIntNum2.GetString()));

	//try {
	//	if (std_qIntNum2 == "") {
	//		std_qIntNum2 = "0";
	//	}
	//	if (std_qIntNum2 == "-") {
	//		std_qIntNum2 = "-0";
	//	}
	//	qIntNum2.ScanQInt(qIntNum2, std_qIntNum2);
	//}
	//catch (nERROR e) {
	//	catchError(e);
	//}

	switch (coeff1) {
	case 0: {
		try {
			if (std_qIntNum2 == "") {
				std_qIntNum2 = "0";
			}
			if (std_qIntNum2 == "-") {
				std_qIntNum2 = "-0";
			}
			qIntNum2.ScanQInt(qIntNum2, std_qIntNum2);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 1: {
		try {
			if (std_qIntNum2 == "") {
				std_qIntNum2 = "0";
			}
			if (std_qIntNum2 == "-") {
				std_qIntNum2 = "-0";
			}
			qIntNum2 = qIntNum2.BinToDec(std_qIntNum2);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 2: {
		try {
			if (std_qIntNum2 == "") {
				std_qIntNum2 = "0";
			}
			if (std_qIntNum2 == "-") {
				std_qIntNum2 = "-0";
			}
			//qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
			qIntNum2.ScanHex(std_qIntNum2, qIntNum2);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;
	}

	QInt temp;

	//Mở comment này ra khi có QInt
	QInt add = qIntNum1 + qIntNum2; //Kết quả phép cộng
	QInt subtract = qIntNum1 - qIntNum2; //Kết quả phép trừ
	QInt multiply = qIntNum1 * qIntNum2; //Kết quả phép nhân
	QInt divine = qIntNum1 / qIntNum2; //Kết quả phép chia


	//string s_Add = temp.PrintQInt(add);
	//string s_Subtract = temp.PrintQInt(subtract);
	//string s_Multiply = temp.PrintQInt(multiply);
	//string s_Divine = temp.PrintQInt(divine);

	string s_Add;
	string s_Subtract;
	string s_Multiply;
	string s_Divine;
	switch (coeff1) {
	case 0: {
		s_Add = temp.PrintQInt(add);
		s_Subtract = temp.PrintQInt(subtract);
		s_Multiply = temp.PrintQInt(multiply);
		s_Divine = temp.PrintQInt(divine);
	} break;

	case 1: {
		s_Add = temp.DecToBin(add);
		s_Subtract = temp.DecToBin(subtract);
		s_Multiply = temp.DecToBin(multiply);
		s_Divine = temp.DecToBin(divine);
	} break;

	case 2: {
		s_Add = temp.BinToHex(add.DecToBin(add));
		s_Subtract = temp.BinToHex(subtract.DecToBin(subtract));
		s_Multiply = temp.BinToHex(multiply.DecToBin(multiply));
		s_Divine = temp.BinToHex(divine.DecToBin(divine));
	} break;
	}

	CString cs_Add(s_Add.c_str());
	CString cs_Subtract(s_Subtract.c_str());
	CString cs_Multiply(s_Multiply.c_str());
	CString cs_Divine(s_Divine.c_str());

	SetDlgItemText(IDC_RESULT_ADD, cs_Add);
	SetDlgItemText(IDC_RESULT_SUBTRACT, cs_Subtract);
	SetDlgItemText(IDC_RESULT_MULTIPLY, cs_Multiply);
	
	QInt zero;
	if (qIntNum2 == zero) {
		SetDlgItemText(IDC_RESULT_DIVINE, CString(_T("NaN")));
	}
	else {
		SetDlgItemText(IDC_RESULT_DIVINE, cs_Divine);
	}
}


void CMFCNumberConverterDlg::OnEnChangeNum3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_qIntNum3;
	GetDlgItemText(IDC_NUM3, cs_qIntNum3);
	std::string std_qIntNum3(CW2A(cs_qIntNum3.GetString()));
	
	//try {
	//	if (std_qIntNum3 == "") {
	//		std_qIntNum3 = "0";
	//	}
	//	if (std_qIntNum3 == "-") {
	//		std_qIntNum3 = "-0";
	//	}
	//	qIntNum3.ScanQInt(qIntNum3, std_qIntNum3);
	//}
	//catch (nERROR e) {
	//	catchError(e);
	//}

	switch (coeff2) {
	case 0: {
		try {
			if (std_qIntNum3 == "") {
				std_qIntNum3 = "0";
			}
			if (std_qIntNum3 == "-") {
				std_qIntNum3 = "-0";
			}
			qIntNum3.ScanQInt(qIntNum3, std_qIntNum3);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 1: {
		try {
			if (std_qIntNum3 == "") {
				std_qIntNum3 = "0";
			}
			if (std_qIntNum3 == "-") {
				std_qIntNum3 = "-0";
			}
			qIntNum3 = qIntNum3.BinToDec(std_qIntNum3);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 2: {
		try {
			if (std_qIntNum3 == "") {
				std_qIntNum3 = "0";
			}
			if (std_qIntNum3 == "-") {
				std_qIntNum3 = "-0";
			}
			//qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
			qIntNum3.ScanHex(std_qIntNum3, qIntNum3);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;
	}

	QInt temp;

	QInt and = qIntNum3 & qIntNum4; //Kết quả phép AND
	QInt or = qIntNum3 | qIntNum4; //Kết quả phép OR
	QInt xor = qIntNum3 ^ qIntNum4; //Kết quả phép XOR
	QInt not1 = ~qIntNum3; //Kết quả phép NOT 1
	QInt not2 = ~qIntNum4; //Kết quả phép NOT 2

	string s_And;
	string s_Or;
	string s_Xor;
	string s_Not1;
	string s_Not2;

	switch (coeff2) {
	case 0: {
		s_And  = temp.PrintQInt(and );
		s_Or   = temp.PrintQInt(or  );
		s_Xor  = temp.PrintQInt(xor );
		s_Not1 = temp.PrintQInt(not1);
		s_Not2 = temp.PrintQInt(not2);
	} break;

	case 1: {
		s_And = temp.DecToBin(and);
		s_Or = temp.DecToBin(or);
		s_Xor = temp.DecToBin(xor);
		s_Not1 = temp.DecToBin(not1);
		s_Not2 = temp.DecToBin(not2);
	} break;

	case 2: {
		s_And  = temp.BinToHex(and.DecToBin(and));
		s_Or = temp.BinToHex(or.DecToBin(or));
		s_Xor = temp.BinToHex(xor.DecToBin(xor));
		s_Not1 = temp.BinToHex(not1.DecToBin(not1));
		s_Not2 = temp.BinToHex(not2.DecToBin(not2));
	} break;
	}


	CString cs_And(s_And.c_str());
	CString cs_Or(s_Or.c_str());
	CString cs_Xor(s_Xor.c_str());
	CString cs_Not1(s_Not1.c_str());
	CString cs_Not2(s_Not2.c_str());

	SetDlgItemText(IDC_RESULT_AND, cs_And);
	SetDlgItemText(IDC_RESULT_OR, cs_Or);
	SetDlgItemText(IDC_RESULT_XOR, cs_Xor);
	SetDlgItemText(IDC_RESULT_NOT1, cs_Not1);
	SetDlgItemText(IDC_RESULT_NOT2, cs_Not2);

	CString vTrue = CString(_T("TRUE"));
	CString vFalse = CString(_T("FALSE"));

	if (qIntNum3 > qIntNum4) {
		SetDlgItemText(IDC_RESULT_BIGGER, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_BIGGER, vFalse);
	}

	if (qIntNum3 < qIntNum4) {
		SetDlgItemText(IDC_RESULT_SMALLER, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_SMALLER, vFalse);
	}

	if (qIntNum3 == qIntNum4) {
		SetDlgItemText(IDC_RESULT_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_EQUAL, vFalse);
	}

	if (qIntNum3 >= qIntNum4) {
		SetDlgItemText(IDC_RESULT_BIGGER_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_BIGGER_EQUAL, vFalse);
	}

	if (qIntNum3 <= qIntNum4) {
		SetDlgItemText(IDC_RESULT_SMALLER_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_SMALLER_EQUAL, vFalse);
	}
}


void CMFCNumberConverterDlg::OnEnChangeNum4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_qIntNum4;
	GetDlgItemText(IDC_NUM4, cs_qIntNum4);
	std::string std_qIntNum4(CW2A(cs_qIntNum4.GetString()));

	//try {
	//	if (std_qIntNum4 == "") {
	//		std_qIntNum4 = "0";
	//	} 
	//	if (std_qIntNum4 == "-") {
	//		std_qIntNum4 = "-0";
	//	}
	//	qIntNum4.ScanQInt(qIntNum4, std_qIntNum4);
	//}
	//catch (nERROR e) {
	//	catchError(e);
	//}

	switch (coeff2) {
	case 0: {
		try {
			if (std_qIntNum4 == "") {
				std_qIntNum4 = "0";
			}
			if (std_qIntNum4 == "-") {
				std_qIntNum4 = "-0";
			}
			qIntNum4.ScanQInt(qIntNum4, std_qIntNum4);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 1: {
		try {
			if (std_qIntNum4 == "") {
				std_qIntNum4 = "0";
			}
			if (std_qIntNum4 == "-") {
				std_qIntNum4 = "-0";
			}
			qIntNum4 = qIntNum4.BinToDec(std_qIntNum4);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 2: {
		try {
			if (std_qIntNum4 == "") {
				std_qIntNum4 = "0";
			}
			if (std_qIntNum4 == "-") {
				std_qIntNum4 = "-0";
			}
			//qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
			qIntNum4.ScanHex(std_qIntNum4, qIntNum4);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;
	}

	QInt temp;

	QInt and = qIntNum3 & qIntNum4; //Kết quả phép AND
	QInt or = qIntNum3 | qIntNum4; //Kết quả phép OR
	QInt xor = qIntNum3 ^ qIntNum4; //Kết quả phép XOR
	QInt not1 = ~qIntNum3; //Kết quả phép NOT 1
	QInt not2 = ~qIntNum4; //Kết quả phép NOT 2

	string s_And;
	string s_Or;
	string s_Xor;
	string s_Not1;
	string s_Not2;

	switch (coeff2) {
	case 0: {
		s_And = temp.PrintQInt(and);
		s_Or = temp.PrintQInt(or );
		s_Xor = temp.PrintQInt(xor);
		s_Not1 = temp.PrintQInt(not1);
		s_Not2 = temp.PrintQInt(not2);
	} break;

	case 1: {
		s_And = temp.DecToBin(and);
		s_Or = temp.DecToBin(or );
		s_Xor = temp.DecToBin(xor);
		s_Not1 = temp.DecToBin(not1);
		s_Not2 = temp.DecToBin(not2);
	} break;

	case 2: {
		s_And = temp.BinToHex(and .DecToBin(and));
		s_Or = temp.BinToHex(or .DecToBin(or ));
		s_Xor = temp.BinToHex(xor .DecToBin(xor));
		s_Not1 = temp.BinToHex(not1.DecToBin(not1));
		s_Not2 = temp.BinToHex(not2.DecToBin(not2));
	} break;
	}

	//string s_And = temp.PrintQInt(and);
	//string s_Or = temp.PrintQInt(or );
	//string s_Xor = temp.PrintQInt(xor);
	//string s_Not1 = temp.PrintQInt(not1);
	//string s_Not2 = temp.PrintQInt(not2);

	CString cs_And(s_And.c_str());
	CString cs_Or(s_Or.c_str());
	CString cs_Xor(s_Xor.c_str());
	CString cs_Not1(s_Not1.c_str());
	CString cs_Not2(s_Not2.c_str());

	SetDlgItemText(IDC_RESULT_AND, cs_And);
	SetDlgItemText(IDC_RESULT_OR, cs_Or);
	SetDlgItemText(IDC_RESULT_XOR, cs_Xor);
	SetDlgItemText(IDC_RESULT_NOT1, cs_Not1);
	SetDlgItemText(IDC_RESULT_NOT2, cs_Not2);

	CString vTrue = CString(_T("TRUE"));
	CString vFalse = CString(_T("FALSE"));

	if (qIntNum3 > qIntNum4) {
		SetDlgItemText(IDC_RESULT_BIGGER, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_BIGGER, vFalse);
	}

	if (qIntNum3 < qIntNum4) {
		SetDlgItemText(IDC_RESULT_SMALLER, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_SMALLER, vFalse);
	}

	if (qIntNum3 == qIntNum4) {
		SetDlgItemText(IDC_RESULT_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_EQUAL, vFalse);
	}

	if (qIntNum3 >= qIntNum4) {
		SetDlgItemText(IDC_RESULT_BIGGER_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_BIGGER_EQUAL, vFalse);
	}

	if (qIntNum3 <= qIntNum4) {
		SetDlgItemText(IDC_RESULT_SMALLER_EQUAL, vTrue);
	}
	else {
		SetDlgItemText(IDC_RESULT_SMALLER_EQUAL, vFalse);
	}
}


void CMFCNumberConverterDlg::OnEnChangeNum5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_qIntNum5;
	GetDlgItemText(IDC_NUM5, cs_qIntNum5);
	std::string std_qIntNum5(CW2A(cs_qIntNum5.GetString()));

	//try {
	//	if (std_qIntNum5 == "") {
	//		std_qIntNum5 = "0";
	//	}
	//	if (std_qIntNum5 == "-") {
	//		std_qIntNum5 = "-0";
	//	}
	//	qIntNum5.ScanQInt(qIntNum5, std_qIntNum5);
	//}
	//catch (nERROR e) {
	//	catchError(e);
	//}

	switch (coeff3) {
	case 0: {
		try {
			if (std_qIntNum5 == "") {
				std_qIntNum5 = "0";
			}
			if (std_qIntNum5 == "-") {
				std_qIntNum5 = "-0";
			}
			qIntNum5.ScanQInt(qIntNum5, std_qIntNum5);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 1: {
		try {
			if (std_qIntNum5 == "") {
				std_qIntNum5 = "0";
			}
			if (std_qIntNum5 == "-") {
				std_qIntNum5 = "-0";
			}
			qIntNum5 = qIntNum5.BinToDec(std_qIntNum5);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;

	case 2: {
		try {
			if (std_qIntNum5 == "") {
				std_qIntNum5 = "0";
			}
			if (std_qIntNum5 == "-") {
				std_qIntNum5 = "-0";
			}
			//qIntNum1 = qIntNum1.BinToDec(std_qIntNum1);
			qIntNum5.ScanHex(std_qIntNum5, qIntNum5);
		}
		catch (nERROR e) {
			catchError(e);
		}
	} break;
	}

	QInt temp;

	QInt shiftLeft = qIntNum5 << bitShiftLeft; //Kết quả phép Shift Left
	QInt shiftRight = qIntNum5 >> bitShiftRight; //Kết quả phép OR
	QInt rol = temp.rol(qIntNum5, bitROL); //Kết quả phép ROL
	QInt ror = temp.ror(qIntNum5, bitROR); //Kết quả phép ROR

	string s_ShiftLeft;
	string s_ShiftRight;
	string s_ROL;
	string s_ROR;

	switch (coeff3) {
	case 0: {
		s_ShiftLeft = temp.PrintQInt(shiftLeft);
		s_ShiftRight = temp.PrintQInt(shiftRight);
		s_ROL = temp.PrintQInt(rol);
		s_ROR = temp.PrintQInt(ror);
	} break;

	case 1: {
		s_ShiftLeft  = temp.DecToBin(shiftLeft);
		s_ShiftRight = temp.DecToBin(shiftRight);
		s_ROL        = temp.DecToBin(rol);
		s_ROR        = temp.DecToBin(ror);
	} break;

	case 2: {
		s_ShiftLeft  = temp.BinToHex(temp.DecToBin(shiftLeft));
		s_ShiftRight = temp.BinToHex(temp.DecToBin(shiftRight));
		s_ROL = temp.BinToHex(temp.DecToBin(rol));
		s_ROR = temp.BinToHex(temp.DecToBin(ror));
	} break;
	}

	CString cs_ShiftLeft(s_ShiftLeft.c_str());
	CString cs_ShiftRight(s_ShiftRight.c_str());
	CString cs_ROL(s_ROL.c_str());
	CString cs_ROR(s_ROR.c_str());

	SetDlgItemText(IDC_RESULT_SHIFT_LEFT, cs_ShiftLeft);
	SetDlgItemText(IDC_RESULT_SHIFT_RIGHT, cs_ShiftRight);
	SetDlgItemText(IDC_RESULT_ROL, cs_ROL);
	SetDlgItemText(IDC_RESULT_ROR, cs_ROR);
}


void CMFCNumberConverterDlg::OnEnChangeBitShiftLeft()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_bitShiftLeft;
	GetDlgItemText(IDC_BIT_SHIFT_LEFT, cs_bitShiftLeft);
	std::string std_bitShiftLeft(CW2A(cs_bitShiftLeft.GetString()));
	if (std_bitShiftLeft == "") {
		std_bitShiftLeft = "0";
	}
	bitShiftLeft = stoi(std_bitShiftLeft);

	QInt temp;
	QInt shiftLeft = qIntNum5 << bitShiftLeft; //Kết quả phép Shift Left
	string s_ShiftLeft;
	switch (coeff3) {
	case 0: {
		s_ShiftLeft = temp.PrintQInt(shiftLeft);
	} break;

	case 1: {
		s_ShiftLeft = temp.DecToBin(shiftLeft);
	} break;

	case 2: {
		s_ShiftLeft = temp.BinToHex(temp.DecToBin(shiftLeft));
	} break;
	}
	
	CString cs_ShiftLeft(s_ShiftLeft.c_str());
	SetDlgItemText(IDC_RESULT_SHIFT_LEFT, cs_ShiftLeft);
}


void CMFCNumberConverterDlg::OnEnChangeBitShiftRight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_bitShiftRight;
	GetDlgItemText(IDC_BIT_SHIFT_RIGHT, cs_bitShiftRight);
	std::string std_bitShiftRight(CW2A(cs_bitShiftRight.GetString()));
	if (std_bitShiftRight == "") {
		std_bitShiftRight = "0";
	}
	bitShiftRight = stoi(std_bitShiftRight);

	QInt temp;
	QInt shiftRight = qIntNum5 >> bitShiftRight; //Kết quả phép Shift Right
	string s_ShiftRight;
	switch (coeff3) {
	case 0: {
		s_ShiftRight = temp.PrintQInt(shiftRight);
	} break;

	case 1: {
		s_ShiftRight = temp.DecToBin(shiftRight);
	} break;

	case 2: {
		s_ShiftRight = temp.BinToHex(temp.DecToBin(shiftRight));
	} break;
	}
	//string s_ShiftRight = temp.PrintQInt(shiftRight);
	CString cs_ShiftRight(s_ShiftRight.c_str());
	SetDlgItemText(IDC_RESULT_SHIFT_RIGHT, cs_ShiftRight);
}


void CMFCNumberConverterDlg::OnEnChangeBitRol()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString cs_ROL;
	GetDlgItemText(IDC_BIT_ROL, cs_ROL);
	std::string std_ROL(CW2A(cs_ROL.GetString()));
	if (std_ROL == "") {
		std_ROL = "0";
	}
	bitROL = stoi(std_ROL);

	QInt temp;
	QInt rol = temp.rol(qIntNum5, bitROL); //Kết quả phép ROL
	string s_ROL;
	switch (coeff3) {
	case 0: {
		s_ROL = temp.PrintQInt(rol);
	} break;

	case 1: {
		s_ROL = temp.DecToBin(rol);
	} break;

	case 2: {
		s_ROL = temp.BinToHex(temp.DecToBin(rol));
	} break;
	}
	//string s_ROL = temp.PrintQInt(rol);
	CString cs_resultROL(s_ROL.c_str());
	SetDlgItemText(IDC_RESULT_ROL, cs_resultROL);
}


void CMFCNumberConverterDlg::OnEnChangeBitRor()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	CString cs_ROR;
	GetDlgItemText(IDC_BIT_ROR, cs_ROR);
	std::string std_ROR(CW2A(cs_ROR.GetString()));
	if (std_ROR == "") {
		std_ROR = "0";
	}
	bitROR = stoi(std_ROR);

	QInt temp;
	QInt ror = temp.ror(qIntNum5, bitROR); //Kết quả phép ROR
	string s_ROR;
	switch (coeff3) {
	case 0: {
		s_ROR = temp.PrintQInt(ror);
	} break;

	case 1: {
		s_ROR = temp.DecToBin(ror);
	} break;

	case 2: {
		s_ROR = temp.BinToHex(temp.DecToBin(ror));
	} break;
	}
	//string s_ROR = temp.PrintQInt(ror);
	CString cs_resultROR(s_ROR.c_str());
	SetDlgItemText(IDC_RESULT_ROR, cs_resultROR);
}


void CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent1() //Khi ấn vào chọn ComboBox thì hàm này sẽ chạy
{
	// TODO: Add your control notification handler code here
	coeff1 = IDC_SELECT_COEFFICIENT_1.GetCurSel(); //Lấy giá trị của Combo box 1, là lựa chọn hệ số
}

void CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent2()
{
	// TODO: Add your control notification handler code here
	coeff2 = IDC_SELECT_COEFFICIENT_2.GetCurSel();
}

void CMFCNumberConverterDlg::OnCbnSelchangeSelectCoefficent3()
{
	// TODO: Add your control notification handler code here
	coeff3 = IDC_SELECT_COEFFICIENT_3.GetCurSel();
}
