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
		return "Zwierzak jest glodny";
	}
} petHungryException;

class PetIsNotMyFriend : public exception
{
	virtual const char* what() const throw()
	{
		return "sory, to nie moj przyjaciel";
	}
} petIsNotMyFriend;

class Animal
{
private:
	int UID;
	queue<std::string> foodBuffer;
	string name;
protected:
	float distanceTraveled;
public:
	Animal(const string& aName)
	{
		name = aName;
		UID = NEXT_ID;
		distanceTraveled = 0;
		printf("Masz nowe zwierze o UID %d\n", UID);
	}

	virtual ~Animal()
	{
		printf("Zginelo zwierze o UID %d\n", UID);
	}

	const string getName()
	{
		return name;
	}

	template<typename T>
	void travel(T aDystans)
	{
		distanceTraveled += aDystans;
	}

	void feed(const string& food)
	{
		foodBuffer.push(food);
	}

	string poo()
	{
		if (foodBuffer.size() == 0)
			throw petHungryException;

		string ans = foodBuffer.front();
		foodBuffer.pop();
		return ans;
	}

	const string getType()
	{
		string subans = typeid(*this).name();
		return subans.substr(6);
	}

	virtual const string growl() = 0;
};

class Dog : public Animal
{
	friend class Human;
public:
	Dog(const string& aImie) : Animal(aImie)
	{
		cout << "To piesek " + aImie + "!\n\n";
	}

	virtual const string growl()
	{
		return "hau hau";
	}
};

class Cat : public Animal
{
public:
	Cat(const string& aName) : Animal(aName)
	{
		cout << "To kotek " + aName + "!\n\n";
	}

	virtual const string growl()
	{
		return "miau";
	}
};

class Human
{
	Animal* pet;
public:
	void setPet(Animal* aPet)
	{
		pet = aPet;
	}

	float getPetDistanceTraveled()
	{
		if (Dog* aDog = dynamic_cast<Dog*>(pet))
			return aDog->distanceTraveled;
		else
			throw petIsNotMyFriend;
	}
};

int main()
{
	Human czarek;
	Animal* zwierzakistat[2];
	Animal* zwierz;
	Animal** zwierzakidyn;
	zwierzakidyn = new Animal*[2];
	zwierzakidyn[0] = new Dog("Leszek");
	zwierzakidyn[1] = new Cat("Filemon");

	cout << "\n";

	for (int i = 0; i < 2; i++)
		cout << zwierzakidyn[i]->getType() << " robi " << zwierzakidyn[i]->growl() << endl;

	cout << "\n";

	cout << "Karmie " + zwierzakidyn[0]->getType() + " mieskiem!" << endl;
	zwierzakidyn[0]->feed("miesko");

	while (true)
	{
		try
		{
			cout << "Piesek wyproznil " + zwierzakidyn[0]->poo() << endl;
		}
		catch (exception& e)
		{
			cout << "Blad! " << e.what() << endl;
			break;
		}
	}

	cout << "\nSPACEREK\n";	
	zwierzakidyn[0]->travel(20);
	zwierzakidyn[1]->travel(0.7f);
	
	Animal* aZwierzaczek;

	for (int i = 0; i < 2; i++)
	{
		aZwierzaczek = zwierzakidyn[i];
		czarek.setPet(aZwierzaczek);
		try
		{
			printf("%s przebiegl %f\n\n", aZwierzaczek->getName().c_str(), czarek.getPetDistanceTraveled());
		}
		catch (exception& e)
		{
			printf("Nie wiem ile przebiegl %s\n", aZwierzaczek->getName().c_str());
			cout << "Blad! " << e.what() << endl << endl;
		}
	}

	for (int i = 0; i < 2; i++)
		printf("%d : %s %s\n", i, zwierzakidyn[i]->getType().c_str(), zwierzakidyn[i]->getName().c_str());

	cout << "\n Sortowanko z lambda po imionach\n\n";

	sort(zwierzakidyn, zwierzakidyn + 2,
		[](Animal* a, Animal* b) -> bool {return a->getName() < b->getName(); }
	);

	for (int i = 0; i < 2; i++)
		cout << i << " : " << zwierzakidyn[i]->getType() << " " << zwierzakidyn[i]->getName() << endl;
	cout << endl;

	for (int i = 0; i < 2; i++)
		delete zwierzakidyn[i];
	delete[] zwierzakidyn;

	cout << "\nDziekuje za pokaz\n\n";

	system("pause");
	return 0;
}

