#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>
#define MAX_PILOTO 399
#define MAX_CIRCUITO 500

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
	struct Tempo tempoRecorde;
	struct MelhorVolta *melhorVolta;
};

char pedeSexo();
int incluiNovoCircuito(struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados);
int incluiMelhorVolta(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados, struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados);
int pedeIdPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados);
int pedeIdade();
void pedePais(char paisOrigem[100], char pedido[100]);
void exibePilotos(struct Piloto pilotos[MAX_PILOTO], int quantidadePilotos);
void exibeCircuitos(struct Circuito circuitos[MAX_CIRCUITO],int qntdCircuitos);
void pedeNome(char nome[100], char pedido[50]);

int main() {
	setlocale(LC_ALL, "Portuguese");
	struct Piloto pilotosRegistrados[MAX_PILOTO];
	struct Circuito circuitosRegistrados[MAX_CIRCUITO];
	int circuitosJaRegistrados = 0;
	int pilotosJaRegistrados = 0;
	int opcaoUsuario;
	int x,qntdvezes;
	char consulta[100];
	//	Para o cadastro de um Piloto ou Circuito só poderão ser utilizados os países
	//	previamente cadastrados (seja um vetor pré-definido ou com o uso de leitura em
	//	arquivos).
	
	while(1){
		
		//exibe o menu para o usuário e pede que ele escolha uma das opções abaixo:
		system("CLS");
		printf("BEM VINDO AO SISTEMA DA FORMULA 1\n\n");
		printf("1) Cadastrar um novo piloto\n");
		printf("2) Cadastrar um novo circuito\n");
		printf("3) Exibir pilotos cadastrados\n");
		printf("4) Exibir circuitos cadastrados\n");
		printf("5) Exibir todos os dados cadastrados\n");
		printf("6) Pesquisar piloto por nome\n");
		printf("7) Incluir a melhor volta\n");
		printf("8) Encerrar o programa\n");
		printf("Digite a sua opção: ");
		scanf("%i", &opcaoUsuario);
		fflush(stdin);
		system("CLS");
		
		// baseado no que o usuário digitou, um dos caminhos será escolhido.
		switch(opcaoUsuario){
			case 1: 
				pilotosJaRegistrados = incluiNovoPiloto(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 2:
				circuitosJaRegistrados=incluiNovoCircuito(circuitosRegistrados,circuitosJaRegistrados);
				break;
			case 3:
				exibePilotos(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 4: 
				exibeCircuitos(circuitosRegistrados,circuitosJaRegistrados);
				break;
			case 5:
				exibePilotos(pilotosRegistrados, pilotosJaRegistrados);
				exibeCircuitos(circuitosRegistrados,circuitosJaRegistrados);
				break;
			case 6:
				printf("digite o piloto que deseja buscar:");
				scanf("%[^\n]s",&consulta);
				fflush(stdin);
				
				qntdvezes = 0;
				for(x=0; x<pilotosJaRegistrados; x++){
					int retorno= strcmp(pilotosRegistrados[x].nome,consulta);
					if(retorno==0){
						qntdvezes;
 						printf("nome:%s\n", pilotosRegistrados[x].nome);
 						printf("codigo:%d\n", pilotosRegistrados[x].codigo);
						printf("idade:%d\n", pilotosRegistrados[x].idade);
						printf("sexo:%c\n", pilotosRegistrados[x].sexo);
						printf("Pais de origem: %s\n", pilotosRegistrados[x].paisOrigem);
						printf("\n\n");
						system("PAUSE");
					}		 
				}	
			
				if(qntdvezes != 0){
					printf("Não existe piloto cadastrado com esse nome.");
					printf("\n\n");
				}			
				break;
			case 7:
				incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, circuitosJaRegistrados);
				break;
			case 8:
				return 0;
				break;
			default: 
				printf("\nValor digitado incorreto, tente novamente...\n");
				system("PAUSE");
				break;
		}
	}
}

// essa função exibe todos os pilotos registrados, recebe o vetor de pilotos cadastrados e a quantidade de pilotos já cadastrados
void exibePilotos(struct Piloto pilotos[MAX_PILOTO], int quantidadePilotos){
	int i;
	// para cada um dos pilotos que estão dentro do vetor passado como argumento para a função
	// ele imprime várias informações sobre o piloto em questão.
	system("CLS");
	printf("============= PILOTOS REGISTRADOS ============\n\n");

	for(i = 0; i < quantidadePilotos; i++){
		struct Piloto piloto = pilotos[i];
		// imprimindo o código do piloto, nome, idade, país de origem e sexo.
		printf("Piloto número: %i\n", piloto.codigo);
		printf("Nome: %s\n", piloto.nome);
		printf("Idade: %d\n", piloto.idade);
		printf("País de origem: %s\n", piloto.paisOrigem);
		printf("Sexo: ");
		// verifica se o sexo salvo é f, então o piloto é do sexo feminino, caso contrário, o sexo do
		// piloto em questão é masculino.
		if(piloto.sexo == 'f') 
			printf("feminino");
		else printf("masculino");
		printf("\n\n");
	}
	
	printf("\n============================================\n\n");
	
	// pausa o programa esperando uma entrada do usuário para prosseguir o programa normalmente.
	system("PAUSE");
}
void exibeCircuitos(struct Circuito circuitos[MAX_CIRCUITO],int qntdCircuitos){
	//função que imprime os dados do circuito
	int i;
	system("CLS");
	printf("============= CIRCUITOS REGISTRADOS ============\n\n");

	for(i = 0; i < qntdCircuitos; i++){
		// imprimindo o código,nome,pais e o tamanho do circuito
		printf("Circuito Numero: %d\n", circuitos[i].codigo);
		printf("Nome: %s\n", circuitos[i].nome);
		printf("Pais: %s\n", circuitos[i].pais);
		printf("Tamanho: %i KM", circuitos[i].tamanho);
		printf("\n\n");
	}
	
	printf("\n===============================================\n\n");
	
	// pausa o programa esperando uma entrada do usuário para prosseguir o programa normalmente.
	system("PAUSE");
}
	
int incluiNovoCircuito(struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados){
	printf("====== INCLUIR UM NOVO CIRCUITO ========\n\n");

	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
//	fflush(stdin);
	// entrada do tamanho do circuito a ser adicionado
	pedeNome(circuito.nome, "circuito");
	pedePais(circuito.pais, "circuito");
	printf("Digite o tamanho do circuito: ");
	scanf("%d", &circuito.tamanho);
	fflush(stdin);
	
	// falta incluir as melhores voltas do percurso, que será incluída em outra funcionalidade, por enquanto
	// o circuito ficará sem uma melhor volta até que o usuário insira uma em um circuito especifico.
	
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	
	//exibe mensagem de sucesso, deixa esperar 2 segundos e depois retorna o valor passado da quantidade de circuitos já registrados no sistema somando 1
	printf("\n\nCircuito adicionado com sucesso!");
	Sleep(2000);
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados){
	printf("====== INCLUIR UM NOVO PILOTO ========\n\n");
	struct Piloto piloto;
	
	// preenche as informações do piloto que está sendo cadastrado
	piloto.codigo = pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
	pedeNome(piloto.nome, "piloto");
	pedePais(piloto.paisOrigem, "piloto");
	piloto.idade = pedeIdade();
	piloto.sexo = pedeSexo();
	
	// adiciona o piloto criado nessa função dentro do vetor de pilotos.
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	
	// o programa "espera" por 2 segundos para poder voltar ao menu.
	Sleep(2000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}

int incluiMelhorVolta(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados, struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados){
	if(pilotosJaRegistrados == 0 || circuitosJaRegistrados == 0){
		printf("ERRO! Pilotos ou circuitos insuficiente para realizar a operação...\n\n");
		system("PAUSE");
		return 0;
	}
	
	struct MelhorVolta melhorVolta;
	
	char dataMelhorVoltaString[10], tempoString[8];
	int idPiloto, idCircuito, i;
	
	printf("Digite o id do piloto que realizou essa volta: ");
	scanf("%i", &idPiloto);
	fflush(stdin);
	
	printf("Digite o id do circuito que foi realizado essa volta: ");
	scanf("%i", &idCircuito);
	fflush(stdin);
	
	// essa parte é para verificar se ambos os ids existem de fato:
	
	//1) verificar se o id do piloto existe: 
	int idPilotoExiste = 0;
	for(i = 0; i < pilotosJaRegistrados; i++){
		if(pilotosRegistrados[i].codigo == idPiloto){
			idPilotoExiste = 1;
			break;
		}
	}
	if(idPilotoExiste == 0){
		system("PAUSE");
		printf("Erro! Id passado é inválido...\n");
		incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, circuitosJaRegistrados);
	}
	
	//2) verificar se o id do circuito existe: 
	// se o id passado é menor do que a quantidade de circuitos que já foram registrados, ou id é menor que 0, então o id passado é inválido.
	if(!(idCircuito < circuitosJaRegistrados && idCircuito >= 0)){
		system("PAUSE");
		printf("Erro! Id passado é inválido CIRCUITO...\n");
		incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, circuitosJaRegistrados);
	}
	
	
	// essa parte existe para verificar se ambos os ids já foram encontradas em outra melhor volta.
	
	
	// pedaço de código para encontrar data da melhor volta: 
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
	
	// pedaço de código para encontrar o tempo dessa volta: 
	printf("Digite o tempo da volta nesse formato: (mm ss ms): ");
	scanf("%[^\n]s", &tempoString);
	fflush(stdin);
	
	char minutoString[2];
	minutoString[0] = tempoString[0];
	minutoString[1] = tempoString[1];
		
	char segundoString[2];
	segundoString[0] = tempoString[3];
	segundoString[1] = tempoString[4];

	char milissegundoString[4];
	milissegundoString[0] = tempoString[6];
	milissegundoString[1] = tempoString[7];

	melhorVolta.tempoRecorde.minutos = atoi(minutoString);
	melhorVolta.tempoRecorde.segundos = atoi(segundoString);
	melhorVolta.tempoRecorde.milisegundos = atoi(milissegundoString);
	
	printf("\n");
	system("PAUSE");
	return 0;
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

int pedeIdPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados){
	
	// falta verificar se o id que o usuário passou já foi incluído em algum momento, assim evitar a repetição do mesmo piloto
	int idPiloto, i;
	
	// pedindo a identificação do piloto
	printf("Numero de identificacao do piloto:");
	scanf("%i",&idPiloto);
	fflush(stdin);
	
	// verifica se o id do piloto está no intervalo de 100 e 500 (não incluso) 
	
	for(i = 0; i < pilotosJaRegistrados; i++){
		if(idPiloto == pilotosRegistrados[i].codigo){
			system("CLS");
			printf("ERRO! ID JÁ REGISTRADO, TENTE NOVAMENTE...\n");
			return pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
		}
	}
	if(idPiloto > 100 && idPiloto < 500){
		return idPiloto;
	} else { 
	// se o id do piloto não passou pelas verificações acima, então o programa limpa a tela, exibe uma mensagem de erro e começa o processo novamente até achar um id válido
		system("CLS");
		printf("Valor digitado incorreto, tente novamente...\n\n");
		return pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
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
	
	// caso o contrário: limpa a tela, exibe a mensagem de valor inválido e repete a função
	system("CLS");
	printf("Valor inválido! Tente novamente...\n");
	return pedeSexo();	
}

void pedePais(char paisOrigem[100], char pedido[100]){
	int i;
	// entrada do país de origem
	printf("Digite o país de origem do %s: ", pedido);
	scanf("%[^\n]s", paisOrigem);
	fflush(stdin);
	// essa variável indica se o programa encontrou o nome do país que o usuário digitou no vetor de países
	// 0 significa que não encontrou, 1 significa que encontrou o nome
	int achou = 0;

	//verifica se o país de origem está dentro da lista de países
	for(i = 0; i < 20; i++){
		if(strcmp(paisOrigem, paises[i]) == 0)
			achou = 1;
	}
	
	// se não achou o país na lista, então:
	if(achou == 0){
		// limpa a tela, imprime mensagem de erro e chama a função novamente.
		system("CLS");
		printf("Não conseguimos entender... tente novamente\n");
		pedePais(paisOrigem, pedido);	
	}
}

// função feita para pedir algum nome, a string de pedido serve para se passar o que está sendo pedido
void pedeNome(char nome[100], char pedido[50]){
	// entrada do nome
	printf("Digite o nome do %s: ", pedido);
	scanf("%[^\n]s", nome);
	fflush(stdin);
}
