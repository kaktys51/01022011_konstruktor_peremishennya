#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ion
{
protected:
	char charge;
	int valence;
public:
	Ion() :charge('-'), valence(1) {}
	Ion(char _charge, int valen) : valence(valen)
	{
		if (_charge != '-' && _charge != '+') charge = '-'; 
		else charge = _charge;

		if (valen > 7 || valen < 1) valence = 1;
		else valence = valen;
	}
	Ion(const Ion& a) : charge(a.charge), valence(a.valence) {} // конструктор копировани€
	Ion(Ion&& a) noexcept : charge(move(a.charge)), valence(move(a.valence)) {} //конструтор перемещени€
	~Ion() {}

	Ion& operator=(const Ion& a)
	{
		if (&a == this)return *this;

		charge = a.charge;
		valence = a.valence;
		return *this;
	}
	Ion& operator=(Ion&& a) noexcept
	{
		if (&a == this)return *this;

		charge = move(a.charge);
		valence = move(a.valence);
		return *this;
	}
	bool operator==(const Ion& a) const
	{
		return (charge == a.charge) && (valence == a.valence);
	}
	char getCharge() { return charge; }
	char getValence() { return valence; }
	void printIon()
	{
		cout << "Charge: " << charge << "  Valence: " << valence << endl;
	}
};

class Element
{
protected:
	vector<Ion> elem;
	vector<Ion> reacted;
	vector<Ion> unreacted;

public:
	Element() { elem.reserve(10); reacted.reserve(10); }
	void insertIon(Ion& a)
	{
		elem.push_back(a);
	}
	void reaction()
	{
		bool rcheck = false;
		do
		{
			rcheck = false;
			for (size_t i = 0; i < elem.size(); ++i)
			{
				for (size_t j = 0; j < elem.size(); ++j)
				{
					if (elem[i].getValence() == elem[j].getValence() && (elem[i].getCharge() != elem[j].getCharge())) //проверка первого элемента на совместимость с другими элементами
					{
						reacted.push_back(move(elem[i])); //если 2 элемента совместимы, они отправл€ютс€ в ветор прореагировавших
						reacted.push_back(move(elem[j]));
						elem.erase(elem.begin() + j); // а потом копии которые остались тут просто удал€ютс€
						elem.erase(elem.begin() + i);
						rcheck = true;
						break;
					}
				}
				if (rcheck == true) break;
				else
				{
					unreacted.push_back(elem[i]); // если элемент не будет ни скем реагировать то он отправл€етс€ в вектор не реагирующих
					elem.erase(elem.begin() + i); // и удал€етс€ отсюда
					rcheck = true;
					break;
				}
			}
			if (elem.empty()) rcheck = false; // и так пока вектор не отанентс€ путым
		} while (rcheck);

		int count = 0;

	}
	void printElement()
	{
		int count = 0;
		cout << "List of ions:" << endl;
		for (size_t i = 0; i < elem.size(); ++i)
		{
			cout << ++count << ". ";
			elem[i].printIon();
		}
	}
	void printReacted()
	{
		int count = 0;
		cout << "List of ions:" << endl;
		for (size_t i = 0; i < reacted.size(); ++i)
		{
			cout << ++count << ". ";
			reacted[i].printIon();
		}
	}
	void printUnreacted()
	{
		int count = 0;
		cout << "List of ions:" << endl;
		for (size_t i = 0; i < unreacted.size(); ++i)
		{
			cout << ++count << ". ";
			unreacted[i].printIon();
		}
	}
};

int main()
{
	Ion ox('-', 7);
	Ion oa('+', 4);//
	Ion os('+', 2);//
	Ion od('-', 6);// 
	Ion oc('-', 4);//
	Ion oq('+', 1);
	Ion op('+', 6);//
	Ion ow('-', 2);//
	Ion oe('+', 6);

	Element some;

	some.insertIon(ox);
	some.insertIon(oa);
	some.insertIon(os);
	some.insertIon(od);
	some.insertIon(oc);
	some.insertIon(oq);
	some.insertIon(op);
	some.insertIon(ow);
	some.insertIon(oe);

	cout << "Before reaction: " << endl;
	some.printElement();
	cout << " " << endl;

	cout << "Reaction started!" << endl;
	some.reaction();
	cout << " " << endl;

	cout << "Unreacted ions:" << endl;
	some.printUnreacted();
	cout << " " << endl;

	cout << "Reacted ions: " << endl;
	some.printReacted();
	return 0;
}