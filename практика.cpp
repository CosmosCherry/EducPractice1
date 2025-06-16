#include <iostream>
#include <string>
#include <vector>
using namespace std;

float side(pair<int, int> x, pair<int, int> y) {
	float z = fabs(sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2)));
	return z;
}

float square(pair<int, int> x, pair<int, int> y, pair<int, int> z) {
	float x1 = side(x, y);
	float y1 = side(x, z);
	float z1 = side(z, y);
	float p = (x1 + y1 + z1) / 2;
	float S = sqrt(p*(p-z1)*(p-x1)*(p-y1));
	return S;
}


float Geom(pair<int, int> x, pair<int, int> y, pair<int, int> z, vector<pair<int, int>> Coord) {
	pair<int, int> x1;
	x1 = { (x.first + y.first + z.first)/3,(x.second + y.second + z.second) / 3 };
	float dlina = 0;
	for (int i = 0; i < Coord.size(); i++) {
		if (dlina <= side(Coord[i], x1)) dlina = side(Coord[i], x1);
	}
	return dlina;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int choice;
	string task = "Задание:\nУфологи обнаружили на некоторой местности K точек посадки НЛО. Так как всем известно, что инопланетяне очень любят треугольники, вам была поставлена задача найти треугольник с самой меньшей площадью, который только можно из них построить, определить его геометрический центр и провести от него линию к самой удаленной от него точке посадки НЛО. Узнав длину этой линии человечество получит шанс узнать хоть что-нибудь о наших братьях по разуму.\n";
	cout << task;
	while (true) {
		cout << "Меню:\n1 - Задание;\n2 - Повторить задание;\n3 - Выйти из программы.\n>> ";
		cin >> choice;
		if (cin.peek() != '\n') choice = 0;
	switch (choice)
	{
		case 1:
		{
			vector<pair<int,int>> Coord;
			vector<pair<int, int>> sides;
			float Square = 0;
			string dot;
			int dots = 0;
			do { cout << "Введите количество точек НЛО от 3 до 100.\n>> "; 
			cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cin >> dots;
			if (cin.peek() != '\n') dots =0;
			} while (cin.fail() || dots < 3 || dots > 100);
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
			cout << "Длина от геометрического центра до дальней точки: " <<Geom(sides[0], sides[1], sides[2], Coord) << endl;
			break;
		}
		case 2:cout << task;
		case 3: cout << "Выход из программы."; exit(1);
		default:
			cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Недопустимый ввод. Введите заново. ";
	}
}
}