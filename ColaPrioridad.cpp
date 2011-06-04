#include <iostream.h>
#include <stdlib.h>
#define localizar (struct nodo_cola *) malloc(sizeof(struct nodo_cola))

struct Nodo {
	int dato;
	int prioridad;
	struct Nodo *izquierdo;
	struct Nodo *derecho;
};

struct nodo_cola {
	struct Nodo *info;
	struct nodo_cola *sig;
};

typedef struct Nodo Nodo;
typedef Nodo *NodoPtr;

void insertarNodo(NodoPtr *, int, int);
int retirarNodo(NodoPtr *);
void inOrder(NodoPtr);
void preOrder(NodoPtr);
void postOrder(NodoPtr);
void imprimirArbol(NodoPtr);
void mostrarMenu();

void iniciar(struct nodo_cola **);
void sumar(struct nodo_cola **, Nodo *);
void atender(struct nodo_cola **, Nodo **);
int vacia(struct nodo_cola *);

NodoPtr raiz = NULL;

void main() {
	mostrarMenu();
}

void mostrarMenu() {
	char choice;

	system("cls");
	cout<< "\t\tCola de Prioridad - Camilo Hernando Nova\n" << endl;

	cout<< "1.\tInsertar Elemento." << endl;
	cout<< "2.\tRetirar Elemento." << endl;
	cout<< "3.\tMostrar recorrido inOrder. " << endl;
	cout<< "4.\tMostrar recorrido preOrder." << endl;
	cout<< "5.\tMostrar recorrido posOrder." << endl;
	cout<< "6.\tImprimir Arbol." << endl;
	cout<< "7.\tSalir." << endl;
	cout<< "Digite el numero de su eleccion:\t";

	cin>> choice;

	switch(choice) {
	case '1':
		system("cls");
		int dato, prioridad;

		cout<< "Digite el numero a insertar:\t";
		cin>> dato;
		cout<< "Digite la prioridad del numero:\t";
		cin>> prioridad;
		insertarNodo(&raiz, dato, prioridad);

		mostrarMenu();
		break;
	case '2':
		system("cls");
		cout<< "El numero retirado es:\t" << retirarNodo(&raiz);
		cin.get(); cin.get();

		mostrarMenu();
		break;
	case '3':
		inOrder(raiz);
		system("cls");
		cin.get(); cin.get();

		mostrarMenu();
		break;
	case '4':
		preOrder(raiz);
		system("cls");
		cin.get(); cin.get();

		mostrarMenu();
		break;
	case '5':
		postOrder(raiz);
		system("cls");
		cin.get(); cin.get();

		mostrarMenu();
		break;
	case '6':
		imprimirArbol(raiz);
		system("cls");
		cin.get(); cin.get();

		mostrarMenu();
		break;
	case '7':
		exit(0);
		break;
	default:
		mostrarMenu();
		break;
	}
}

void insertarNodo(NodoPtr *raiz, int valor, int prioridad) {
	if(*raiz == NULL) {
		*raiz = (Nodo *) malloc(sizeof(Nodo));

		if(*raiz != NULL) {
			(*raiz)->dato = valor;
			(*raiz)->prioridad = prioridad;
			(*raiz)->derecho = NULL;
			(*raiz)->izquierdo = NULL;
		}
		else
			cout<< "\nMemoria no disponible...";
	}
	else
		if(prioridad < (*raiz)->prioridad)
			insertarNodo(&((*raiz)->izquierdo), valor, prioridad);
		else
			if(prioridad > (*raiz)->prioridad)
				insertarNodo(&((*raiz)->derecho), valor, prioridad);
}

int retirarNodo(NodoPtr *raiz) {
	int valor;
	if(*raiz != NULL) {
		valor = (*raiz)->dato;
		// Retirar nodos
	
		return valor;
	}
	return -1;
}

void inOrder(NodoPtr raizPtr) {
	if(raizPtr != NULL) {
		inOrder(raizPtr->izquierdo);
		cout<< raizPtr->dato << "," << raizPtr->prioridad << " ";
		inOrder(raizPtr->derecho);
	}
}

void preOrder(NodoPtr raizPtr) {
	if(raizPtr != NULL) {
		cout<< raizPtr->dato << "," << raizPtr->prioridad << " ";
		preOrder(raizPtr->izquierdo);
		preOrder(raizPtr->derecho);
	}
}

void postOrder(NodoPtr raizPtr) {
	if(raizPtr != NULL) {
		postOrder(raizPtr->izquierdo);
		postOrder(raizPtr->derecho);
		cout<< raizPtr->dato << "," << raizPtr->prioridad << " ";
	}
}

void imprimirArbol(NodoPtr p) {
	struct nodo_cola *cab;

	if(p == NULL)
		return;

	if(p) {
		iniciar(&cab);
		sumar(&cab, p);
	}
	while(!vacia(cab)) {
		atender(&cab, &p);
		cout<< p->dato << "," << p->prioridad << " ";
		if(p->izquierdo)
			sumar(&cab, p->izquierdo);
		if(p->derecho)
			sumar(&cab, p->derecho);
	}
}

void iniciar(struct nodo_cola **p) {
	*p = localizar;
	(*p)->sig = *p;
}

void sumar(struct nodo_cola **p, Nodo *objeto) {
	struct nodo_cola *nuevo;

	nuevo = localizar;
	nuevo->info = objeto;
	nuevo->sig = (*p)->sig;
	(*p)->sig = nuevo;
	*p = nuevo;
}

void atender(struct nodo_cola **p, Nodo **s) {
	struct nodo_cola *q, *r;

	if(*p == (*p)->sig) {
		cout<< "No hay objetos" << endl;
		(*s)->dato = '#';
	}
	else {
		q = (*p)->sig;
		r = q->sig;
		*s = r->info;
		q->sig = r->sig;
		if(q == q->sig)
			*p = q;
		free(r);
	}
}

int vacia(struct nodo_cola *p) {
	return (p == p->sig);
}