#include <iostream>

using namespace std;

class AdjNode //pojedynczy wezel, komorka w tablicy, pojedyncza lista dla danego wezla
{
private:
	int nodeNo; //numer wezla
	AdjNode* next; //wskazuje na kolejny wezel
public:
	AdjNode(); //konstruktor, ktory tworzy pusty wezel
	AdjNode(int u, AdjNode* n); //konstruktor, ktory tworzy wezel u i ustawia jego nastepnika
	int GetNode(); //zwraca numer wezla
	AdjNode* GetNext(); //zwraca nastepnika wezla
	void insertAdjNode(int u); //wstawia wezel u
	void deleteAdjNode(int u); //usuwa wezel u
	friend ostream& operator<<(ostream& out, AdjNode* node); //wyswietla na ekranie wszystkie wezel, czyli dopoki next nie bedzie nullem, od pewnego momentu do konca
};

AdjNode::AdjNode()
{
	nodeNo = -1;
	next = NULL;
}

AdjNode::AdjNode(int u, AdjNode* n)
{
	this->nodeNo = u; //this to wskaznik na obecny obiekt
	this->next = n;
}

int AdjNode::GetNode()
{
	return nodeNo;
}

AdjNode* AdjNode::GetNext()
{
	return next;
}

void AdjNode::insertAdjNode(int u)
{
	if (u < 0) //nie chcemy wstawiac ujemnych wezlow
		return;
	//AdjNode* head = new AdjNode(u, NULL); //jakbym chciala utworzyc nowego heada
	if (this == NULL) //this czyli head
	{
		return;
	}
	AdjNode* head =this; //wskazuje na ten obiekt
	if (head->next== NULL) //bo wszystko tu jest widoczne, wiec nie potrzebuje metod, metody sa do drugiej klasy
	{
		AdjNode* newNode = new AdjNode(u, NULL); //tworze nowy wezel
		head->next = newNode;
		return;
	}
	else
	{
		AdjNode* temp = head;
		AdjNode* tempPrev = NULL;
		if (head->nodeNo == u)
		{
			return;
		}
		while (temp->next->nodeNo <= u)
		{
			if (temp->next->nodeNo == u)
			{
				return;
			}
			tempPrev = temp; //poprzednikiem bedzie ten, w ktorym jestem, bo w nastepnej linii sie przesuwam
			temp = temp->next;
			if (temp->next == NULL)
			{
				AdjNode* newNode = new AdjNode(u, NULL);
				temp->next = newNode;
			}
		}
		AdjNode* newNode = new AdjNode(u, temp);
		if (tempPrev != NULL)
		{
			tempPrev->next = newNode;
		}
	}
}

void AdjNode::deleteAdjNode(int u)
{
	if (next == NULL)
	{
		return;
	}
	AdjNode* temp = next;
	AdjNode* tempPrev = this;
	while (temp->nodeNo != u)
	{
		tempPrev = temp;
		temp = temp->next;
		if (temp == NULL) //jak dojde do ostatniego to go nie ma, czyli nie ma co usuwac
		{
			return;
		}
	}
	tempPrev->next = temp->next;
	delete temp;
}

ostream& operator<<(ostream& out, AdjNode* node) 
{
	if (node == NULL)
		return out;

	AdjNode* temp = node->GetNext();
	out << node->GetNode() << ": ";
	bool lolz1337 = true;
	while (temp != NULL) 
	{
		if (!lolz1337)
			out << ", ";
		out << temp->GetNode();
		temp = temp->GetNext();
		lolz1337 = false;
	}
	return out;
}

class AdjList //tablica list jednokierunkowych
{
private:
	AdjNode** nodes; //dwie gwiazdki, bo AdjNode* to typ i druga gwiazda to znaczy, ze tworzymy tablice jednowymiarowa
	int amountOfNodes; //liczba wezlow calego grafu
public:
	AdjList(); //konstruktor, tworzy pusta liste sasiedztwa
	AdjList(int c); //konstruktor, tworzy liste sasiedztwa o rozmiarze c
	void insertAdjNode(int primeNode, int secNode); //korzysta z inserta z klasy adjnode, primenode to nodeno
	void deleteAdjNode(int primeNode, int secNode); //korzysta z delete z klasy adjnode
	friend ostream& operator<<(ostream& out, AdjList* graph); //wyswietla liste sasiedztwa
};

AdjList::AdjList() //konstruktor domyslny
{
	nodes = NULL;
	amountOfNodes = 0;
}

AdjList::AdjList(int c)
{
	nodes = new AdjNode * [c];
	amountOfNodes = c; //robie tablice wskaznikow
	for (int i = 0; i < amountOfNodes; i++)
	{
		nodes[i] = new AdjNode(i, NULL);
	}
}

void AdjList::insertAdjNode(int primeNode, int secNode)
{
	nodes[primeNode]->insertAdjNode(secNode); //to nie ta metoda w sensie, to metoda z klasy adjnode
}

void AdjList::deleteAdjNode(int primeNode, int secNode)
{
	nodes[primeNode]->deleteAdjNode(secNode);
}

ostream& operator<<(ostream& out, AdjList* graph)
{
	for (int i = 0; i < graph->amountOfNodes; i++)
	{
		out << graph->nodes[i] << endl;
	}
	return out;
}

int main()
{
	/**AdjNode* newNode = new AdjNode(1, NULL);
	newNode->insertAdjNode(2);
	newNode->insertAdjNode(4); //kolejnosc naprawic!!!!!!!!!
	newNode->insertAdjNode(6);
	newNode->insertAdjNode(9);
	newNode->deleteAdjNode(1);
	cout << newNode << endl;**/

	AdjList* lista = new AdjList(5);
	lista->insertAdjNode(0, 2);
	lista->insertAdjNode(0, 4);
	lista->insertAdjNode(1, 2);
	lista->insertAdjNode(1, 3);
	lista->insertAdjNode(3, 4);
	lista->insertAdjNode(4, 1);
	cout << lista << endl;

	return 0;
}