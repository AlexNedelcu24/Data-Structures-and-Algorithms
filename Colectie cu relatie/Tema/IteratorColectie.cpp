#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
}

TElem IteratorColectie::element() const {
	return col.e[curent];
}

TElem IteratorColectie::frecventa() const {
	return col.frv[curent];
}

bool IteratorColectie::valid() const {
	return curent < col.lg;
}

void IteratorColectie::urmator() {
	curent++;
}

void IteratorColectie::prim() {
	curent = 0;
}