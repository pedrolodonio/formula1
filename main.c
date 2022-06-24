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
	// único gerado automaticamente com base no último circuito registrado
	int codigo;
	char nome[100];
	char pais[100];
	int tamanho;
	struct MelhorVolta melhorVolta;
};

char pedeSexo();
void pedeNome(char nomePiloto[100], char pedido[50]);
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int incluirMelhorVolta();
int pedeIdPiloto();
int pedeIdade();
void pedePais(char paisOrigem[100], char pedido[100]);

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
	incluirMelhorVolta();
}

int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados){
	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	pedeNome(circuito.nome, "circuito");
	pedePais(circuito.pais, "circuito");
	
	printf("Digite o tamanho do circuito: ");
	scanf("%f", &circuito.tamanho);
	fflush(stdin);
	
	// falta incluir as melhores voltas do percurso, que será incluída em outra funcionalidade, por enquanto
	// o circuito ficará sem uma melhor volta até que o usuário insira uma em um circuito especifico.
		
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	struct Piloto piloto;
	
	// preenche as informações do piloto que está sendo cadastrado
	piloto.codigo = pedeIdPiloto();
	pedeNome(piloto.nome, "piloto");
	piloto.idade = pedeIdade();
	pedePais(piloto.paisOrigem, "piloto");
	piloto.sexo = pedeSexo();
	
	// adiciona o piloto criado nessa função dentro do vetor de pilotos.
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	
	// o programa "espera" por 2 segundos para poder voltar ao menu.
	Sleep(2000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}


/*
Melhor Volta: identifica a melhor volta de um piloto em uma data em um circuito:
- Identificação do piloto
- Identificação do circuito
- Nome da equipe do piloto
- Data da volta com dia, mês e ano.
- Tempo da melhor volta em minutos, segundos e milissegundos;
OBS: Deverá existir um único registro para um piloto em um circuito em uma data. Um
piloto pode realizar várias melhores voltas em um circuito desde que sejam em dias
diferentes.
Universidade Católica de Brasília – UCB
Curso de BCC - Programação Estruturada - Lista #3
Prof. Diego Rodrigues
Eixo de Programação BOM PROJETO
Para o cadastro de um Piloto ou Circuito só poderão ser utilizados os países
previamente cadastrados (seja um vetor pré-definido ou com o uso de leitura em
arquivos).
*/

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
	printf("Idade inválida! Tente novamente...\n");
	return pedeIdade();
}

void pedePais(char paisOrigem[100], char pedido[100]){
	int i;
	
	printf("Digite o país de origem do %s: ", pedido);
	scanf("%[^\n]s", &paisOrigem);
	fflush(stdin);
	// essa variável indica se o programa encontrou o nome do país que o usuário digitou no vetor de países
	// 0 significa que não encontrou, 1 significa que encontrou o nome
	int achou = 0;

	//validação do pais origem:

//	for(i = 0; i < 20; i++){
//		if(strcmp(paisOrigem, paises[i]) == 0)
			achou = 1;
//	}
	
	if(achou == 0){
		system("CLS");
		printf("Não conseguimos entender... tente novamente\n");
		pedePais(paisOrigem, pedido);	
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
