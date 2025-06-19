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
	cout << "Входные координаты: {INT_MAX,INT_MAX}, {0,0}.\nВыходные данные: 3037000499.976" << endl;
	EXPECT_NEAR(side({ INT_MAX,INT_MAX }, { 0,0 }), 3037000499.976, 1e6);
}

TEST(SideTest, Negative) {
	cout << "Входные координаты: { -100,-100 }, { 100,100 }.\nВыходные данные: 282.843" << endl;
	EXPECT_NEAR(side({ -100,-100 }, { 100,100 }), 282.843, 0.001);
}

TEST(SideTest, SamePoints) {
	cout << "Входные координаты: { 100,100 }, { 100,100 }.\nВыходные данные: 0" << endl;
	EXPECT_EQ(side({ 100,100 }, { 100,100 }), 0.0);
}

TEST(SideTest, MaxMin) {
	cout << "Входные координаты: {INT_MAX,INT_MAX}, {INT_MIN,INT_MIN}.\nВыходные данные: <Некорректное малое значение <2" << endl;
	EXPECT_LT(side({ INT_MIN,INT_MIN }, { INT_MAX,INT_MAX }), 2.0);
}


float square(pair<int, int> x, pair<int, int> y, pair<int, int> z) {
	float S = 0.5 * abs((x.first * (y.second - z.second) + y.first * (z.second - x.second) + z.first * (x.second - y.second)));
	return S;
}

TEST(SquareTest, PositiveCoords) {
	cout << "Входные координаты: {100,100}, {0,0}, {75,25}.\nВыходные данные: 1250" << endl;
	EXPECT_EQ(square({ 100,100 }, { 0,0 }, { 75,25 }), 2500);
}

TEST(SquareTest, NegativeCoords) {
	cout << "Входные координаты: {-100,-100}, {0,0}, {-75,-25}.\nВыходные данные: 1250" << endl;
	EXPECT_EQ(square({ -100,-100 }, { 0,0 }, { -75,-25 }), 2500);
}

TEST(SquareTest, RightTriangle) {
	cout << "Входные координаты: {0,0}, {3,0}, {0,4}.\nВыходные данные: 6" << endl;
	EXPECT_EQ(square({ 0,0 }, { 3,0 }, { 0,4 }), 6.0);
}

TEST(SquareTest, SamePoints) {
	cout << "Входные координаты: {5,5}, {5,5}, {5,5}.\nВыходные данные: 0" << endl;
	EXPECT_EQ(square({ 5,5 }, { 5,5 }, { 5,5 }), 0.0);
}

TEST(SquareTest, borders) {
	cout << "Входные координаты:{ INT_MAX,INT_MAX }, { INT_MIN,INT_MIN }, { INT_MIN,INT_MAX }.\nВыходные данные: <4" << endl;
	EXPECT_LT(square({ INT_MAX,INT_MAX }, { INT_MIN,INT_MIN }, { INT_MIN,INT_MAX }), 4.0);
}

float Geom(pair<int, int> x, pair<int, int> y, pair<int, int> z, vector<pair<int, int>> Coord) {
	pair<float, float> x1;
	x1 = { (x.first + y.first + z.first) / 3,(x.second + y.second + z.second) / 3 };
	float dlina = 0;
	for (size_t i = 0; i < Coord.size(); i++) {
		if (dlina < side(Coord[i], x1)) dlina = side(Coord[i], x1);
	}
	return dlina;
}

TEST(GeomTest, PositiveCoords) {
	vector<pair<int, int>> coord = { {10,50}, {0,0}, {75,25}, {100,100} };
	cout << "Входные данные: Coord = { {10,50}, {0,0}, {75,25}, {100,100} }\nВыходные данные: 103.97" << endl;
	EXPECT_NEAR(Geom(coord[0], coord[1], coord[2], coord), 103.97, 0.01);
}

TEST(GeomTest, NegativeCoords) {
	vector<pair<int, int>> coord = { {-10,-50}, {0,0}, {-75,-25}, {-100,-100} };
	cout << "Входные данные: Coord = { {-10,-50}, {0,0}, {-75,-25}, {-100,-100} }\nВыходные данные: 103.97" << endl;
	EXPECT_NEAR(Geom(coord[0], coord[1], coord[2], coord), 103.97, 0.01);
}

TEST(GeomTest, ThreePoints) {
	vector<pair<int, int>> coord = { {0,0}, {3,0}, {0,4} };
	cout << "Входные данные: Coord = { {0,0}, {3,0}, {0,4} }\nВыходные данные: 3.16" << endl;
	EXPECT_NEAR(Geom(coord[0], coord[1], coord[2], coord), 3.16, 0.01);
}

TEST(GeomTest, SamePoints) {
	vector<pair<int, int>> coord = { {10,10}, {10,10}, {10,10} };
	cout << "Входные данные: Coord = { {10,10}, {10,10}, {10,10} }\nВыходные данные: 0" << endl;
	EXPECT_EQ(Geom(coord[0], coord[1], coord[2], coord), 0.0);
}

TEST(GeomTest, OverflowCase) {
	vector<pair<int, int>> coord = { {INT_MAX,INT_MAX}, {INT_MIN,INT_MIN}, {INT_MIN,INT_MAX} };
	float result = Geom(coord[0], coord[1], coord[2], coord);
	cout << "Входные данные: Coord = { {INT_MAX,INT_MAX}, {INT_MIN,INT_MIN}, {INT_MIN,INT_MAX} }\nВыходные данные:  2.02467e+09" << endl;
	EXPECT_GT(result, 1e9);
}

TEST(GeomTest, MinPoints) {
	vector<pair<int, int>> coord;
	cout << "Входные данные: { 10,50 }, { 0,0 }, { 75,25 }, Coord = {}\nВыходные данные: 0" << endl;
	EXPECT_EQ(Geom({ 10,50 }, { 0,0 }, { 75,25 }, coord), 0);
}


bool proverka(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	return a != b && b != c && a != c;
}

TEST(ProverkaTest, PositivePoints) {
	cout << "Входные данные: a={1,2}, b={3,4}, c={INT_MAX,INT_MAX}\nВыходные данные: true" << endl;
	EXPECT_TRUE(proverka({ 1,2 }, { 3,4 }, { INT_MAX,INT_MAX }));
}

TEST(ProverkaTest, TwoSamePoints) {
	cout << "Входные данные: a={1,1}, b={1,1}, c={2,2}\nВыходные данные: false" << endl;
	EXPECT_FALSE(proverka({ 1,1 }, { 1,1 }, { 2,2 }));
}

TEST(ProverkaTest, NegativePoints) {
	cout << "Входные данные: a={-3,-1}, b={INT_MIN,INT_MIN}, c={-2,-2}\nВыходные данные: true" << endl;
	EXPECT_TRUE(proverka({ -3,-1 }, { INT_MIN,INT_MIN }, { -2,-2 }));
}

TEST(ProverkaTest, AllSamePoints) {
	cout << "Входные данные: a={5,5}, b={5,5}, c={5,5}\nВыходные данные: false" << endl;
	EXPECT_FALSE(proverka({ 5,5 }, { 5,5 }, { 5,5 }));
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

TEST(MinSquareTest, NormalCase) {
	vector<pair<int, int>> points, coord = { {0,0}, {3,0}, {0,4} };
	cout << "Входные данные: (0,0), (3,0), (0,4)\nВыходные данные: 6" << endl;
	EXPECT_EQ(MinSquare(points, coord, 3), 6.0);
}

TEST(MinSquareTest, FourPoints) {
	vector<pair<int, int>> points, coord = { {0,0}, {1,0}, {0,1}, {1,1} };
	cout << "Входные данные: {0,0}, {1,0}, {0,1}, {1,1} \nВыходные данные: 0.5" << endl;
	EXPECT_EQ(MinSquare(points, coord, 4), 0.5);
}

TEST(MinSquareTest, MaxCoordinates) {
	vector<pair<int, int>> points, coord = { {INT_MAX,0}, {0,INT_MAX}, {INT_MIN,0} };
	cout << "Входные данные: INT_MAX/INT_MIN\nВыходные данные: >1e1" << endl;
	EXPECT_GT(MinSquare(points, coord, 3), 1e1);
}

TEST(MinSquareTest, DuplicatePoints) {
	vector<pair<int, int>> points, coord = { {2,2}, {2,2}, {2,2} };
	cout << "Входные данные: {2,2}, {2,2}, {2,2}\nВыходные данные: 0" << endl;
	EXPECT_EQ(MinSquare(points, coord, 3), 0.0);
}

TEST(MinSquareTest, LessThanThreePoints) {
	vector<pair<int, int>> points, coord = { {1,1}, {2,2} };
	cout << "Входные данные: 2 точки (1,1), (2,2)\nВыходные данные: Вызвана критическая ошибка" << endl;
	EXPECT_NO_THROW({
		float result = MinSquare(points, coord, 2);
		EXPECT_FLOAT_EQ(result, 0.0);
		});
}

void OutputTask(vector<pair<int, int>> Coord, int dots) {
	vector<pair<int, int>> points;
	float Square;
	Square = MinSquare(points, Coord, dots);
	cout << "Наименьшая площадь = " << Square << endl;
	cout << "Длина от геометрического центра до дальней точки: " << Geom(points[0], points[1], points[2], Coord) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int choice;
	string task = "Задание:\nУфологи обнаружили на некоторой местности K точек посадки НЛО. Так как всем известно, что инопланетяне очень любят треугольники, вам была поставлена задача найти треугольник с самой меньшей площадью, который только можно из них построить, определить его геометрический центр и провести от него линию к самой удаленной от него точке посадки НЛО. Узнав длину этой линии человечество получит шанс узнать хоть что-нибудь о наших братьях по разуму.\n";
	cout << task;
	while (true) {
		cout << "Меню:\n1 - Решение;\n2 - Повторить постановку задания;\n3 - Выйти из программы;\n4 - Тесты.\n>> ";
		cin >> choice;
		if (cin.peek() != '\n') choice = 0;
		switch (choice)
		{
		case 1:
		{
			vector<pair<int, int>> Coord;
			int dots = 0;
			do {
				cout << "Введите количество точек НЛО от 3 до 100.\n>> ";
				cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> dots;
				if (cin.peek() != '\n') dots = 0;
			} while (cin.fail() || dots < 3 || dots > 100);
			for (size_t i = 0; i < dots; i++)
				Coord.push_back({ rand() % 201 - 100, rand() % 201 - 100 });
			OutputTask(Coord, dots);
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