#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<conio.h>

using namespace std;

struct Room {
	int number;
	string type;
	bool available;
};

static void details()
{
	fstream obj("guestdetail.txt", ios::out);
	string name;
	string num, pasp;
	cout << "Введите имя гостя: ";
	cin >> name;
	cout << "Введите номер телефона гостя: ";
	cin >> num;
	cout << "Введите паспортные данные гостя(серия и номер): ";

	obj << name << " ";
	obj << num << " ";
	obj << pasp;

	system("CLS");
}

static void display() {
	cout << "\t\t=======================================\t\n";
	cout << "\t\t *система управления отелем*\n";
	cout << "\t\t=======================================\t\n";
}

static void displayMenu() {
	details();
	cout << "\t\t\t\tГлавное меню\n" << endl;
	cout << "Нажмите 1 для заселения" << endl;
	cout << "Нажмите 2 для выселения" << endl;
	cout << "Нажмите 3 для обслуживания номера" << endl;
	cout << "Нажмите 4 для выставления счёта" << endl;
	cout << "Нажмите 5 для выхода" << endl;
	cout << endl;
}

static void initializeRooms(Room rooms[], int size) {
	for (int i = 0; i < size; i++) {
		rooms[i].number = i + 1;
		rooms[i].type = "Стандартный";
		rooms[i].available = true;
	}
}

static void checkIn(Room rooms[], int roomNumber) {
	if (roomNumber < 1 || roomNumber > 10) {
		cout << "Неверный номер комнаты!\n";
		return;
	}

	Room& room = rooms[roomNumber - 1];
	if (!room.available) {
		cout << "Комната " << roomNumber << " уже занята.\n";
	}
	else {
		room.available = false;
		cout << "Заселение в комнату " << roomNumber << ".\n";
	}
}

static void checkOut(Room rooms[], int roomNumber) {
	if (roomNumber < 1 || roomNumber > 10) {
		cout << "Неверный номер комнаты!\n";
		return;
	}

	Room& room = rooms[roomNumber - 1];
	if (room.available) {
		cout << "Комната " << roomNumber << " уже свободна.\n";
	}
	else {
		room.available = true;
		cout << "Выселение из комнаты " << roomNumber << ".\n";
	}
}

static void displayRooms(Room rooms[], int size) {
	cout << "Номер\tТип\t\tСтатус\n";
	for (int i = 0; i < size; i++) {
		cout << rooms[i].number << "\t" << rooms[i].type << "\t"
			<< (rooms[i].available ? "Свободна" : "Занята") << endl;
	}
}

static void roomService(Room rooms[], int roomNumber) {
	int room_service = 1000;
	cout << "Стоимость обслуживания номера составляет " << room_service << " рублей за раз" << endl;
	cout << "Введите номер комнаты для обслуживания: ";
	cin >> roomNumber;
	if (roomNumber < 1 || roomNumber > 10) {
		cout << "Неверный номер комнаты!" << endl;
		return;
	}

	Room& room = rooms[roomNumber - 1];
	if (!room.available) {
		cout << "Комната " << roomNumber << " — обслуживание номера предоставлено.\n";
	}
	else {
		room.available = false;
		cout << "Комната " << roomNumber << " уже занята. Обслуживание не может быть предоставлено.\n";
	}
}

static void billdetail() {
	char choice;
	int room_service = 1000, r_s_bill, room_charges = 400, r_c_bill, time, hours, total_amount;
	float gst, total_bill;
	cout << "Сколько часов вы пробыли в нашем отеле?" << endl;
	cin >> hours;
	cout << "Включено ли обслуживание номера? (Y/N): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y' || choice == 'Д' || choice == 'д') {
		cout << "Сколько раз вы пользовались обслуживанием номера?" << endl;
		cin >> time;
		r_s_bill = room_service * time;
		r_c_bill = room_charges * hours;
		cout << "Стоимость обслуживания номера: " << r_s_bill << endl;
		cout << "Стоимость проживания в отеле: " << r_c_bill << endl;
		cout << "Налог составляет 13%" << endl;
		total_amount = r_s_bill + r_c_bill;
		gst = (13 * total_amount) / 100;
		total_bill = total_amount + gst;
		cout << "Ваш счёт: " << total_bill << endl;
	}
	else if (choice == 'N' || choice == 'n' || choice == 'Н' || choice == 'н') {
		r_c_bill = room_charges * hours;
		cout << "Стоимость проживания в отеле: " << r_c_bill << endl;
		cout << "Налог составляет 13%" << endl;
		total_amount = 0 + r_c_bill;
		gst = (13 * total_amount) / 100;
		total_bill = total_amount + gst;
		cout << "Ваш счёт: " << total_bill << " рублей" << endl;
	}
	else
		cout << "!!!Неверный выбор!!!\n";
}

static void billing(Room rooms[], int roomNumber) {
	cout << "Введите номер комнаты для выставления счёта: ";
	cin >> roomNumber;
	if (roomNumber < 1 || roomNumber > 10) {
		cout << " Неверный номер комнаты!" << endl;
		return;
	}

	Room& room = rooms[roomNumber - 1];
	if (!room.available) {
		cout << "Комната " << roomNumber << " — детали счёта:" << endl;
		void billdetail();
	}
	else {
		cout << "Комната " << roomNumber << " свободна! Детали счёта недоступны." << endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	Room rooms[10];
	initializeRooms(rooms, 10);

	int choice, roomNumber;
	string name;
	string num, cnic;

	system("color F5");

	display();

	do {
		displayMenu();

		cout << "Введите ваш выбор: ";
		cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			displayRooms(rooms, 10);
			cout << "Введите номер комнаты для заселения: ";
			cin >> roomNumber;
			checkIn(rooms, roomNumber);
			break;
		case 2:
			cout << "Введите номер комнаты для выселения: ";
			cin >> roomNumber;
			checkOut(rooms, roomNumber);
			break;
		case 3:
			roomService(rooms, roomNumber);
			break;
		case 4:
			billing(rooms, roomNumber);
			billdetail();
			break;a
		case 5:
			cout << "Выход из программы. До свидания!" << endl;
			break;
		default:
			cout << "Неверный выбор!\n";
		}

		cout << endl;

	} while (choice != 5);

	system("pause");
	return 0;
}
