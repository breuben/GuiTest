// GuiTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GuiTest.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
HIMAGELIST hImageList;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HWND CreateToolbarFromResource(HWND hWndParent);

int APIENTRY _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUITEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUITEST));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUITEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
	  return FALSE;
   }

   HWND hWndToolbar = CreateToolbarFromResource(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HWND CreateToolbarFromResource(HWND hWndParent)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_WIN95_CLASSES|ICC_COOL_CLASSES|ICC_BAR_CLASSES|ICC_USEREX_CLASSES;
	InitCommonControlsEx(&icex);

	// Declare and initialize local constants.
	int ImageListID;
	int resourceId = IDB_FILE_VIEW_24;
	int numButtons = 31;
	const int bmHeight = 16;
	const int bmWidth = 16;
	
	const DWORD buttonStylesasdfasdf = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, 
									  WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
									  hWndParent, NULL, hInst, NULL);
	if (hWndToolbar == NULL)
		return NULL;


	resourceId = IDB_TOOLBAR256;

	HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(resourceId));

	// Create the image list.
	int cx = bmWidth;
	int cy = bmHeight;
	UINT nFlags = ILC_COLOR24 | ILC_MASK;
	int nInitial = 0;
	int nGrow = 0;
	hImageList = ImageList_Create(bmWidth, bmHeight, nFlags, 0, nGrow);
	ImageListID = ImageList_AddMasked(hImageList, hBitmap, RGB(0, 255, 0));


	// Set the image list.
	LRESULT r1 = SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)hImageList); 

	// Load the button images.
	//LRESULT r2 = SendMessage(hWndToolbar, TB_LOADIMAGES, 
				//(WPARAM)IDB_STD_SMALL_COLOR, 
				//(LPARAM)HINST_COMMCTRL);
	// Load the text from a resource.
	
	// In the string table, the text for all buttons is a single entry that 
	// appears as "~New~Open~Save~~". The separator character is arbitrary, 
	// but it must appear as the first character of the string. The message 
	// returns the index of the first item, and the items are numbered 
	// consecutively.
	
	int iNew = SendMessage(hWndToolbar, TB_ADDSTRING, (WPARAM)hInst, (LPARAM)0); 
 
	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
	
	::SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	::SendMessage(hWndToolbar, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_HIDECLIPPEDBUTTONS);

	TBBUTTON *pButtons = new TBBUTTON[numButtons];

	for (int i = 0 ; i < numButtons ; i++)
	{
		pButtons[i].iBitmap = i;
		pButtons[i].idCommand = 20 + i;
		pButtons[i].fsState = (BYTE)TBSTATE_ENABLED;
		pButtons[i].fsStyle = (BYTE)TBSTYLE_FLAT;
		pButtons[i].dwData = 0;
		pButtons[i].iString = NULL;
	}

	//typedef struct _TBBUTTON {
	//    int iBitmap;
	//    int idCommand;
	//    BYTE fsState;
	//    BYTE fsStyle;
	//#ifdef _WIN64
	//    BYTE bReserved[6];          // padding for alignment
	//#elif defined(_WIN32)
	//    BYTE bReserved[2];          // padding for alignment
	//#endif
	//    DWORD_PTR dwData;
	//    INT_PTR iString;
	//} TBBUTTON, NEAR* PTBBUTTON, *LPTBBUTTON;

	BOOL b = IsAppThemed();

	// Add buttons.
	LRESULT a1 = SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	LRESULT a2 = SendMessage(hWndToolbar, TB_ADDBUTTONS,       (WPARAM)numButtons,       (LPARAM)pButtons);

	// Resize the toolbar, and then show it.
	LRESULT a3 = SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0); 
	LRESULT a4 = ShowWindow(hWndToolbar,  TRUE);
	return hWndToolbar;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
