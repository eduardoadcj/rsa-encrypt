#include <iostream>
#include <math.h>

using namespace std;

int is_prime_number(int n)
{

  if(n <= 0)
    return 0;
  if(n <= 2)
    return 1;

  int div = 1;

  int square = sqrt(n);

  for(int i = 2; i <= square; i++){
    if(n%i == 0 && i<n){
      div = 0;
      break;
    }
  }

  return div;

}

//Encontre e, tal que d × e = 1 mod z
int find_e(int d, int z)
{

  int e = 0;
  while(!(d * e == 1 % z) && e <= 20)
    e++;

  if(e <= 20)
    e = 0;

  return e;

}

int prime_each_other(int d, int z)
{
  if(is_prime_number(d))
    return 0;

  if(z % d == 0)
    return 0;

  return 1;

}

//o ideal é separar a informacoes em 4bits, pq esse é o limite la q o professor disse q vai tirar D quem nao fizer
//operar os bits de forma a criptografar cada 4 bits

int main()
{

  int n = 234223243;

  if(is_prime_number(n)){
    cout << "É primo!" << endl;
  }else{
    cout << "Não é primo" << endl;
  }

  return 0;
}
