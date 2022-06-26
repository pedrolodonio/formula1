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

struct Data{
	int ano;
	int mes;
	int dia;
};

struct MelhorVolta{
	int identificacaoPiloto;
	int identificacaoCircuito;
	struct Tempo tempoRecorde;
	struct Data data;
};

struct Circuito{
	// �nico gerado automaticamente com base no �ltimo circuito registrado
	int codigo;
	char nome[100];
	char pais[100];
	int tamanho;
	float tempoRecorde;
	struct MelhorVolta melhorVolta;
};

char pedeSexo();
void pedeNome(char nomePiloto[100], char pedido[50]);
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int incluirMelhorVolta();
int pedeIdPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int pedeIdade();
void pedePais(char paisOrigem[100], char pedido[100]);
void exibePilotos(struct Piloto pilotos[399], int quantidadePilotos);

int main() {
	setlocale(LC_ALL, "Portuguese");
	struct Piloto pilotosRegistrados[399];
	struct Circuito circuitosRegistrados[500];
	int circuitosJaRegistrados = 0;
	int pilotosJaRegistrados = 0;
	int opcaoUsuario;
	
	//	Para o cadastro de um Piloto ou Circuito s� poder�o ser utilizados os pa�ses
	//	previamente cadastrados (seja um vetor pr�-definido ou com o uso de leitura em
	//	arquivos).
	
	while(1){
		
		printf("BEM VINDO AO SISTEMA DA FORMULA 1\n\n");
		printf("1) Cadastrar um novo piloto\n");
		printf("2) Cadastrar um novo circuito\n");
		printf("3) Exibir pilotos cadastrados\n");
		printf("4) Sair do programa\n");
		printf("Digite a sua op��o: ");
		scanf("%i", &opcaoUsuario);
		
		switch(opcaoUsuario){
			case 1: 
				pilotosJaRegistrados = incluiNovoPiloto(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 2:
				circuitosJaRegistrados=incluiNovoCircuito(circuitosRegistrados,circuitosJaRegistrados);
			case 3:
				exibePilotos(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 4: 
				return 0;
				break;
		}
	}
}

// aqui eu vou fazer um programa que exibe todos os pilotos registrados:
void exibePilotos(struct Piloto pilotos[399], int quantidadePilotos){
	
	// para cada um dos pilotos que est�o dentro do vetor passado como argumento para a fun��o
	// ele imprime v�rias informa��es sobre o piloto em quest�o.
	system("CLS");
	printf("============= PILOTOS REGISTRADOS ============\n\n");

	for(int i = 0; i < quantidadePilotos; i++){
		// imprimindo o c�digo do piloto, nome, idade, pa�s de origem e sexo.
		printf("Piloto n�mero: %i\n", pilotos[i].codigo);
		printf("Nome: %s\n", pilotos[i].nome);
		printf("Idade: %d\n", pilotos[i].idade);
		printf("Pa�s de origem: %s\n", pilotos[i].paisOrigem);
		printf("Sexo: ");
		// verifica se o sexo salvo � f, ent�o o piloto � do sexo feminino, caso contr�rio, o sexo do
		// piloto em quest�o � masculino.
		if(pilotos[i].sexo == 'f') 
			printf("feminino\n");
		else printf("masculino\n");
	}
	
	printf("\n============================================\n");
}

int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados){
	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	pedeNome(circuito.nome, "circuito");
	pedePais(circuito.pais, "circuito");
	printf("Digite o tamanho do circuito: ");
	scanf("%f", &circuito.tamanho);
	fflush(stdin);
	// falta incluir as melhores voltas do percurso, que ser� inclu�da em outra funcionalidade, por enquanto
	// o circuito ficar� sem uma melhor volta at� que o usu�rio insira uma em um circuito especifico.
		
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	struct Piloto piloto;
	
	// preenche as informa��es do piloto que est� sendo cadastrado
	piloto.codigo = pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
	pedeNome(piloto.nome, "piloto");
	piloto.idade = pedeIdade();
	pedePais(piloto.paisOrigem, "piloto");
	piloto.sexo = pedeSexo();
	
	// adiciona o piloto criado nessa fun��o dentro do vetor de pilotos.
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	
	// o programa "espera" por 2 segundos para poder voltar ao menu.
	Sleep(2000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}

int incluirMelhorVolta(){
	struct MelhorVolta melhorVolta;
	
	char dataMelhorVoltaString[10];
	printf("Digite a data da melhor volta nesse formato: (dd mm yyyy): ");
	scanf("%[^\n]s", &dataMelhorVoltaString);
	fflush(stdin);
	
	char diaString[2];
	diaString[0] = dataMelhorVoltaString[0];
	diaString[1] = dataMelhorVoltaString[1];
		
	char mesString[2];
	mesString[0] = dataMelhorVoltaString[3];
	mesString[1] = dataMelhorVoltaString[4];

	char anoString[4];
	anoString[0] = dataMelhorVoltaString[6];
	anoString[1] = dataMelhorVoltaString[7];
	anoString[2] = dataMelhorVoltaString[8];
	anoString[3] = dataMelhorVoltaString[9];
	
	melhorVolta.data.dia = atoi(diaString);
	melhorVolta.data.mes = atoi(mesString);
	melhorVolta.data.ano = atoi(anoString);

	return 0;
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
	printf("Idade inv�lida! Tente novamente...\n");
	return pedeIdade();
}

void pedePais(char paisOrigem[100], char pedido[100]){
	int i;
	
	char pais[100];
	strcpy(pais, paisOrigem);
	
	printf("Digite o pa�s de origem do %s: ", pedido);
	scanf("%[^\n]s", &pais);
	fflush(stdin);
	// essa vari�vel indica se o programa encontrou o nome do pa�s que o usu�rio digitou no vetor de pa�ses
	// 0 significa que n�o encontrou, 1 significa que encontrou o nome
	int achou = 0;

	//valida��o do pais origem:

	for(i = 0; i < 20; i++){
		if(strcmp(pais, paises[i]) == 0)
			achou = 1;
	}
	
	if(achou == 0){
		system("CLS");
		printf("N�o conseguimos entender... tente novamente\n");
		pedePais(paisOrigem, pedido);	
	}
}


int pedeIdPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	
	// falta verificar se o id que o usu�rio passou j� foi inclu�do em algum momento, assim evitar a repeti��o do mesmo piloto
	int idPiloto;
	
	// pedindo a identifica��o do piloto
	printf("Numero de identificacao do piloto:");
	scanf("%i",&idPiloto);
	fflush(stdin);
	
	// verifica se o id do piloto est� no intervalo de 100 e 500 (n�o incluso) 
	
	for(int i = 0; i < pilotosJaRegistrados; i++){
		if(idPiloto == pilotosRegistrados[i].codigo){
			system("CLS");
			printf("ERRO! ID J� REGISTRADO, TENTE NOVAMENTE...\n");
			return pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
		}
	}
	if(idPiloto > 100 && idPiloto < 500){
		return idPiloto;
	} else { 
	// se o id do piloto n�o passou pelas verifica��es acima, ent�o o programa limpa a tela, exibe uma mensagem de erro e come�a o processo novamente at� achar um id v�lido
		system("CLS");
		printf("Valor digitado incorreto, tente novamente...\n\n");
		return pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
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
