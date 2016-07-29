#include "stdafx.h"

#include <ctype.h>
#include <exception>
#include <queue>
#include <typeinfo>
#include <iostream>
#include <string>


//Simple ID generator
static int StartingId = 1000;
#define NEXT_ID StartingId++;

using namespace std;

class PetHungryException : public exception
{
	virtual const char* what() const throw()
	{
		return "Piesek jest glodny";
	}
} petHungryException;

class Zwierze
{
private:
	int UID;
	queue<std::string> foodBuffer;
	float dystans;
protected:
public:
	string imie;
	Zwierze(string aImie)
	{
		imie = aImie;
		UID = NEXT_ID;
		printf("Masz nowe zwierze o UID %d\n", UID);
	}

	virtual ~Zwierze()
	{
		printf("Zabiles zwierze o UID %d\n", UID);
	}

	template<typename T>
	void biegnij(T aDystans)
	{
		dystans += aDystans;
	}

	void nakarm(std::string papu)
	{
		foodBuffer.push(papu);
	}

	string kupka()
	{
		if (foodBuffer.size() == 0)
			throw petHungryException;

		string ans = foodBuffer.front();
		foodBuffer.pop();
		return ans;
	}

	string nazwa()
	{
		string subans = typeid(*this).name();
		return subans.substr(6);
	}

	virtual string dajGlos() = 0;
};

class Piesek : public Zwierze
{
public:
	Piesek(string aImie) : Zwierze(aImie)
	{
		cout << "To piesek " + aImie + "!\n\n";
	}

	virtual string dajGlos()
	{
		return "hau hau";
	}
};

class Kotek : public Zwierze
{
public:
	Kotek(string aImie) : Zwierze(aImie)
	{
		cout << "To kotek " + aImie + "!\n\n";
	}

	virtual string dajGlos()
	{
		return "mial";
	}
};

int main()
{
	Zwierze* zwierzakistat[2];
	Zwierze* zwierz;
	Zwierze** zwierzakidyn;
	zwierzakidyn = new Zwierze*[2];
	zwierzakidyn[0] = new Piesek("Leszek");
	zwierzakidyn[1] = new Kotek("Filemon");

	cout << "\n";

	for (int i = 0; i < 2; i++)
		cout << zwierzakidyn[i]->nazwa() << " robi " << zwierzakidyn[i]->dajGlos() << endl;

	cout << "\n";

	cout << "Karmie " + zwierzakidyn[0]->nazwa() + " mieskiem!" << endl;
	zwierzakidyn[0]->nakarm("miesko");

	while (true)
	{
		try
		{
			cout << "Piesek wyproznil " + zwierzakidyn[0]->kupka() << endl;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
			break;
		}

	}

	cout << "\n";

	for (int i = 0; i < 2; i++)
		printf("%d : %s %s\n", i, zwierzakidyn[i]->nazwa().c_str(), zwierzakidyn[i]->imie.c_str());

	cout << "\n Sortowanko z lambda po imionach\n\n";


	sort(zwierzakidyn, zwierzakidyn + 2,
		[](const Zwierze* a, const Zwierze* b) -> bool {return a->imie < b->imie; }
	);

	for (int i = 0; i < 2; i++)
		cout << i << " : " << zwierzakidyn[i]->nazwa() << " " << zwierzakidyn[i]->imie << endl;
	cout << endl;

	for (int i = 0; i < 2; i++)
		delete zwierzakidyn[i];
	delete[] zwierzakidyn;


	cout << "\n";
	cout << "Dziekuje za pokaz";

	system("pause");
	return 0;
}

