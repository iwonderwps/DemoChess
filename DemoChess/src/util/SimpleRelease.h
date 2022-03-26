#pragma once

template <class T>
void SimpleRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = 0;
	}
}

template <class T>
void SimpleDelete(T** ppT) {
	if (*ppT) {
		delete (*ppT);
		*ppT = 0;
	}
}

