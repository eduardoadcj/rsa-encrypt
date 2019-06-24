#include <iostream>
#include <math.h>
#include <cstring>

struct encrypted_text{
  int* text;
  int size;
};

struct decrypted_text{
  char* text;
  int size;
};

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

int find_e(int d, int z)
{

  int e = 0;
  while(!((d * e)%z == 1) && e <= 20)
    e++;

  if(e >= 20)
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

void encrypt(char *input, encrypted_text *output, int p, int q, int d)
{

  int size = strlen(input);
  int i, j, n, z, e, c;

  output->text = (int*) malloc((2 * size) * sizeof(int));

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

  if(e == 0){
    cout << "E não encontrado" << endl;
    return;
  }

  j = 0;
  for(i = 0; i < size; i++){

      c = 0;
      c = input[i] & 0xF;
      output->text[j] = fmod(pow(c, e), n);
      j++;

      c = input[i] >> 4;
      output->text[j] = fmod(pow(c, e), n);
      j++;

  }

  output->size = j;

}

void decrypt(encrypted_text *input, decrypted_text *output, int p, int q, int d)
{

  int i, j, n, z;
  char c;

  output->size = input->size/2;
  output->text = (char*) malloc((output->size + 1) * sizeof(char));

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

  j = 0;
  for(i = 0; i < output->size; i++){

      c = 0x00;
      c = ( (int) fmod(pow(input->text[j], d), n)) | 0x00;
      j++;

      output->text[i] = c | ( ((int) fmod(pow(input->text[j], d), n)) << 4);
      j++;

  }

  output->text[output->size] = 0;

}

int main()
{

  encrypted_text enc_text;
  decrypted_text dec_text;
  char input[50];

  cout << "Informe uma mensagem: ";
  cin.get(input, 50);

  encrypt(input, &enc_text, 3, 11, 7);

  cout << "Mensagem criptografada ---------------------" << endl << endl;
  for(int i = 0; i < enc_text.size; i++){

    if(enc_text.text[i] < 10 && enc_text.text[i] >= 0){
      cout << "  0" << enc_text.text[i] << "  ";
    }else if(enc_text.text[i] < 0){
      cout << " " << enc_text.text[i] << "  ";
    }else{
      cout << "  " << enc_text.text[i] << "  ";
    }

    if((i+1)%10 == 0)
      cout << endl;

  }
  cout << endl << endl;

  decrypt(&enc_text, &dec_text, 3, 11, 7);

  cout << "Mensagem descriptografada: " << dec_text.text << endl;

  return 0;

}
