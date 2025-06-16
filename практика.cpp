#include <iostream>
#include <string>
#include <vector>
using namespace std;
//3.	Уфологи обнаружили на некоторой местности K точек посадки НЛО. Так как всем известно, что инопланетяне очень любят 
//треугольники, вам была поставлена задача найти треугольник с самой меньшей площадью, который только можно из них построить,
//  определить его геометрический центр и провести от него линию к 
//самой удаленной от него точке посадки НЛО. Узнав длину этой линии человечество получит шанс узнать хоть что-нибудь о наших братьях по разуму.

float square(pair<int, int> x, pair<int, int> y, pair<int, int> z) {
	float x1 = fabs(sqrt(pow(x.first-y.first, 2)+ pow(x.second - y.second, 2)));
	float y1 = fabs(sqrt(pow(x.first - z.first, 2) + pow(x.second - z.second, 2)));
	float z1 = fabs(sqrt(pow(z.first - y.first, 2) + pow(z.second - y.second, 2)));
	float p = (x1 + y1 + z1) / 2;
	float S = sqrt(p*(p-z1)*(p-x1)*(p-y1));
	return S;
}

pair<int, int> 

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int choice;
	while (true) {
		cout << "Меню:\n1 - Ввести количество точек НЛО;\n2 - Выйти из программы.\nВвод: ";
		cin >> choice;
	switch (choice)
	{
		case 1:
		{
			vector<pair<int,int>> Coord;
			vector<pair<int, int>> sides;
			float Square = 0;
			int dots = 0;
			do { cout << "Введите количество точек НЛО от 3 до 100: "; cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin >> dots; } while (cin.fail() || dots < 3);
			for (int i = 0; i < dots;i++) 
				Coord.push_back({ rand() % 201 - 100, rand() % 201 - 100});
			for (int i = 0; i < Coord.size(); i++) {
				for (int j = i+1; j < Coord.size(); j++) {
					for (int z = j+1; z < Coord.size(); z++) {
						if ((Square > square(Coord[i], Coord[j], Coord[z]) && Coord[i]!= Coord[j] && Coord[z] != Coord[j] && Coord[i]!= Coord[z]) || Square == 0) {
							Square = square(Coord[i], Coord[j], Coord[z]);
							sides.clear();
							sides.push_back(Coord[i]); sides.push_back(Coord[j]); sides.push_back(Coord[z]);
						}
					}
				}
				cout << "Точка " << i + 1 << " с координатами: (" << Coord[i].first << ", " << Coord[i].second << ")" << endl;
			}
			cout << "Наименьшая площадь = " << Square << endl;
			cout << "Координаты наименьшего треугольника (" << sides[0].first <<", "<< sides[0].second << "), (" << sides[1].first << ", " << sides[1].second << "), (" << sides[2].first << ", " << sides[2].second << ")" << endl;
			break;
		}
		case 2: cout << "Выход из программы."; exit(1);
		default:
			cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Недопустимый ввод. Введите заново. ";
	}
}
}