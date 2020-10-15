//�E�B���h�E�ɕ�����`��

#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//�V���{��
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//�C���X�^���X
HINSTANCE hInst;

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	static TCHAR szWindowClass[] = _T("Sample02");
	static TCHAR szTitle[] = _T("�E�B���h�E�T���v��");

	WNDCLASSEX wcex;

	//�E�B���h�E�̊T�v��ݒ肷��
	wcex.cbSize = sizeof(WNDCLASSEX);											//�\���̂̃T�C�Y
	wcex.style = CS_HREDRAW | CS_VREDRAW;										//�N���X�̃X�^�C��
	wcex.lpfnWndProc = WndProc;													//�E�B���h�E�v���V�[�W��
	wcex.cbClsExtra = 0;														//�⏕������
	wcex.cbWndExtra = 0;														//�⏕������
	wcex.hInstance = hInstance;													//�C���X�^���X�n���h��
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));			//�A�C�R��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);									//�J�[�\��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);							//�w�i�u���V
	wcex.lpszMenuName = NULL;													//���j���[��
	wcex.lpszClassName = szWindowClass;											//�N���X��
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//�������A�C�R��

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("RegisterClassEx�̏����Ɏ��s���܂���"), _T("Sample02"), NULL);

		return 1;
	}

	//�O���[�o���ϐ��ɒl������
	hInst = hInstance;

	//�E�B���h�E�̐���
	HWND hWnd = CreateWindow(
		szWindowClass,                  // �A�v���P�[�V�����̖��O
		szTitle,                        // �^�C�g���o�[�Ɍ���镶����
		WS_OVERLAPPEDWINDOW,            // ��������E�B���h�E�̃^�C�v�i�I�[�o�[���b�v�E�B���h�E�j
		CW_USEDEFAULT, CW_USEDEFAULT,	// �ŏ��ɒu���|�W�V���� (x, y)
		WINDOW_WIDTH, WINDOW_HEIGHT,    // �ŏ��̃T�C�Y (��, ����)
		NULL,                           // ���̃E�B���h�E�̐e�E�B���h�E�̃|�C���^
		NULL,                           // ���j���[�o�[
		hInstance,                      // �A�v���P�[�V�����C���X�^���X�̃n���h��(WinMain�֐��̍ŏ��̃p�����[�^)
		NULL                            // WM_CREATE���
	);

	//�E�B���h�E�̐����Ɏ��s�����ꍇ
	if (!hWnd) {
		MessageBox(NULL, _T("�E�B���h�E�̐����Ɏ��s"), _T("Sample02"), NULL);

		return 1;
	}

	//�E�B���h�E�ɕK�v�ȃp�����[�^
	// hWnd     : CreateWindow�̖߂�l
	// nCmdShow : WinMain�̈�����4�Ԗ�
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���C���̃��b�Z�[�W���[�v:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��(���b�Z�[�W�����������p���[�`��)
//�R�[���o�b�N�֐�:���炩�̃C�x���g���N�������ꍇ�A�O������Ăяo��������Ȋ֐�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World");

	switch (message) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps); //�`�揈���̊J�n
			//������̏o��
			TextOut(
				hdc,				//�f�o�C�X�R���e�L�X�g�̃n���h��
				5,					//�J�n�ʒu��x���W
				5,					//�J�n�ʒu��y���W
				greeting,			//������
				_tcslen(greeting)	//������
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