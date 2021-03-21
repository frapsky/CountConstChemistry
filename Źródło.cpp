#include <iostream>
#include <cmath>

template<typename T>
T f_Ek1(T Aj, T Ck,T l) {

	return Aj / (Ck*l);
};

template<typename T>
double f_Ck1m(T Am, T Ek1, T l) {

	return Am / (Ek1*l);
};

template<typename T>
T f_K1(T Ck1m, T CFem,T Ckwm) {
	
	return  ((Ck1m) / ((CFem - Ck1m) * (Ckwm - Ck1m)));
};

template<typename T>
T f_K1kwadrat(T K1, T CFej, T Ckwj) {
	T x1, x2;
	//T x;

	//K1* x - (1 + (K1 * CFej) + (K1 * Ckwj)) * x + (K1 * CFej * Ckwj);

	T delta = (pow((-1*(1 + (K1 * CFej) + (K1 * Ckwj))),2) - (4 * ((K1) * (K1 * CFej * Ckwj))));

	x1 = ((-1*(-1 * (1 + (K1 * CFej) + (K1 * Ckwj))) - sqrt(delta)) / (2 * K1));
	x2 = ((-1*(-1 * (1 + (K1 * CFej) + (K1 * Ckwj))) + sqrt(delta)) / (2 * K1));

	//cout << "X1 to: " << x1 << "  X2 to: " << x2 << endl;

	return x1 > x2 ? x2 : x1;
}

int main() {

	double lambda = 505;
	double Aj = 0.263;
	double Am = 0.817;
	double l = 1;

	double CFej = 3 * pow(10, -3);
	double CFem = 1.5 * pow(10, -2);
	double Ckwm = 3 * pow(10, -2);
	double Ckwj = 5.4 * pow(10, -2);

	//std::cout << f_Ek1(Aj, CFej, l) << std::endl; //fine
	double Ek1 = f_Ek1<double>(Aj,CFej,l);

	//std::cout << f_Ck1m(Am,Ek1, l) << std::endl;//fine
	double Ck1m = f_Ck1m<double>(Am,Ek1,l);

	double K1 = f_K1<double>(Ck1m, CFem, Ckwm);

	/*std::cout <<Ek1<<"    "<<Ck1m<<"    "<<K1 << std::endl;
	cout << Ek1<<"  Ck1m:"<< "  " <<Ck1m<<"   K1:" << K1<< std::endl;

	Ek1 = f_Ek1<double>(0.320,K1*pow(10,-7), l);
	std::cout << Ek1 << "  Ck1m:" << "  " << Ck1m << "   K1:" << K1 << std::endl;*/

	//K1 = f_K1kwadrat<double>(K1, CFej, Ckwj);
	//std::cout << "Nowe K1 to: " << K1 << std::endl;
	int n = 1;
	int cnt = 0;
	while ( n <60) {


		std::cout <<cnt<<": "<< Ek1 << "    " << Ck1m << "    " << K1 << std::endl;
		double K2 = f_K1kwadrat<double>(K1, CFej, Ckwj);
		Ek1 = f_Ek1<double>(Aj, K2, l);
		Ck1m = f_Ck1m<double>(Am, Ek1,l);
		K1 = f_K1<double>(Ck1m,CFem,Ckwm);
		cnt++;
		n++;
	}
	
	return 0;
}