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

int is_prime_each_other(int d, int z)
{
  if(is_prime_number(d))
    return 0;

  if(z % d == 0)
    return 0;

  return 1;

}

//o ideal é separar a informacoes em 4bits, pq esse é o limite la q o professor disse q vai tirar D quem nao fizer
//operar os bits de forma a criptografar cada 4 bits

void encrypt(char *input, int p, int q, int d)
{

  int size = sizeof(input);
  int i, j, n, z, e;
  unsigned int c;

  if(!is_prime_number(p) || !is_prime_number(q)){
    cout << "P ou Q não é primo!" << endl;
    return;
  }

  z = (p - 1) * (q - 1);

  if(is_prime_each_other(d, z)){
    cout << "Não é primo entre si!" << endl;
    return;
  }

  n = p * q;
  e = find_e(d, z);

  for(i = 0; i < size; i++){

      c = 0x00;
      c = input[i] & 0xF;
      c = fmod(pow(c, e), n);
      input[i] = input[i] | c;

      c = 0x00;
      c = input[i] & 0xF0;
      c = c >> 4;
      c = fmod(pow(c, e), n);
      input[i] = input[i] | (c << 4);

  }

}

int main()
{

  char c[] = "eduar";

  encrypt(c, 3, 11, 7);
  cout << "Teste: " << c << endl;

  return 0;
}
