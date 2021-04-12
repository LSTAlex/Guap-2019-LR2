#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;
struct Elem
{
	int value; // переменная хранящая значение элемента
	Elem* next; // указатель на следующий элемент списка
};
struct List
{
	Elem* begin; // указатель на начало списка 
	Elem* end; // указатель на конец списка 
	List()
	{
		// присваиваем указзателям значение
		begin = NULL;
		end = NULL;
	}
};
void Addelem(List* list, int value) // добавление элемента в список
{
	Elem* newelem = new Elem; // здесь new это создание переменной типа Elem  
	newelem->value = value; // присваиваем переменной значение value
	newelem->next = NULL;
	// указатель на следующий элемент теперь смотрит на NULL
		if (list->end != NULL) // проверка если указатель на конец списка не равен NULL,то
		{
		list->end->next = newelem; // передвигаем указатель на newelem
		}
	list->end = newelem;
	if (list->begin == NULL) //проверка если указатель на начало списка не равен NULL,то
	{
	list->begin = newelem; // указатель на начала списка будет сдвинут на newelem
	}
}
void print(List* list) // функция для печати списка 
{
	for (Elem* p = list->begin; p != NULL; p = p->next) // выводим элементы начиная от
		//указателя на начало списка до того момента пока p = NULL
	{
		cout << p->value << "->";
	}
	cout << "Null\n";
}
void removefirst(List* list) // функция для удаления первого элемента списка
{
	Elem* tmp; // создание буферной переменной типа Elem 
	if (list->end == NULL) //проверка если указательна на конец списка ссылается на NULL, то
	{
		return; // выходим 
	}
	tmp = list->begin->next; //переменной-буферу присваиваем значение следубщего элемента
	delete list->begin; // удаляем указатель на начало списка 
	list->begin = tmp; // присваиваем указатель начала списка переменной записанной до этого в tmp
}
int input(List* list)
{
	int n, x;
	cout << "Введите колличество элементов списка: ";
	cin >> n;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		//cin >> x; // для ручного ввода 
		x = rand() % 10; // рандомная генерация элементов списка
		Addelem(list, x);
	}
	return n;
}
struct VC
{
	int value;
	int count;
};
void sort(int* a, int n);
void sort(VC* vc, int n);
void printmenu();
int main()
{
	setlocale(LC_ALL, "Russian");
	int choise = 0;
	int index = 0;
	List A;
	List B;
	int n = input(&A);
	print(&A);
	int* a = new int[n];
	// Create array from list A
	int i = 0;
	for (Elem* p = A.begin; p != NULL; p = p->next)
	{
		a[i++] = p->value;
	}
	sort(a, n);
	VC* vc = new VC[n];
	do
	{
		cout << "Введите номер пункта меню: " << endl;
		printmenu();
		cin >> choise;
		switch (choise)
		{
		case 1:
		{

			for (int i = 0; i < n; i++)
			{
				int v = a[i];
				int c = 1;
				while (i < n - 1 && a[i + 1] == v)
				{
					i++;
					c++;
				}
				if (c > 1)
				{
					vc[index].value = v;
					vc[index].count = c;
					index++;
				}
			}
			// Create result list2 
			for (int i = 0; i < index; i++)
			{
				Addelem(&B, vc[i].value);
			}
			print(&B);
			// Sort vc array by count decrease 
			sort(vc, index);
		}
		case 2:
		{
			//Удаление элементов списка 
			while (A.begin != NULL)
				removefirst(&A);
			while (B.begin != NULL)
				removefirst(&B);
		}
		case 9:break;
		}
	} while (choise != 9);
	// Free memory 
	delete[]a;
	delete[]vc;
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
void sort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] > a[j])
			{
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
}
void sort(VC* vc, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (vc[i].count < vc[j].count)
			{
				VC tmp = vc[i];
				vc[i] = vc[j];
				vc[j] = tmp;
			}
}
void printmenu()
{
	cout << "1.Выполнить задание данное в варианте №1" << endl;
	cout << "2.Очистить список" << endl;
	cout << "9.Выход" << endl;

}