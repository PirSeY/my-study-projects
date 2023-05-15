#include <iostream>
#include "List.h"
#include <string>
#include <clocale>

using namespace std;

void loop() {
	List<string> list;
	string el;
	int parameter;
	bool result = false;
	int position;
	bool flag = 1;
	while (flag) {
		cout << "Âíèìàíèå! Íóìåðàöèÿ â ñïèñêå íà÷èíàåòñÿ ñ 1!" << endl;
		cout << "0 - âûõîä" << endl;
		cout << "1 - âñòàâèòü" << endl;
		cout << "2 - âñòàâèòü íà ïîçèöèþ" << endl;
		cout << "3 - óäàëèòü ýëåìåíò" << endl;
		cout << "4 - óäàëèòü ñ ïîçèöèè" << endl;
		cout << "5 - âûâåñòè íà ýêðàí" << endl;
		cout << "6 - èçìåíèòü" << endl;
		cout << "7 - ïîçèöèÿ ýëåìåíòà" << endl;
		cout << "8 - ïîëó÷èòü ýëåìåíò ïî ïîçèöèè" << endl;
		cout << "9 - íàëè÷èå ýëåìåíòà â ñïèñêå" << endl;
		cout << "10 - ïóñòîé ëè ñïèñîê" << endl;
		cout << "11 - ðàçìåð ñïèñêà" << endl;
		cout << "12 - î÷èñòêà ñïèñêà" << endl;
		cout << "13 - âûçîâ èòåðàòîðà" << endl;
		cin >> parameter;
		if (parameter > 13 || parameter < 0) {
			cout << "Íåïðàâèëüíûé âûáîð" << endl;
			cin.get();
			cin.get();
			continue;
		}
		switch (parameter)
		{
		case 0:
			flag = 0;
			break;
		case 1: // insert
			cout << "Ââåäèòå ýëåìåíò" << endl;
			cin >> el;
			list.insert(el);
			break;
		case 2: // insert pos
			cout << "Ââåäèòå ýëåìåíò è ïîçèöèþ" << endl;
			cin >> el >> parameter;
			try {
				list.insert(el, parameter);
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
				cin.get();
				cin.get();
			}
			break;
		case 3: // remove
			cout << "Ââåäèòå ýëåìåíò" << endl;
			cin >> el;
			try {
				list.remove(el);
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
				cin.get();
				cin.get();
			}
			break;
		case 4: // remove pos
			cout << "Ââåäèòå ïîçèöèþ" << endl;
			cin >> parameter;
			try {
				list.remove_from(parameter);
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
				cin.get();
				cin.get();
			}
			break;
		case 5: // print
			try {
				list.print();
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			cin.get();
			cin.get();
			break;
		case 6: // change         
			cout << "Ââåäèòå ýëåìåíò è ïîçèöèþ" << endl;
			cin >> el >> parameter;
			try {
				list.change(el, parameter);
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
				cin.get();
				cin.get();
			}
			break;
		case 7: // position        
			cout << "Ââåäèòå ýëåìåíò" << endl;
			cin >> el;
			try {
				cout << list.position(el);
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			cin.get();
			cin.get();
			break;
		case 8: // get              
			cout << "Ââåäèòå ïîçèöèþ" << endl;
			cin >> parameter;
			try {
				cout << list.get(parameter) << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			cin.get();
			cin.get();
			break;
		case 9: // contains
			cout << "Ââåäèòå ýëåìåíò" << endl;
			cin >> el;
			result = list.contains(el);
			if (result == true) cout << "Ñîäåðæèò" << endl;
			else cout << "Íå ñîäåðæèò" << endl;
			cin.get();
			cin.get();
			break;
		case 10: // is empty
			result = list.isEmpty();
			if (result == 1) cout << "Ñïèñîê ïóòîé" << endl;
			else cout << "Ñïèñîê íå ïóñòîé" << endl;
			cin.get();
			cin.get();
			break;
		case 11: // size
			cout << "Ðàçìåð ñïèñêà= " << list.size() << endl;
			cin.get();
			cin.get();
			break;
		case 12://clear list
			list.clear();
			cout << "Ñïèñîê î÷èùåí" << endl;
			cin.get();
			cin.get();
			break;
		case 13:
			List <string>::Iterator iter = list.begin();//Ñîçäàåì èòåðàòîð
			List <string>::Iterator iterEnd = list.end();
			int exit = 1;
			int nom;
			string h;
			while (exit) {
				cout << "Ìåíþ" << endl;
				cout << "Äëÿ óñòàíîâêè èòåðàòîðà â íà÷àëî ñïèñêà íàæìèòå 1" << endl;
				cout << "Äëÿ ñîçäàíèÿ èòåðàòîðà end() íàæìèòå 2" << endl;
				cout << "Äëÿ âûâîäà ýëåìåíòà,íà êîòîðûé óêàçûâàåò èòåðàòîð, íàæìèòå 3" << endl;
				cout << "Äëÿ ïåðåäâèæåíèÿ èòåðàòîðà âïåð¸ä íàæìèòå 4" << endl;
				cout << "Äëÿ ïåðåäâèæåíèÿ èòåðàòîðà íàçàä íàæìèòå 5" << endl;
				cout << "Äëÿ çàäàíèÿ çíà÷åíèÿ èòåðàòîðó íàæìèòå 6" << endl;
				cout << "Äëÿ ñðàâíåíèÿ ñ èòåðàòîðîì end() íàæìèòå 7" << endl;
				cout << "Äëÿ âûõîäà íàæìèòå 8" << endl;
				cin >> nom;
				if (nom > 8 || nom < 1) {
					cout << "Íåïðàâèëüíûé âûáîð" << endl;
					cin.get();
					continue;
				}
				switch (nom) {
				case 1:
					iter = list.begin();
					cout << "Èòåðàòîð óñòàíîâëåí íà íà÷àëî ñïèñêà" << endl;
					cin.get();
					cin.get();
					break;

				case 2:
					iter = list.end();
					cout << "Ñîçäàí èòåðàòîð end()" << endl;
					cin.get();
					cin.get();
					break;

				case 3:
					try {
						cout << *iter;
						cout << "- Íà ýòîò ýëåìåíò óêàçûâàåò èòåðàòîð ";
					}
					catch (std::overflow_error& err) {
						std::cout << err.what() << std::endl;
					}
					cin.get();
					cin.get();
					break;
				case 4:
					try {
						++iter;
					}
					catch (std::overflow_error& err) {
						cout << err.what() << endl;
					}
					cin.get();
					cin.get();
					break;
				case 5:
					try {
						--iter;
					}
					catch (std::overflow_error& err) {
						cout << err.what() << endl;
					}
					cin.get();
					cin.get();
					break;
				case 6:
					try {
						cout << "Ââåäèòå çíà÷åíèå- " << endl;
						cin >> h;
						*iter = h;
					}
					catch (std::overflow_error& err) {
						cout << err.what() << endl;
						cin.get();
						cin.get();
					}
					break;

				case 7:
					if (iter == iterEnd) cout << "Èòåðàòîðû ðàâíû" << endl;
					else cout << "Èòåðàòîðû íå ðàâíû" << endl;
					cin.get();
					cin.get();
					break;
				case 8:
					exit = 0;
					break;
				}
			}
			break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	loop();
}
