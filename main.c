#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>

char paises[20][100] = {
	"Reino Unido",	
	"Alemanha",
	"Brasil",	
	"Argentina",	
	"França",
	"Áustria",
	"Austrália",
	"Finlândia",
	"Itália",
	"Espanha",	
	"Estados Unidos",
	"Canadá",
	"África do Sul",
	"Nova Zelândia",
	"Países Baixos"
};

struct Piloto{
	int codigo;
	char nome[100];
	int idade;
	char sexo;
	char paisOrigem[100];
};

struct Tempo{
	int minutos;
	int segundos;
	int milisegundos;
};


struct Circuito{
	// único gerado automaticamente com base no último circuito registrado
	int codigo;
	char nome[100];
	char pais[100];
	int tamanhoCircuito;
	
//	O valor do menor tempo do circuito deverá ser atualizado automaticamente sempre 
// que um piloto realizar uma volta melhor do que a anteriormente cadastrada.
	struct Tempo tempoRecorde;
	
// Identificação do piloto que obteve o menor tempo do circuito;
	int identificacaoPiloto;
};

char pedeSexo();
void pedeNome(char nomePiloto[100], char pedido[50]);
void pedePaisOrigemPiloto(char paisOrigem[100]);
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int pedeIdPiloto();
int pedeIdade();

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	struct Piloto pilotosRegistrados[399];
	struct Circuito circuitosRegistrados[500];
	int circuitosJaRegistrados = 0;
	int pilotosJaRegistrados = 0;
	
	
	//	Para o cadastro de um Piloto ou Circuito só poderão ser utilizados os países
	//	previamente cadastrados (seja um vetor pré-definido ou com o uso de leitura em
	//	arquivos).
	

	
	// inclusão de um novo piloto
	pilotosJaRegistrados = incluiNovoPiloto(pilotosRegistrados, pilotosJaRegistrados);
	circuitosJaRegistrados = incluiNovoCircuito(circuitosRegistrados, circuitosJaRegistrados);
}

int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados){
	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	pedeNome(circuito.nome, "circuito");
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	struct Piloto piloto;
	
	piloto.codigo = pedeIdPiloto();
	pedeNome(piloto.nome, "piloto");
	piloto.idade = pedeIdade();
	pedePaisOrigemPiloto(piloto.paisOrigem);
	piloto.sexo = pedeSexo();
	
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	Sleep(3000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}


void pedeNome(char nomePiloto[100], char pedido[50]){
	printf("Digite o nome do %s: ", pedido);
	scanf("%[^\n]s", &nomePiloto);
	fflush(stdin);
}

int pedeIdade(){
	int idade;
	
	printf("Digite a idade do piloto: ");
	scanf("%i", &idade);
	fflush(stdin);
	
	if(idade > 0 && idade < 200) return idade;
	system("CLS");
	printf("Idade inválida! Tente novamente...\n");
	return pedeIdade();
}

void pedePaisOrigemPiloto(char paisOrigem[100]){
	int i;
	
	printf("Digite o país de origem do piloto: ");
	scanf("%[^\n]s", &paisOrigem);
	fflush(stdin);
	// essa variável indica se o programa encontrou o nome do país que o usuário digitou no vetor de países
	// 0 significa que não encontrou, 1 significa que encontrou o nome
	int achou = 0;

	for(i = 0; i < 20; i++){
		if(strcmp(paisOrigem, paises[i]) == 0)
			achou = 1;
	}
	
	if(achou == 0){
		system("CLS");
		printf("Não conseguimos entender... tente novamente\n");
		pedePaisOrigemPiloto(paisOrigem);	
	}

}


int pedeIdPiloto(){
	
	// falta verificar se o id que o usuário passou já foi incluído em algum momento, assim evitar a repetição do mesmo piloto
	int idPiloto;
	
	// pedindo a identificação do piloto
	printf("Numero de identificacao do jogo:");
	scanf("%i",&idPiloto);
	fflush(stdin);
	
	// verifica se o id do piloto está no intervalo de 100 e 500 (não incluso) 
	if(idPiloto > 100 && idPiloto < 500){
		return idPiloto;
	} else { 
	// se o id do piloto não passou pelas verificações acima, então o programa limpa a tela, exibe uma mensagem de erro e começa o processo novamente até achar um id válido
		system("CLS");
		printf("Valor digitado incorreto, tente novamente...\n\n");
		return pedeIdPiloto();
	}
}

char pedeSexo(){
	char sexo;
	
	// pedindo para o usuário um char que represente o sexo do piloto
	printf("Digite o sexo do piloto (m -> masculino, f -> feminino): ");
	scanf("%c", &sexo);
	fflush(stdin);
	
	// se for f ou m, então está válido, portanto já retorna o valor
	if(sexo == 'f' || sexo == 'm') return sexo;
	
	// caso o contrário exibe a mensagem de valor inválido e repete a função
	printf("Valor inválido! Tente novamente...\n");
	return pedeSexo();	
}
