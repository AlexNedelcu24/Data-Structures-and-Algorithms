#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 > e2)
	    return false;
	return true;
}

void Colectie::redim() {
	TElem* eNou = new int[2 * cp];
	TElem* frvNou = new int[2 * cp];

	for (int i = 0; i < lg; i++) {
		eNou[i] = e[i];
		frvNou[i] = frv[i];
	}

	cp = 2 * cp;

	delete[] e;
	delete[] frv;

	e = eNou;
	frv = frvNou;
}

Colectie::Colectie() {
	this->cp = 1;
	e = new TElem[cp];
	frv = new TElem[cp];
	this->lg = 0;
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = n = ?(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = ?(n)

--Complexitatea: O(n)
*/
void Colectie::adauga(TElem elem) {
	bool ultim = true;

	if (cauta(elem) == false && lg == cp)
		redim();

	if (cauta(elem) == true)
		for (int i = 0; i < lg; i++)
		{
            if (elem == e[i])
				 frv[i]++;
		}
	else
	{
		for (int i = 0; i < lg; i++)
		{
			if (rel(elem, e[i]))
			{
				lg++;
				for (int j = lg - 1; j > i; j--)
				{
					e[j] = e[j - 1];
					frv[j] = frv[j - 1];
				}
					
				e[i] = elem;
				frv[i] = 1;
				ultim = false;
				break;
			}
		}
    if (ultim == true) {
	    	frv[lg] = 1;
		    e[lg] = elem;
		    lg++;
	}	
	}
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = logn = ?(logn)

-caz mediu:
T(n) = (1+2+..+logn)/logn = ?(logn)

--Complexitatea: O(logn)
*/
bool Colectie::sterge(TElem elem) {
	int st = 0, dr = lg - 1;
	while (dr >= st)
	{
		int mid = (st + dr) / 2;
		if (elem == e[mid])
		{
			frv[mid]--;
			if (frv[mid] == 0) {
				lg--;
				for (int j = mid; j < lg; j++)
				{
					e[j] = e[j + 1];
					frv[j] = frv[j + 1];
				}
			}
			return true;
		}
		if (rel(e[mid], elem)) st = mid + 1;
		else dr = mid - 1;
	}
	return false;
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = logn = ?(logn)

-caz mediu:
T(n) =  (1+2+..+logn)/logn = ?(logn)

--Complexitatea: O(logn)
*/
bool Colectie::cauta(TElem elem) const {

	int st=0, dr=lg-1;
	while (dr >= st)
	{
		int mid = (st + dr) / 2;
		if (e[mid] == elem) return true;
		if (rel(e[mid], elem)) st = mid+1;
		else dr = mid-1;
	}
	return false;
}

/*
-caz favorabil:
T(n) = 1 = ?(1)

-caz defavorabil:
T(n) = n = ?(n)

-caz mediu:
T(n) = 1/n * (1+2+..+n) = n*(n+1)/2*n = (n+1)/2 = ?(n)

--Complexitatea: O(n)
*/
int Colectie::nrAparitii(TElem elem) const {
	int aparitii = 0;
	for (int i = 0; i < lg; i++)
	{
		if (e[i] == elem)
		{
			return frv[i];
		}
	}
	return 0;
}


/*
-caz favorabil:
T(n) = n = ?(n)

-caz defavorabil:
T(n) = n = ?(n)

-caz mediu:
T(n) = ?(n)

--Complexitatea: O(n)
*/
int Colectie::dim() const {
	int len = 0;
	for (int i = 0; i < lg; i++) {
		len += this->frv[i];
	}
	return len;
}


bool Colectie::vida() const {
	if (lg)
		return false;
	else return true;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] e;
	delete[] frv;
}