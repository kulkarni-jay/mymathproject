/***************************************************************************** 
 * Copyright (C) Jay Kulkarni
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <stdio.h>
#include "math.h"
#include <stdlib.h>
#include <errno.h>

int check(double x) {
	if(isnan(x) == 1)
		return 1;
	else if(isinf(x) == 1)
		return 2;
}

double sine(double x) {
	if(x == 0)
		return 0;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	else {
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		if(fabse(x) > 2 * M_PI) { 			/* term reduction */
			long double y = fmode(x, 2 * M_PI);
			x = y;
		}
		int n;
		long double sum, term;
		n = 3;
		sum = x;
		term = x;
		while(fabse(term) > 0.000000000001) {
			term = ((-1) * term * (x * x)) / (n * (n - 1));
			sum += term;
			n = n + 2;		
		}
		if(flag == 1)
			return -sum;
		return sum;
	}
}

double sinhe(double x) {
	if(x == 0)
		return 0;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}	
	double term = x, sum = x;
	int n = 1000000, i;
	for(i = 3; i < n;) {
		term = term * x * x / (i * (i - 1));
		sum += term;
		i = i + 2;
	}
	if(fabse(sum) > DBL_MAX) {
		errno = ERANGE;
		return INFINITY;
	}
	return sum;
}

double asine(double x) {
	
	if(x > 1. || x < -1.) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	else if(x == 1)
		return M_PI_2;
	else if(x == -1)
		return -M_PI_2;
	else {
		int  i = 3;
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		long double term = powe(x, 3) / 6, sum = x + (powe(x, 3) / 6);
		while(term > 0.00000000001) { 
			term = (term * x * x * powe(i, 2)) / ((i + 1) * (i + 2));
			sum += term;
			i += 2;
		}
		if(flag == 1)
			return -sum;
		return sum;
	}
}

double cose(double x) {
	if(x == 0)
		return 1;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	return sine(M_PI_2 - x);
}

double acose(double x) {
	if(x == 0)
		return M_PI_2;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	else if(x >= -1 && x <= 1) {
		if(x < 0)
			return M_PI - acose(-x);
		return M_PI_2 - asine(x);
	}
	else {
		errno = EDOM;
		return NAN; 
	}	 
}

double coshe(double x) {
	if(x == 0)
		return 1.;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else {
		double sum = 1, term = 1;
		int n = 2;
		while(term > 0.0000000001) {
			term = (term * x * x) / (n * (n - 1));
			sum += term;
			n = n + 2;
		}
		if(fabse(sum) > DBL_MAX) {
		errno = ERANGE;
		return INFINITY;
		}
		return sum;
	}
}

double tane(double x) {
	if(fmode(x, M_PI) == 0)
		return 0.;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	else if(fmode(fabse(x), M_PI_2) == 0) {           /* domain error */
		errno = EDOM;
		return INFINITY;
	}
	else if(fmode(x, M_PI_4) == 1. && fmode(fabse(x), M_PI_2) != 0.)
		return 1.;
	else {
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		if(flag == 1)
			return (-1)*(sine(x) / cose(x));
		return (sine(x) / cose(x));
	}
}

double tanhe(double x) {
	if(fmode(x, M_PI) == 0)
		return 0.;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		return 1.;
	}
	else if(x > 8.)
		return 1;
	return (sinhe(x) / coshe(x));
}

double atane(double x) {
	if(fmode(x, M_PI) == 0)
		return 0.;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		return M_PI_2;
	}
	int i = 3;
	long double sum = x, term = x;
	if(fabse(x) <= 1.) {
		while(i < 100) {		//x -x^3/3 + x^5/5 ...... range : [-pi, pi]
			term = powe(x, i) / i;
			if(i % 4 == 3)
				sum = sum - term;
			else if(i % 4 == 1) 
				sum += term;
			i += 2;
		}
		return sum;
	}
	
}

double atan2e(double y, double x) {
	if(x == 0)
		return NAN;
	else if(y == 0)
		return 0;
	else if(check(x) == 1 || check(y) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(y) == 2) {
		return M_PI_2 / 2;
	}
	else {
		long double term = (fabse(y) / fabse(x));
		if(x > 0 && y > 0) {		/*first quadrant*/
			return atane(term);
		}
		else if(y < 0 && x > 0) {	/*second quadrant*/
			return -(atane(term));
		}
		else if(y < 0 && x < 0) {	/*third quadrant*/
			return -(M_PI - atane(term));
		}
		return	(M_PI - atane(term));	/*fourth quadrant*/
	}
}

double powe(double x, double y) {
	int sign = 0;
	long double term, result;
	if(x==0) 
		if(y == 0)
			return 1;
		else 
			return 	0.0;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else if((int)y == y){
		if(y == 0)
			return 1.0;
		else {
			if(y < 0) {
				sign = 1;
				y = -y;
			}	
			term = x; 
			result = 1;
			while(y) {
				if((int)y%2 == 1)
					result = result * term;
				y /= 2;
				term = term * term;
			}
			if(sign) 
				return (1.0)/result;	
			else 
				return (double)result;	
		}	
	}
	else {
		long double ln = loge(x), exp = y * ln;
		return (expe(exp));
	}
}

double expe(double x) {
	int sign = 0, n =1;
	long double term, sum;
	if(x == 0)
		return 1;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else {
		if(x < 0) {
			sign = 1;
			x = -x;
		}
		term = 1;
		sum = 1;
		for(int i = 1; i < 1000; i++) {
			term = (term * x) / n;
			sum += term;
			n++;
		}	
	}
	if(sign)
		return (1.0)/sum;
	else 
		return sum;	
}

double floore(double x) {
	if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else {
		int i = (int)x; 
		if (i > x) 
			return (double)(--i);
		else if(i < x)
			return (double)(i);
		else
			return x;
	}			
}

double ceile(double x) {
	if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else { 
		int i =(int)x;
		if (i > x) 
			return (double)(i);
		else if(i < x)
			return (double)(++i);
		else
			return x;
	}
}

double fabse(double x) {
	if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else if(x >= 0)
		return x;
	return -x;
}

double loge(double x) {
	if(x < 0) {
		errno = EDOM;
		return NAN;
	}
	else if(x == 0) {
		errno = EDOM;
		return INFINITY;
	}
	else if(x == 1)
		return 0.;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else {	
		long int i = 1;
		long double sum = 0, term = 1;
		if(x > 1.) {
			while(term > 0.0000001) {
				term *= (1-(1/x));
				sum += term/i;
				i++;
			}
			return sum;
		}
		else { //x < 1 && x > 0
			long double num = (x - 1);
			while(i < 2500) {
				term = powe(num, i) / i;
				if(i % 2 == 1)
					sum += term;
				else 
					sum = sum - term;
				i++;
			}
			return sum;
		}
	}
}

double log10e(double x) {
	long double ans;
	if(x < 0) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else if(fmode(x, 10) == 0) {
		double count = 0;
		while(x > 1 ) {
			x = x / 10;
			count++;
		}
		return count;
	}
	else {
		ans = loge(x) / M_LN10;
		return ans;
	}		
}

double fmode(double x, double y) {
	if(y == 0)
		return NAN;
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	else if(check(y) == 2) {
		if(isnan(x) != 0 || isinf(x) != 0)
			return x;
	}
	else if(x == 0)
		return 0;
	else{
		int quo = x / y;
		return (x - quo * y); 
	}
}

double sqrte(double x) {
	if(x < 0)
		return NAN;
	else if(check(x) == 1) {
		return NAN;
		errno = EDOM;
	}
	else if(check(x) == 2) {
		return INFINITY;
		errno = EDOM;
	}
	else if(x == 0)
		return 0.;
	return powe(x, 0.5);
}

double ldexpe(double x, int exponent) {
	if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	long double ans, exp;
	exp = powe(2, exponent);
	ans = x * exp;
	return ans;
}

double modfe(double x, double *integer) {
	if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return NAN;
	}
	double in = (int)x;
	*integer = in;
	return (x - *integer);
}

double frexpe(double x, int *exponent){
	if(x == 0) {
		*exponent = 0;
		return 0;
	}
	else if(check(x) == 1) {
		errno = EDOM;
		return NAN;
	}
	else if(check(x) == 2) {
		errno = EDOM;
		return INFINITY;
	}
	else {
		int i = 1, sign = 0;
		if(x < 0) {
			x = -x;
			sign = 1;
		}
		if(x < 1 && x > 0) {
			i = -1;
			while(powe(2, i) > x) {
				i--;
			}
			i++;
		}
		else {
			while(x >= powe(2, i))
				i++;
		}
		*exponent = i;
		if(sign == 1)
			return -(x / powe(2, *exponent));
		return (x / powe(2, *exponent)); 
	}
}
