//POP_2020_01_13_projekt_2_Ksawery_Armatyñski_EiT_3_180088

#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_L = 20;
const int MAX_S = 200;

struct slowa {
    char slowo[MAX_L] = {};
    int ile_razy = 1;
};

slowa s[MAX_S];

void usuw_inter(int k){
	if(s[k].slowo[0] == ',' or s[k].slowo[0] == '.' or s[k].slowo[strlen(s[k].slowo)-1] == '!' or s[k].slowo[strlen(s[k].slowo)-1] == '?'){
		for(int i = 0; i < 2*strlen(s[k].slowo); i+2)
			s[k].slowo[i++] = s[k].slowo[i];
		}
			
	if(s[k].slowo[strlen(s[k].slowo)-1] == ',' or s[k].slowo[strlen(s[k].slowo)-1] == '.' or s[k].slowo[strlen(s[k].slowo)-1] == '!' or s[k].slowo[strlen(s[k].slowo)-1] == '?'){
		s[k].slowo[strlen(s[k].slowo)-1] = NULL;
	}
}

int wczytywanie() {
    int k = 0;

    fstream plik("tekst.txt");

    if (!plik) {
        cout << "Blad wczytywania pliku!" << endl;
        exit(0);
    }
		
    while (plik >> s[k].slowo) {
        int spr = 0;
        
        usuw_inter(k);
                
        for(int j = 0; j < strlen(s[k].slowo); j++)
        	s[k].slowo[j] = tolower(s[k].slowo[j]);
    	
        for (int i = 0; i < k; i++) {
            if (strcmp(s[i].slowo, s[k].slowo) == 0) {
                s[i].ile_razy++;
                spr++;
            }
        }
        if (spr == 0) k++;
        if (k > MAX_S) {
            cout << "Twoj tekst jest za dlugi!!! Maksymalna obslugiwalna ilosc roznych slow to 200" << endl;
            exit(1);
        }
    }
    plik.close();
    return k;
}

void segregowanie(int ile) {
    slowa buf;
    for (int i = ile - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (s[j].ile_razy < s[j + 1].ile_razy)
            {
                buf = s[j];
                s[j] = s[j + 1];
                s[j + 1] = buf;
            }
        }
    }
}

void wypisanie(int ile) {
    cout << "Liczba roznych slow : " << ile << endl;
    if (ile > 20) ile = 20;
    for (int i = 0; i < ile; i++)
        cout << " " << s[i].slowo << setw(22 - strlen(s[i].slowo)) << s[i].ile_razy << endl;
}
 
int main()
{
    setlocale(LC_ALL, "");

    int ile;

    ile = wczytywanie();

    segregowanie(ile);

    wypisanie(ile);

    return 0;
}
