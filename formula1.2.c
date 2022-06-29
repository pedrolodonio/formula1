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
	float tempoRecorde;
	struct MelhorVolta melhorVolta;
};

char pedeSexo();
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados);
int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int incluirMelhorVolta();
int pedeIdPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados);
int pedeIdade();
void exibePilotos(struct Piloto pilotos[399], int quantidadePilotos);
void exibeCircuitos(struct Circuito circuitos[500],int qntdCircuitos);
void consultaPiloto();

int main() {
	setlocale(LC_ALL, "Portuguese");
	struct Piloto pilotosRegistrados[399];
	struct Circuito circuitosRegistrados[500];
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
		printf("7) Encerrar o programa\n");
		printf("Digite a sua opção: ");
		scanf("%i", &opcaoUsuario);
		
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
			for(x=0;x<pilotosJaRegistrados;x++){
				int retorno= strcmp(pilotosRegistrados[x].nome,consulta);
				if(retorno==0){
						qntdvezes;
 						printf("nome:%s\n",pilotosRegistrados[x].nome);
 						printf("codigo:%d\n",pilotosRegistrados[x].codigo);
						printf("idade:%d\n",pilotosRegistrados[x].idade);
						printf("sexo:%s\n",pilotosRegistrados[x].sexo);
						printf("Pais de origem: %s",pilotosRegistrados[x].paisOrigem);
				}		 
			}	
			
				if(qntdvezes != 0){
					printf("Não existe piloto cadastrado com esse nome.");
					printf("\n\n");}			
				break;
			case 7:
				return 0;
				break;
		}
	}
}

// aqui eu vou fazer um programa que exibe todos os pilotos registrados:
void exibePilotos(struct Piloto pilotos[399], int quantidadePilotos){
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
			printf("feminino\n");
		else printf("masculino\n");
	}
	
	printf("\n============================================\n\n");
	
	system("PAUSE");
}
void exibeCircuitos(struct Circuito circuitos[500],int qntdCircuitos){
	//função que imprime os dados do circuito
	int i;
	system("CLS");
	printf("============= CIRCUITOS REGISTRADOS ============\n\n");

	for(i = 0; i < qntdCircuitos; i++){
		// imprimindo o código,nome,pais e o tamanho do circuito
		printf("Circuito Numero: %d\n", circuitos[i].codigo);
		printf("Nome: %s\n", circuitos[i].nome);
		printf("Pais: %s\n", circuitos[i].pais);
		printf("Tamanho: %i KM\n", circuitos[i].tamanho);
	}
	
	printf("\n============================================\n\n");
	system("PAUSE");
	
	}
	
int incluiNovoCircuito(struct Circuito circuitosRegistrados[500], int circuitosJaRegistrados){
	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	
	// entrada do tamanho do circuito a ser adicionado
	printf("Nome do circuito:");
	scanf("%s",&circuito.nome);
	printf("Pais:");
	scanf("%s",&circuito.pais);
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

int incluiNovoPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	struct Piloto piloto;
	
	// preenche as informações do piloto que está sendo cadastrado
	piloto.codigo = pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
	printf("Nome:");
	scanf("%[^\n]s",&piloto.nome);
	printf("Pais de Origem:");
	scanf("%s",&piloto.paisOrigem);
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

int pedeIdPiloto(struct Piloto pilotosRegistrados[399], int pilotosJaRegistrados){
	
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
	
	// caso o contrário exibe a mensagem de valor inválido e repete a função
	printf("Valor inválido! Tente novamente...\n");
	return pedeSexo();	
}
