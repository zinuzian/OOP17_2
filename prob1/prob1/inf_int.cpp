#include "inf_int.h"
#include <string>
#include <string.h>

// 
// to be filled by students
//
// example :
//
// bool operator==(const inf_int& a , const inf_int& b)
// {
//     // we assume 0 is always positive.
//     if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )
//         return true;
//     return false;
// }
//

inf_int::inf_int()              // assign 0 as a default value
{
	digits = new char[2];
	digits[0] = '0';
	digits[1] = 0;
	length = 1;
	thesign = true;
}
inf_int::inf_int(int n)
{
	thesign = (n < 0) ? false : true;
	if (!thesign) n = -n;
	string s = to_string(n);
	reverse(s.begin(), s.end());
	length = s.length();
	digits = new char[length + 1];
	s.copy(digits, length, 0);
	digits[length] = 0;
}
inf_int::inf_int(const char* str)
{
	if (str[0] == '-') thesign = false;
	else thesign = true;
	string s = string((thesign) ? str : str + 1);
	reverse(s.begin(), s.end());
	length = s.length();
	digits = new char[length+1];
	s.copy(digits, length, 0);
	digits[length] = 0;
}
inf_int::inf_int(const inf_int& that) // copy constructor
{
	length = that.length;
	if (length > 0){
		thesign = that.thesign;
		digits = new char[length+1];
		for (int i = 0; i < length; i++){
			digits[i] = that.digits[i];
		}
		digits[length] = 0;
	}
	else{		//error
		digits = new char[2];
		digits[0] = '0';
		digits[1] = 0;
		length = 1;
		thesign = true;
	}
}
inf_int::~inf_int() // destructor
{
	delete[] this->digits;
}

inf_int& inf_int::operator=(const inf_int& that) // assignment operator
{
	delete[] this->digits;
	this->thesign = that.thesign;
	this->digits = new char[that.length+1];
	this->length = that.length;
	(string(that.digits)).copy(this->digits, this->length, 0);
	this->digits[this->length] = 0;
	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	if (a.thesign == b.thesign){				//same sign
		string s = string(a.digits);
		if (s.compare(b.digits) == 0)			//same digits
			return true;
	}
	return false;

}
bool operator!=(const inf_int& a, const inf_int& b)
{
	return !(a == b);
}
bool operator>(const inf_int& a, const inf_int& b)
{
	if (a.thesign ^ b.thesign){				//sign is diffrent
		if (a.thesign){						//+>-
			return true;
		}
		else{								//->+
			//return false;
		}
	}
	else{									//sign is same
		if (a.thesign){						//+>+
			if (a.length > b.length) return true;
			//if (a.length < b.length) return false;
			for (int i = a.length-1; i >=0; i--){	//same length
				if (a.digits[i] < b.digits[i]) return false;
				if (a.digits[i] > b.digits[i]) return true;
			}
		}
		else{								// ->-
			if (a.length < b.length) return true;
			//if (a.length > b.length) return false;
			for (int i = a.length - 1; i >= 0; i--){
				if (a.digits[i] > b.digits[i]) return false;
				if (a.digits[i] < b.digits[i]) return true;
			}
		}
	}
	return false;			// 1) ->+	2) short+>long+	3)long->short-	4)equal
		
}
bool operator<(const inf_int& a, const inf_int& b){
	if (a == b)
		return false;
	return !(a > b);
}

inf_int operator+(const inf_int&a , const inf_int& b)
{	
	if (a.thesign == b.thesign){		//same sign, result's sign is determined.
		const inf_int *hi = a.length > b.length ? &a:&b;
		const inf_int *lo = a.length > b.length ? &b : &a;
		string str = string(hi->digits);

		for (int i = 0; i < lo->length; i++){		//add every single numbers
			str.at(i) += (lo->digits[i]-'0');
		}

		bool carryExists = false;				//carry occurs -> add 1
		for (int i = 0; i < str.length(); i++){
			str.at(i) += carryExists ? 1 : 0;
			if (str.at(i)>'9'){		//carry
				str.at(i) -= 10;
				carryExists = true;
			}
			else
				carryExists = false;
		}
		if (carryExists)		//MSB carry?
			str += '1';

		reverse(str.begin(), str.end());
		inf_int result(str.c_str());
		result.thesign = hi->thesign;
		return result;
	}
	else{								//different sign(=subtract)
		if (a.thesign){			//b is minus
			inf_int t(b);
			t.thesign = true;
			return a - t;
		}
		else{					//a is minus
			inf_int t(a);
			t.thesign = true;
			return b - t;
		}
	}

}
inf_int operator-(const inf_int& a, const inf_int& b)
{
	if (a.thesign == b.thesign){			//same sign
		const inf_int *hi=&a, *lo=&b;					//let hi's abs is bigger
		bool isMinus = false;
		if (a.length < b.length){						//longer one would be hi
			hi = &b; lo = &a;
			isMinus = true;
		}
		else if (a.length == b.length){					//same length
			int i;
			for (i = a.length - 1; i >= 0; i--){
				if (a.digits[i] > b.digits[i]){ break; }
				if (a.digits[i] < b.digits[i]){ hi = &b; lo = &a; isMinus = true; break; }
			}
			if (i < 0){
				return inf_int();
			}
		}

		string str = string(hi->digits);
		for (int i = 0; i < lo->length; i++){
			str.at(i) -= (lo->digits[i]-'0');
		}
		bool carryExists = false;
		for (int i = 0; i < str.length(); i++){
			str.at(i) -= carryExists ? 1 : 0;
			if (str.at(i) < '0')				//carry
			{
				str.at(i) += 10;
				carryExists = true;
			}
			else
				carryExists = false;
		}
		if (carryExists)		//error
			return *lo - *hi;	//change hi, lo

		for (int i = str.length() - 1; i >= 0; i--){	//shrink to fit
			if (str.at(i) != '0') break;
			str = str.substr(0, str.length() - 1);
		}
		reverse(str.begin(), str.end());
		inf_int result(str.c_str());
		result.thesign = isMinus ^ hi->thesign;
		return result;
	}
	else{									//different sign(=add)
		if (a.thesign){				//b is minus
			inf_int t(b);
			t.thesign = true;
			return a + t;
		}
		else{
			inf_int t(a);			//a is minus
			t.thesign = true;
			return inf_int() - (t + b);
		}
		
	}
}
inf_int operator*(const inf_int& a, const inf_int& b)
{
	int len = a.length + b.length;
	int *r = new int[len];
	for (int i = 0; i < len; i++){
		r[i] = 0;
	}
	for (int i = 0; i < a.length; i++){
		int multiplicand = a.digits[i]-'0';
		for (int j = 0; j < b.length; j++){
			int multiplyer = b.digits[j]-'0';
			r[i + j] += (multiplyer * multiplicand);
		}
	}

	string str = "";
	for (int i = 0; i < len-1; i++){
		if (r[i]>9){
			r[i + 1] += (r[i] / 10);
			r[i] %= 10;
		}
		str = str + (char)(r[i]+'0');
	}
	if (r[len-1]!=0)
		str = str + (char)(r[len-1] + '0');
	for (int i = str.length() - 1; i >= 0; i--){	//shrink to fit
		if (str.at(i) != '0') break;
		str = str.substr(0, str.length() - 1);
	}

	reverse(str.begin(), str.end());
	inf_int result(str.c_str());
	result.thesign = !(a.thesign ^ b.thesign);
	return result;
}
// friend inf_int operator/(const inf_int& , const inf_int&); // not required

ostream& operator<<(ostream& o, const inf_int& a)
{
	if (!a.thesign)
		o << '-';
	for (int i = a.length-1; i >= 0; i--){
		o << a.digits[i];
	}
	return o;
}
// friend istream& operator>>(istream& , inf_int&);    // not required