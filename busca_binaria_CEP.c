#include <stdio.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;
struct _Endereco
{
    char rua[72];
    char bairro[72];
    char cidade[72];
    char estado[72];
    char UF[2];
    char CEP[8];
    char lixo[2] ;
};

Endereco buscaCEP(char *cep, FILE *f, long ultEnd, long partida)
{
    int meio = ultEnd/2;
    fseek(f, meio * sizeof(Endereco), partida);
    Endereco e;

    int aux = fread(&e, sizeof(Endereco), 1, f);

    while(aux > 0 )
    {
        if (strncmp(cep, e.CEP, 8) != 0  )
        {
            if (strncmp(cep, e.CEP, 8) > 0 )
                buscaCEP(cep, f, ultEnd, meio);
            else if (strncmp(cep, e.CEP, 8) < 0 )
                buscaCEP(cep, f, meio, partida);
        }
        else
        {
            return e;
            break;
        }
    }
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "faltou o parâmetro");
        return 1;
    }
	
    FILE *f;
    f = fopen("C:\\Users\\vaise\\Desktop\\cep_ordenado.dat", "r");

    fseek(f, 0, SEEK_END);
    long ultimoEndereco = ftell(f)/sizeof(Endereco);
    rewind(f);

    Endereco e = buscaCEP("20541080", f, ultimoEndereco/sizeof(Endereco), SEEK_SET);x = fread(&e, sizeof(Endereco), 1, f);
	
	fprintf(stdout, "CEP: %.8s\nRua: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.2s\n",
					e.CEP, e.rua, e.bairro, e.cidade, e.UF);
    }

    return 0;
}
