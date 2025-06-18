#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
using namespace std;
void runTests() {
	int fake_argc = 1;
	char fake_argv0[] = "program_name"; 
	char* fake_argv[] = { fake_argv0, nullptr };
	testing::InitGoogleTest(&fake_argc, fake_argv);
	RUN_ALL_TESTS();
}
float side(pair<int, int> x, pair<int, int> y) {
	float z = abs(sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2)));
	return z;
}
TEST(SideTest, Positive) { 
	cout << "Входные координаты: { 100,100 }, { 0,0 }.\nВыходные данные: 141.421" << endl;
	EXPECT_NEAR(side({ 100,100 }, { 0,0 }), 141.421, 0.001); 
}

TEST(SideTest, Negative) { 
	cout << "Входные координаты: { -100,-100 }, { 100,100 }.\nВыходные данные: 282.843" << endl;
	EXPECT_NEAR(side({ -100,-100 }, { 100,100 }), 282.843, 0.001); }

TEST(SideTest, SamePoints) { 
	cout << "Входные координаты: { 100,100 }, { 100,100 }.\nВыходные данные: 0" << endl;
	EXPECT_FLOAT_EQ(side({ 100,100 }, { 100,100 }), 0.0); }

float square(pair<int, int> x, pair<int, int> y, pair<int, int> z) {
	float S = 0.5 * abs((x.first * (y.second - z.second) + y.first * (z.second - x.second) + z.first * (x.second - y.second)));
	return S;
}

float Geom(pair<int, int> x, pair<int, int> y, pair<int, int> z, vector<pair<int, int>> Coord) {
	pair<float, float> x1;
	x1 = { (x.first + y.first + z.first) / 3,(x.second + y.second + z.second) / 3 };
	float dlina = 0;
	for (size_t i = 0; i < Coord.size(); i++) {
		if (dlina <= side(Coord[i], x1)) dlina = side(Coord[i], x1);
	}
	return dlina;
}

bool proverka(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	return a != b && b != c && a != c;
}

float MinSquare(vector<pair<int, int>>& points, vector<pair<int, int>> Coord, int dots) {
	float Square = 0;
	for (size_t i = 0; i < dots; i++) {
		for (size_t j = i + 1; j < dots; j++) {
			for (size_t z = j + 1; z < dots; z++) {
				float current_square = square(Coord[i], Coord[j], Coord[z]);
				if ((Square > current_square && proverka(Coord[i], Coord[j], Coord[z])) || Square == 0) {
					Square = current_square;
					points = { Coord[i],Coord[j],Coord[z] };
				}
			}
		}
		cout << "Точка " << i + 1 << " с координатами: (" << Coord[i].first << ", " << Coord[i].second << ")" << endl;
	}
	return Square;
}


int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int choice;
	string task = "Задание:\nУфологи обнаружили на некоторой местности K точек посадки НЛО. Так как всем известно, что инопланетяне очень любят треугольники, вам была поставлена задача найти треугольник с самой меньшей площадью, который только можно из них построить, определить его геометрический центр и провести от него линию к самой удаленной от него точке посадки НЛО. Узнав длину этой линии человечество получит шанс узнать хоть что-нибудь о наших братьях по разуму.\n";
	cout << task;
	while (true) {
		cout << "Меню:\n1 - Решение;\n2 - Повторить постановку задания;\n3 - Выйти из программы.\n>> ";
		cin >> choice;
		if (cin.peek() != '\n') choice = 0;
		switch (choice)
		{
		case 1:
		{
			vector<pair<int, int>> Coord;
			vector<pair<int, int>> sides;
			float Square = 0;
			int dots = 0;
			do {
				cout << "Введите количество точек НЛО от 3 до 100.\n>> ";
				cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> dots;
				if (cin.peek() != '\n') dots = 0;
			} while (cin.fail() || dots < 3 || dots > 100);
			for (size_t i = 0; i < dots; i++)
				Coord.push_back({ rand() % 201 - 100, rand() % 201 - 100 });
			Square = MinSquare(sides, Coord, dots);
			cout << "Наименьшая площадь = " << Square << endl;
			cout << "Координаты наименьшего треугольника (" << sides[0].first << ", " << sides[0].second << "), (" << sides[1].first << ", " << sides[1].second << "), (" << sides[2].first << ", " << sides[2].second << ")" << endl;
			cout << "Длина от геометрического центра до дальней точки: " << Geom(sides[0], sides[1], sides[2], Coord) << endl;
			break;
		}
		case 2:cout << task; break;
		case 3: cout << "Выход из программы."; exit(1);
		case 4: runTests();  break;
		default:
			cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Недопустимый ввод. Введите заново. ";
		}
	}
}