#include <iostream>

//задание 1 и 2:

class Date
{
private:
    int m_Day;
    int m_Month;
    int m_Year;

public:
    Date(int day, int month, int year) : 
    m_Day(day), m_Month(month), m_Year(year){}

	const int& getDay() const
	{
		return m_Day;
	}

	const int& getMonth() const
	{
		return m_Month;
	}

	const int& getYear() const
	{
		return m_Year;
	}

	friend std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		os << d.m_Day << '.' << d.m_Month << '.' << d.m_Year;

		return os;
	}
};

template <class T>
class Myptr
{
private:
	T* m_ptr;
public:
	Myptr(T* ptr = nullptr) : m_ptr(ptr) {}
	~Myptr() { delete m_ptr; }

	Myptr(Myptr& p)
	{
		m_ptr = p.m_ptr;
		p.m_ptr = nullptr;
	}

	Myptr& operator=(Myptr& p)
	{
		if (&p == this)
			return *this;

		delete m_ptr;
		m_ptr = p.m_ptr;
		p.m_ptr = nullptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	bool isNull() const { return m_ptr == nullptr; }
};

const Myptr<Date>& compares_dates(const Myptr<Date>&, const Myptr<Date>&);

void ex1()
{
	Myptr<Date> today(new Date(15, 12, 2021));

	std::cout << "Day: " << today->getDay() << std::endl;
	std::cout << "Month: " << today->getMonth() << std::endl;
	std::cout << "Year: " << today->getYear() << std::endl;
	std::cout << "today: " << *today << std::endl;

	Myptr<Date> date;

	std::cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	std::cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	date = today;

	std::cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	std::cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	std::cout << "date: " << *date << std::endl;
}
const Myptr<Date>& compares_dates(const Myptr<Date>& a, const Myptr<Date>& b)
{
	if (a->getYear() > b->getYear())
		return a;
	else if (a->getYear() < b->getYear())
		return b;
	else
	{
		if (a->getMonth() > b->getMonth())
			return a;
		else if (a->getMonth() < b->getMonth())
			return b;
		else
		{
			if (a->getDay() > b->getDay())
				return a;
			else
				return b;
		}
	}
}

void swap_dates(Myptr<Date>& a, Myptr<Date>& b)
{
	Myptr<Date> temp(a);
	a = b;
	b = temp;
}

void ex2()
{
	Myptr<Date> date1(new Date(12, 12, 2022));
	Myptr<Date> date2(new Date(13, 12, 2022));

	std::cout << *compares_dates(date1, date2) << std::endl;
	swap_dates(date1, date2);
	std::cout << *compares_dates(date1, date2) << std::endl;
}

int main()
{
	ex1();
	ex2();
}
