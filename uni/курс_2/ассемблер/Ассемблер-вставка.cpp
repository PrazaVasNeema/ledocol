#include <iostream>

using namespace std;
/*
void  main(){
	short A, B;
	cin >> A >> B;
	_asm {
		MOV Ax, A
		MOV Bx, B
		MOV Dx, 1
		L1: add Ax, A
			add Dx, 1
			CMP Dx, Bx
			JL L1
			MOV A, Ax
	}
	cout << A << endl;
	system("pause");
}
*/

void  main() {
	short x[5], N = 5;
	for (int i = 0; i < N; i++)
		cin >> x[i];
	for (int i = 0; i < N; i++)
		cout << x[i] << '\t';
	cout << endl;
	_asm {
		mov ecx, 0
		mov cx, N
		mov ebx, 0
		dec cx
		L_BEG :
		push cx
			mov edi, 0
			mov esi, 2
			L_BODY0 :
			mov ax, x[edi]
			cmp ax, x[esi]
			JL L_BODY1
			push    x[esi]
			push    x[edi]
			pop    x[esi]
			pop    x[edi]
			L_BODY1:
		add edi, 2
			add esi, 2
			loop L_BODY0
			pop cx
			add ebx, 2
			loop L_BEG
	}
	for (int i = 0; i < N; i++)
		cout << x[i] << '\t';
	cout << endl;
	system("pause");
}