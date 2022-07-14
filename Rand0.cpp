
// Rand0.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>   
#include <random>
#include <stdint.h>
#include <vector>
#include <string>
#include <cstdint>
#include <conio.h>

using namespace std;

double congruential(int &x) // функция генерации псевдослучайных чисел
{
	int m = 100, a = 8, inc = 65;
	x = ((a * x) + inc) % m;
	return (x / double(m));
}

const uint8_t random_map[] =
{
  4,  1,   63, 3,
  64, 22,  54, 2,
  0,  52,  75, 34,
  89, 100, 23, 84
};

uint8_t get_random()
{
  static uint8_t index = 0;
  index = (index + 1) & 0xF; // 0xF, потому что столько значений в random_map
  return random_map[index];
}


unsigned XorShift128()
{
	unsigned x = rand()%3; // начальные значения могут быть любыми
	unsigned y = rand()%100;
	unsigned z = rand()%500;
	unsigned w = rand()%800;
	unsigned t = x^(x<<11);
	x = y;
	y = z;
	z = w;
	w = (w^(w>>19)) ^ (t^(t>>8));
	return w;
}


//Pseudo-random Numbers Generator
unsigned int PRNG()
{
    // наше начальное число - 5323
    static unsigned int seed = 5323;
 
    // Берём текущее порождающее значение и генерируем из него новое значение
    seed = 8253729 * seed + 2396403;
 
    // Берём число и возвращаем значение от 0 до 32767
    return seed % 32768;
}

// Генерируем случайное число от min до max (включительно)
int getRandomNumber(int min, int max)
{
    // static используется для повышения эффективности, поэтому
    // мы вычисляем это значение только один раз
    static const double fraction ( 1.0 / (RAND_MAX + 1.0) );  
    // равномерно распределяем случайные числа по нашему диапазону
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

void a1() {
	//Встроенный генератор функцией rand()
	srand(5323);
	cout << "1 Встроенный генератор функцией rand()" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << rand() << '\t';
		if (count % 5 == 0)
			cout << '\n';
	}


}


void a2(){

//rand(), зависящий от времени
	srand(static_cast<unsigned int>(time(nullptr)));
	cout << "2 rand(), зависящий от времени" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << rand() << '\t';
		if (count % 5 == 0)
			cout << '\n';
	}



}

void a3(){
	//rand() с минимальным и максимальным значением
	cout << "3 rand() с минимальным и максимальным значением" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << getRandomNumber(1, 10000) << '\t';
		if (count % 5 == 0)
			cout << '\n';
	}


}

void a4(){
		//ГПСЧ
	cout << "4 ГПСЧ" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << PRNG() << '\t';
		if (count % 5 == 0)
			cout << '\n';
	}

}

void a5(){
//Вихрь Мерсенна
	mt19937 mersenne (static_cast<mt19937::result_type>(time(nullptr))) ;
	uniform_int_distribution<> num (1, 10000);
	cout << "5 Вихрь Мерсенна" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << num(mersenne) << '\t';
		if (count % 5 == 0)
			cout << '\n';
	}
}

void a6(){
	//STL
	mt19937 engine;
	engine.seed(time(nullptr));
	cout << "6 STL Random" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << engine() << '\t'; 
		if (count % 5 == 0)
			cout << '\n';
	}

}


void a7(){
	//Xorshift
	cout << "7 Алгоритм Xorshift" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << XorShift128() << '\t'; 
		if (count % 5 == 0)
			cout << '\n';
	}

}

void a8(){
//Random device
	random_device rd;
	mt19937 generator(rd()); 
	uniform_int_distribution<> range(1, 10000);
	cout << "8 Генерация с помощью random device" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << range(generator) << '\t'; 
		if (count % 5 == 0)
			cout << '\n';
	}
}

void a9(){
	//Табличный рандом
	cout << "9 Табличная генерация как в игре DOOM (1993)" <<endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << get_random() << '\t'; 
		if (count % 5 == 0)
			cout << '\n';
	}
}
int a10(){
//Генератор Лемера
	int x = 2;
	cout << "10 Генератор Лемера" << endl;
	for (int count(1) ; count <= 100; ++count)
	{
		cout << congruential(x) << '\t'; 
		if (count % 5 == 0)
			cout << '\n';
	}
	return x;
}


void print_menu() {   // Функция вызова меню 
    cout << "Главное меню\n" << endl;
    cout << "1. Встроенный Генератор функций rand()\n"
         << "2. rand(), зависящий от времени\n"
         << "3. rand() с минимальным и максимальным значением\n"
         << "4. ГПСЧ\n"
		 << "5. Вихрь Мерсенна\n"
         << "6. STL\n"
         << "7. Xorshift\n"
		 << "8. Random device\n"
		 << "9. Табличный рандом\n"
         << "10. Генератор Лемера\n"
	     << "11. Выход\n"
	     <<" >> "<< endl;
}


int main()
{ int m;
	
for( ; ;){
		print_menu(); // функция вывода меню
		cin >> m;

	  switch(m){ 
	  case 1:
		  a1();  
		  break;
	  case 2:
		  a2();  
		   break;
	  case 3:
		  a3(); 
		   break;
	  case 4:
		  a4(); 
		    break;
	  case 5:
		  a5(); 
		   break;
	  case 6:
		  a6(); 
		  break;
	  case 7:
		  a7(); 
		  break;
	  case 8:
		 a8() ;
		 break;
	  case 9:
		   a9() ;
		  break;
	  case 11:
		  system("pause");  
		  return 0;
	  case 10:
		   a10(); 
		  break;
	  default:
		  cout<<"Ошибка . повторите ввод снова \n";
		  break;
	system("pause");
    return 0;
	  }
}
}