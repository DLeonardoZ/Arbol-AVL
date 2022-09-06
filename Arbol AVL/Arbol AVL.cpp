#include <iostream>

using namespace std;

struct Nodo {
	int data;
	Nodo* der;
	Nodo* izq;
};

//Identificadores
Nodo* crearNodo(int);
void push(Nodo*&, int);
void view(Nodo*, int);
void menu();

class arbolAVL {
	int altura(Nodo*);
	int diferencia(Nodo*);
	Nodo* bal(Nodo*);
	Nodo* rr(Nodo*);
	Nodo* ll(Nodo*);
	Nodo* lr(Nodo*);
	Nodo* rl(Nodo*);
};

Nodo* arbol = NULL;

int main() {
	menu();
	return 0;
}

int altura(Nodo* arbol) {
	int h = 0;
	if (arbol != NULL) {
		int lh = altura(arbol->izq);
		int rh = altura(arbol->der);
		int maxh = max(lh, rh);
		h = maxh + 1;
	}
	return h;
}

int diferencia(Nodo* arbol) {
	int lh = altura(arbol->izq);
	int rh = altura(arbol->der);
	int factor = lh - rh;
	return factor;
}

void view(Nodo* arbol, int cont) {
	if (arbol == NULL) {
		return;
	}
	else {
		view(arbol->der, cont + 1);
		for (int it = 0; it < cont; it++) {
			cout << "   ";
		}
		cout << arbol->data << endl;
		view(arbol->izq, cont + 1);
	}
}

void menu() {
	int v = 0, op = 0, cont = 0;
	do {
		cout << "------------ Menu ------------" << endl;
		cout << "0-. Salir del programa" << endl;
		cout << "1-. Insertar nuevo nodo" << endl;
		cout << "2-. Imprimir arbol" << endl;
		cout << "------------------------------" << endl;
		cout << "-. "; cin >> op;
		cout << "------------------------------" << endl;

		switch (op) {
		case 0:
			break;
		case 1:
			cout << "-. Ingrese un numero: ";
			cin >> v; push(arbol, v);
			cout << "------------------------------" << endl;
			break;
		case 2:
			cout << "Arbol actual:" << endl;
			cout << "------------------------------" << endl;
			view(arbol, cont);
			cout << endl;
			system("pause");
			break;

		default:
			cout << "-. Opcion no disponible" << endl;
			cout << "------------------------------" << endl;
			system("pause");
			break;
		}
		system("cls");
	} while (op != 0);
}

Nodo* rr(Nodo* parent) {
	Nodo* arbol;

	arbol = parent->der;
	parent->der = arbol->izq;
	arbol->izq = parent;

	cout << "Rotacion RR";
	return arbol;
}

Nodo* ll(Nodo* parent) {
	Nodo* arbol;

	arbol = parent->izq;
	parent->izq = arbol->der;
	arbol->der = parent;

	cout << "Rotacion LL";
	return arbol;
}

Nodo* lr(Nodo* parent) {
	Nodo* arbol;

	arbol = parent->izq;
	parent->izq = rr(arbol);

	cout << "Rotacion LR";
	return ll(parent);
}

Nodo* rl(Nodo* parent) {
	Nodo* arbol;

	arbol = parent->der;
	parent->der = ll(arbol);

	cout << "Rotacion RL";
	return rr(parent);
}

Nodo* bal(Nodo* arbol) {
	int factor = diferencia(arbol);

	if (factor > 1) {
		if (diferencia(arbol->izq) > 0) {
			arbol = ll(arbol);
		}
		else {
			arbol = lr(arbol);
		}
	}
	else if (factor < -1) {
		if (diferencia(arbol->der) > 0) {
			arbol = rl(arbol);
		}
		else {
			arbol = rr(arbol);
		}
	}
	return arbol;
}

void push(Nodo*& arbol, int n) {
	if (arbol == NULL) {
		cout << "Nodo vacio.. creando..." << endl;
		system("pause");

		Nodo* nuevoNodo = crearNodo(n);
		arbol = nuevoNodo;
	}
	else {
		int root = arbol->data;
		if (n < root) {
			cout << "izquierda.." << endl;
			push(arbol->izq, n);
			arbol = bal(arbol);
		}
		else {
			cout << "derecha..." << endl;
			push(arbol->der, n);
			arbol = bal(arbol);
		}
	}
}

Nodo* crearNodo(int n) {
	Nodo* nuevoNodo = new Nodo();
	nuevoNodo->data = n;
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	return nuevoNodo;
}