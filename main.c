#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

char paises[20][100] = {
	"Reino Unido",	
	"Alemanha",
	"Brasil",	
	"Argentina",	
	"Fran�a",
	"�ustria",
	"Austr�lia",
	"Finl�ndia",
	"It�lia",
	"Espanha",	
	"Estados Unidos",
	"Canad�",
	"�frica do Sul",
	"Nova Zel�ndia",
	"Pa�ses Baixos"
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
	// �nico gerado automaticamente com base no �ltimo circuito registrado
	int codigo;
	char nome[100];
	char pais[100];
	int tamanhoCircuito;
	
//	O valor do menor tempo do circuito dever� ser atualizado automaticamente sempre 
// que um piloto realizar uma volta melhor do que a anteriormente cadastrada.
	struct Tempo tempoRecorde;
	
// Identifica��o do piloto que obteve o menor tempo do circuito;
	int identificacaoPiloto;
};

char pedeSexo();
void pedeNome(char nomePiloto[100]);
void pedePaisOrigemPiloto(char paisOrigem[100]);
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	struct Piloto pilotosRegistrados[399];
	struct Circuito circuitosRegistrados[500];
	int circuitosJaRegistrados = 0;
	int pilotosJaRegistrados = 0;
	
	
	//	Para o cadastro de um Piloto ou Circuito s� poder�o ser utilizados os pa�ses
	//	previamente cadastrados (seja um vetor pr�-definido ou com o uso de leitura em
	//	arquivos).
	

	
	// inclus�o de um novo piloto
	pilotosJaRegistrados = incluiNovoPiloto(pilotosRegistrados, pilotosJaRegistrados);
	circuitosJaRegistrados = incluiNovoCircuito(circuitosRegistrados, circuitosJaRegistrados);
}

int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados){
	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	struct Piloto piloto;
	
	piloto.codigo = pedeIdPiloto();
	pedeNome(piloto.nome);
	piloto.idade = pedeIdade();
	pedePaisOrigemPiloto(piloto.paisOrigem);
	piloto.sexo = pedeSexo();
	
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	sleep(3000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}


void pedeNome(char nomePiloto[100]){
	printf("Digite o nome do piloto: ");
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
	printf("Idade inv�lida! Tente novamente...\n");
	return pedeIdade();
}

void pedePaisOrigemPiloto(char paisOrigem[100]){
	int i;
	
	printf("Digite o pa�s de origem do piloto: ");
	scanf("%[^\n]s", &paisOrigem);
	fflush(stdin);
	// essa vari�vel indica se o programa encontrou o nome do pa�s que o usu�rio digitou no vetor de pa�ses
	// 0 significa que n�o encontrou, 1 significa que encontrou o nome
	int achou = 0;

	for(i = 0; i < 20; i++){
		if(strcmp(paisOrigem, paises[i]) == 0)
			achou = 1;
	}
	
	if(achou == 0){
		system("CLS");
		printf("N�o conseguimos entender... tente novamente\n");
		pedePaisOrigemPiloto(paisOrigem);	
	}

}


int pedeIdPiloto(){
	
	// falta verificar se o id que o usu�rio passou j� foi inclu�do em algum momento, assim evitar a repeti��o do mesmo piloto
	int idPiloto;
	
	// pedindo a identifica��o do piloto
	printf("Numero de identificacao do jogo:");
	scanf("%i",&idPiloto);
	fflush(stdin);
	
	// verifica se o id do piloto est� no intervalo de 100 e 500 (n�o incluso) 
	if(idPiloto > 100 && idPiloto < 500){
		return idPiloto;
	} else { 
	// se o id do piloto n�o passou pelas verifica��es acima, ent�o o programa limpa a tela, exibe uma mensagem de erro e come�a o processo novamente at� achar um id v�lido
		system("CLS");
		printf("Valor digitado incorreto, tente novamente...\n\n");
		return pedeIdPiloto();
	}
}

char pedeSexo(){
	char sexo;
	
	// pedindo para o usu�rio um char que represente o sexo do piloto
	printf("Digite o sexo do piloto (m -> masculino, f -> feminino): ");
	scanf("%c", &sexo);
	fflush(stdin);
	
	// se for f ou m, ent�o est� v�lido, portanto j� retorna o valor
	if(sexo == 'f' || sexo == 'm') return sexo;
	
	// caso o contr�rio exibe a mensagem de valor inv�lido e repete a fun��o
	printf("Valor inv�lido! Tente novamente...\n");
	return pedeSexo();	
}


