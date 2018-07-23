#pragma once
#include<iostream>
#include<string.h>
using std::ostream;
using std::istream;

class my_string
{
private:
	char *data;
	int len;
public:
	static const int npos = -1;
	my_string()
	{
		data = new char[1];
		data[0] = '\0';
		len = 0;
	}
	my_string(const char *str);
	my_string(const my_string &s);
	my_string(const my_string &s, int begin, int end);
	my_string(int size, char c);
	my_string(const char *str, int n);
	my_string(const char *str, int begin, int end);
	~my_string();
	my_string& operator=(const my_string &s);
	my_string& operator=(const char *str);
	my_string& operator+(const my_string &s);
	my_string& operator+=(const my_string &s);
	bool operator==(const my_string &s);
	bool operator==(const char *str);
	friend bool operator==(const char *str, const my_string &s);
	int length() { return len; }
	const char* c_str() const { return data; }
	char operator[](int n) const;
	friend ostream& operator<<(ostream &out, my_string &s);
	friend istream& operator>>(istream &in, my_string &s);
	int find(const my_string &s, int pos = 0);
	int find(const char *str, int pos = 0);
	int find(const char *str, int pos, int n);
	int find(char ch) const;
	my_string& replace(int pos, int size, const char* str);
};
my_string :: my_string(const char *str)
{
	if (str != NULL)
	{
		len = strlen(str);
		data = new char[len + 1];
		strcpy(data, str);
	}
	else
	{
		len = 0;
		data = new char[1];
		data[0] = '\0';
	}
}

my_string::my_string(const my_string &s)
{
	len = s.len;
	data = new char[len + 1];
	strcpy(data, s.data);
}

my_string::my_string(const my_string &s, int begin, int end)
{
	if (begin >= end)
	{
		len = 1;
		data = new char[1];
		data[0] = s.data[begin];
	}
	else
	{
		len = end - begin + 1;
		data = new char[len + 1];
		strncpy(data, s.data + begin, end);
		data[len] = '\0';
	}
}

my_string::my_string(int size, char c)
{
	len = size;
	data = new char[len + 1];
	memset(data, c, len);
	data[len] = '\0';
}

my_string::my_string(const char *str, int n)
{
	if (str != NULL)
	{
		len = n;
		data = new char[len + 1];
		strncpy(data, str, len);
		data[len] = '\0';
	}
	else
	{
		len = 0;
		data = new char[1];
		data[0] = '\0';
	}
}

my_string::my_string(const char *str, int begin, int end)
{
	if (str != NULL)
	{
		if (begin >= end)
		{
			len = 1;
			data = new char[1];
			data[0] = str[begin];
		}
		else
		{
			len = end - begin + 1;
			data = new char[len + 1];
			strncpy(data, str + begin, end);
			data[len] = '\0';
		}
	}
	else
	{
		len = 0;
		data = new char[1];
		data[0] = '\0';
	}
}

my_string::~my_string()
{
	len = 0;
	delete[] data;
}

my_string& my_string::operator=(const my_string& s)
{
	if (this != &s)
	{
		len = s.len;
		delete[]data;
		data = new char[len + 1];
		strcpy(data, s.data);
	}
	return *this;
}

my_string& my_string::operator=(const char *str)
{
	if (str != NULL)
	{
		len = strlen(str);
		delete[] data;
		data = new char[len + 1];
		strcpy(data, str);
	}
	else
	{
		len = 0;
		data = new char[1];
		data[0] = '\0';
	}
	return *this;
}

my_string& my_string::operator+(const my_string &s)
{
	my_string *ns = new my_string;
	ns->len = len + s.len;
	ns->data = new char[ns->len + 1];
	strcpy(ns->data, data);
	strcat(ns->data, s.data);
	return *ns;
}

my_string& my_string::operator+=(const my_string &s)
{
	len += s.len;
	char* nd = new char[len + 1];
	strcpy(nd, data);
	strcat(nd, s.data);
	delete[] data;
	data = nd;
	return *this;
}

bool my_string::operator==(const my_string &s)
{
	int cmp = strcmp(data, s.data);
	if (cmp == 0)
		return true;
	else
		return false;
}

bool my_string::operator==(const char *str)
{
	int cmp = strcmp(data, str);
	if (cmp == 0)
		return true;
	else
		return false;
}

bool operator==(const char *str, const my_string &s)
{
	int cmp = strcmp(s.data, str);
	if (cmp == 0)
		return true;
	else
		return false;
}

char my_string::operator[](int n) const
{
	if (n >= len)
		return data[len - 1];
	else if (n < 0)
		return data[0];
	else
		return data[n];
}

ostream& operator<<(ostream& out, my_string &s)
{
	out << s.data;
	return out;
}

istream& operator>>(istream &in, my_string &s)
{
	char buf[1000];
	in >> buf;
	s.len = strlen(buf);
	delete[] s.data;
	s.data = new char[s.len + 1];
	strcpy(s.data, buf);
	return in;
}

int my_string::find(const my_string &s, int pos)
{
	char *index = strstr(data + pos, s.data);
	return index - data;
}

int my_string::find(const char *str, int pos)
{
	char *index = strstr(data + pos, str);
	return index - data;
}

int my_string::find(const char *str, int pos, int n)
{
	char *s = new char[n + 1];
	strncpy(s, str, n);
	s[n] = '\0';
	char *index = strstr(data + pos, s);
	delete[] s;
	return index - data;
}

int my_string::find(char ch) const
{
	return strchr(data, ch) - data;
}

my_string& my_string::replace(int pos, int size, const char* str)
{
	int change = strlen(str) - size;
	len = len + change;
	char *s = new char[len + 1];
	data[pos] = '\0';
	strcpy(s, data);
	strcat(s, str);
	strcat(s, (data + pos + size));
	delete[] data;
	data = s;
	return *this;
}
