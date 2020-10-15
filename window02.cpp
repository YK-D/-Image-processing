//ウィンドウに文字を描画

#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//シンボル
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//インスタンス
HINSTANCE hInst;

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	static TCHAR szWindowClass[] = _T("Sample02");
	static TCHAR szTitle[] = _T("ウィンドウサンプル");

	WNDCLASSEX wcex;

	//ウィンドウの概要を設定する
	wcex.cbSize = sizeof(WNDCLASSEX);											//構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;										//クラスのスタイル
	wcex.lpfnWndProc = WndProc;													//ウィンドウプロシージャ
	wcex.cbClsExtra = 0;														//補助メモリ
	wcex.cbWndExtra = 0;														//補助メモリ
	wcex.hInstance = hInstance;													//インスタンスハンドル
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));			//アイコン
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);									//カーソル
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);							//背景ブラシ
	wcex.lpszMenuName = NULL;													//メニュー名
	wcex.lpszClassName = szWindowClass;											//クラス名
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//小さいアイコン

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("RegisterClassExの処理に失敗しました"), _T("Sample02"), NULL);

		return 1;
	}

	//グローバル変数に値を入れる
	hInst = hInstance;

	//ウィンドウの生成
	HWND hWnd = CreateWindow(
		szWindowClass,                  // アプリケーションの名前
		szTitle,                        // タイトルバーに現れる文字列
		WS_OVERLAPPEDWINDOW,            // 生成するウィンドウのタイプ（オーバーラップウィンドウ）
		CW_USEDEFAULT, CW_USEDEFAULT,	// 最初に置くポジション (x, y)
		WINDOW_WIDTH, WINDOW_HEIGHT,    // 最初のサイズ (幅, 高さ)
		NULL,                           // このウィンドウの親ウィンドウのポインタ
		NULL,                           // メニューバー
		hInstance,                      // アプリケーションインスタンスのハンドル(WinMain関数の最初のパラメータ)
		NULL                            // WM_CREATE情報
	);

	//ウィンドウの生成に失敗した場合
	if (!hWnd) {
		MessageBox(NULL, _T("ウィンドウの生成に失敗"), _T("Sample02"), NULL);

		return 1;
	}

	//ウィンドウに必要なパラメータ
	// hWnd     : CreateWindowの戻り値
	// nCmdShow : WinMainの引数の4番目
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メインのメッセージループ:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//ウィンドウプロシージャ(メッセージを処理する専用ルーチン)
//コールバック関数:何らかのイベントが起こった場合、外部から呼び出される特殊な関数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World");

	switch (message) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps); //描画処理の開始
			//文字列の出力
			TextOut(
				hdc,				//デバイスコンテキストのハンドル
				5,					//開始位置のx座標
				5,					//開始位置のy座標
				greeting,			//文字列
				_tcslen(greeting)	//文字数
			);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}