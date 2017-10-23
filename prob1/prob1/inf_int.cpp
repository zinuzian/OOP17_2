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
	digits = new char[1];
	digits[0] = 0;
	length = 1;
	thesign = true;
}
inf_int::inf_int(int n)
{
	thesign = (n < 0) ? false : true;
	if (!thesign) n = -n;
	string s = to_string(n);
	length = s.length();
	digits = new char[length];
	for (int i = 0; n; i++){
		digits[i] = n % 10 + '0';
		n /= 10;
	}
}
inf_int::inf_int(const char* str)
{
	if (str[0] == '-') thesign = false;
	string s = (thesign) ? str : str + 1;
	length = s.length();
	digits = new char[length];
	for (int i = 0; i < length; i++){
		digits[i] = s.at(length - i - 1);
	}
}
inf_int::inf_int(const inf_int& that) // copy constructor
{
	length = that.length;
	if (length > 0){
		thesign = that.thesign;
		digits = new char[length];
		for (int i = 0; i < length; i++){
			digits[i] = that.digits[i];
		}
	}
	else{
		thesign = true;
		length = 0;
	}
}
inf_int::~inf_int() // destructor
{
	delete[] digits;
}

inf_int& inf_int::operator=(const inf_int& that) // assignment operator
{
	this->thesign = that.thesign;
	delete[] this->digits;
	this->length = that.length;
	this->digits = new char[this->length];
	for (int i = 0; i < that.length; i++){
		this->digits[i] = that.digits[i];
	}
	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	int i;
	if (a.thesign == b.thesign){				//same sign
		if (a.length == b.length){				//same length
			for (i = 0; i < a.length; i++){		//same digits
				if (a.digits[i] != b.digits[i])
					break;
			}
		}
	}
	if (i == a.length)
		return true;
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
	return false;			//1) ->+   2) long+>short+	3)short->long-	4)equal
		
}
bool operator<(const inf_int& a, const inf_int& b){
	/*
	if (a.thesign ^ b.thesign){				//sign is diffrent
		if (b.thesign){						//-<+
			return true;
		}
		else{								//+<-
			//return false;
		}
	}
	else{									//sign is same
		if (a.thesign){						//+<+
			if (a.length < b.length) return true;
			//if (a.length > b.length) return false;
			for (int i = a.length - 1; i >= 0; i--){	//same length
				if (a.digits[i] > b.digits[i]) return false;
				if (a.digits[i] < b.digits[i]) return true;
			}
		}
		else{								// -<-
			if (a.length > b.length) return true;
			//if (a.length < b.length) return false;
			for (int i = a.length - 1; i >= 0; i--){
				if (a.digits[i] < b.digits[i]) return false;
				if (a.digits[i] > b.digits[i]) return true;
			}
		}
	}
	return false;			//1) ->+   2) long+>short+	3)short->long-	4)equal
	*/
	if (a == b)
		return false;
	return !(a > b);
}

inf_int operator+(const inf_int&a , const inf_int& b)
{	
	inf_int r;
	string tmp_r;
	inf_int abs_a(a), abs_b(b);
	abs_a.thesign = true; abs_b.thesign = true;
	const inf_int *pa, *pb;					//let pa's abs is bigger
	if (abs_a>abs_b){
		pa = &a; pb = &b;
	}
	else{
		pa = &b; pb = &a;
	}

	if (a.thesign ^ b.thesign){			//diffrent sign(=subtract)

		for (int i = 0; i < pb->length; i++){
			pa->digits[i] -= pb->digits[i];
		}
		for (int i = 0; i < pa->length; i++){
			if (pa->digits)
		}
		if (pa->digits[pa->length-1]<0)
			
	}
	else{									//same sign
		if (abs_a.length == abs_b.length
			&& abs_a.digits[abs_a.length - 1] + abs_b.digits[abs_b.length - 1] > 9)
			r.length = pa->length + 1;
		else
			r.length = pa->length;
		delete[] r.digits;
		r.digits = new char[r.length];		//create new digits array
		r.thesign = a.thesign;
		for (int i = 0; i < r.length; i++){
			r.digits[i] = 0;
		}

		for (int i = 0; i < pb->length; i++){
			char addResult = abs_a.digits[i] + abs_b.digits[i];
			if (addResult > 9){
				r.digits[i+1]++;
			}
			r.digits[i] = addResult % 10;
		}
	}
	return r;
}
inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int tb(b);
	tb.thesign = !b.thesign;
	return a + tb;
}
inf_int operator*(const inf_int& a, const inf_int& b)
{

}
// friend inf_int operator/(const inf_int& , const inf_int&); // not required

ostream& operator<<(ostream& o, const inf_int& a)
{

}
// friend istream& operator>>(istream& , inf_int&);    // not required