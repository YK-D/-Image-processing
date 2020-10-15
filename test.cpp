// ダイアログを表示するサンプル

#define STRICT
#include <windows.h>
#include <tchar.h>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	MessageBox(NULL, _T("処理の成功"), _T("情報"), MB_OK /*| MB_ICONINFORMATION*/);

	return 0;
}