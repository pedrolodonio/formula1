#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>
#define MAX_PILOTO 399
#define MAX_CIRCUITO 500
#define MAX_MELHORES_VOLTAS 1500

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
	int idPiloto;
	int idCircuito;
	char equipe[100];
	struct Tempo tempoRecorde;
	struct Data data;
};

struct Circuito{
	// �nico gerado automaticamente com base no �ltimo circuito registrado
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
int incluiMelhorVolta(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados, struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados, struct MelhorVolta melhoresVoltasRegistradas[MAX_MELHORES_VOLTAS], int melhoresVoltasJaRegistradas);
int pedeIdPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados);
int pedeIdade();
void pedePais(char paisOrigem[100], char pedido[100]);
void exibePilotos(struct Piloto pilotos[MAX_PILOTO], int quantidadePilotos);
void exibeCircuitos(struct Circuito circuitos[MAX_CIRCUITO],int qntdCircuitos);
void pedeNome(char nome[100], char pedido[50]);
void exibemelhoresVoltas(struct MelhorVolta volta[MAX_MELHORES_VOLTAS],int qntdvoltas);
void pesquisaPorTempo(struct MelhorVolta melhoresVoltasCadastradas[MAX_MELHORES_VOLTAS], int melhoresVoltasJaCadastradas);


int main() {
	setlocale(LC_ALL, "Portuguese");
	struct Piloto pilotosRegistrados[MAX_PILOTO];
	struct Circuito circuitosRegistrados[MAX_CIRCUITO];
	struct MelhorVolta melhoresVoltasRegistradas[MAX_CIRCUITO];
	
	int circuitosJaRegistrados = 0;
	int pilotosJaRegistrados = 0;
	int melhoresVoltasJaRegistradas = 0;
	int opcaoUsuario;
	int x,qntdvezes;
	char consulta[100];
	//	Para o cadastro de um Piloto ou Circuito s� poder�o ser utilizados os pa�ses
	//	previamente cadastrados (seja um vetor pr�-definido ou com o uso de leitura em
	//	arquivos).
	
	while(1){
		
		//exibe o menu para o usu�rio e pede que ele escolha uma das op��es abaixo:
		system("CLS");
		printf("BEM VINDO AO SISTEMA DA FORMULA 1\n\n");
		printf("1) Cadastrar um novo piloto\n");
		printf("2) Cadastrar um novo circuito\n");
		printf("3) Incluir a melhor volta\n");
		printf("4) Exibir pilotos cadastrados\n");
		printf("5) Exibir circuitos cadastrados\n");
		printf("6) Exibir melhores voltas\n");
		printf("7) Exibir todos os dados cadastrados\n");
		printf("8) Pesquisar piloto por nome\n");
		printf("9) Pesquisar a volta por equipe\n");
		printf("10) Pesquisar por tempo\n");
		printf("11) Encerrar o programa\n");
		printf("Digite a sua op��o: ");
		scanf("%i", &opcaoUsuario);
		fflush(stdin);
		system("CLS");
		
		// baseado no que o usu�rio digitou, um dos caminhos ser� escolhido.
		switch(opcaoUsuario){
			case 1: 
				pilotosJaRegistrados = incluiNovoPiloto(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 2:
				circuitosJaRegistrados=incluiNovoCircuito(circuitosRegistrados,circuitosJaRegistrados);
				break;
			case 3:
				melhoresVoltasJaRegistradas = incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, circuitosJaRegistrados, melhoresVoltasRegistradas, melhoresVoltasJaRegistradas);
				break;
			case 4:
				exibePilotos(pilotosRegistrados, pilotosJaRegistrados);
				break;
			case 5: 
				exibeCircuitos(circuitosRegistrados,circuitosJaRegistrados);
				break;
			case 6:
				exibemelhoresVoltas(melhoresVoltasRegistradas,melhoresVoltasJaRegistradas);
			case 7:
				exibePilotos(pilotosRegistrados, pilotosJaRegistrados);
				exibeCircuitos(circuitosRegistrados,circuitosJaRegistrados);
				exibemelhoresVoltas(melhoresVoltasRegistradas,melhoresVoltasJaRegistradas);
				break;
			case 8:
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
					printf("N�o existe piloto cadastrado com esse nome.");
					printf("\n\n");
				}			
				break;
			case 9:
				printf("digite a equipe que deseja buscar:");
				scanf("%[^\n]s",&consulta);
				fflush(stdin);
				
				qntdvezes = 0;
				for(x=0; x<melhoresVoltasJaRegistradas; x++){
					int retorno= strcmp(melhoresVoltasRegistradas[x].equipe,consulta);
					if(retorno==0){
						qntdvezes;
 						printf("equipe:%s\n",melhoresVoltasRegistradas[x].equipe);
 						printf("piloto:%d\n", melhoresVoltasRegistradas[x].idPiloto);
						printf("circuito:%d\n", melhoresVoltasRegistradas[x].idCircuito);
						printf("tempo recorde:%d:%d,%d \n", melhoresVoltasRegistradas[x].tempoRecorde.minutos,melhoresVoltasRegistradas[x].tempoRecorde.segundos,melhoresVoltasRegistradas[x].tempoRecorde.milisegundos);
						printf("data: %d/%d/%d\n", melhoresVoltasRegistradas[x].data.dia,melhoresVoltasRegistradas[x].data.mes,melhoresVoltasRegistradas[x].data.ano);
						printf("\n\n");
						system("PAUSE");
					}		 
				}	
			
				if(qntdvezes != 0){
					printf("N�o existe equipe cadastrada com esse nome.");
					printf("\n\n");
				}			
				break;
			case 10:
				pesquisaPorTempo(melhoresVoltasRegistradas, melhoresVoltasJaRegistradas);
				break;
			case 11:
				return 0;
				break;
			default: 
				printf("\nValor digitado incorreto, tente novamente...\n");
				system("PAUSE");
				break;
		}
	}
}

void pesquisaPorTempo(struct MelhorVolta melhoresVoltasCadastradas[MAX_MELHORES_VOLTAS], int melhoresVoltasJaCadastradas){
	int i, minutos, segundos, milisegundos, ehMenor;
	
	printf("================== PESQUISA POR TEMPO ================\n");
	
	// entrada dos minutos
	printf("Digite os minutos");
	scanf("%i", &minutos);
	fflush(stdin);
	
	// entrada dos segundos
	printf("Digite os segundos");
	scanf("%i", &segundos);
	fflush(stdin);
	
	// entrada dos milisegundos
	printf("Digite os milisegundos");
	scanf("%i", &milisegundos);
	fflush(stdin);
	
	printf("\n");
	// loop que verifica quais s�o as voltas cujo tempo � menor do que o que foi passado pelo usu�rio
	for(i = 0; i < melhoresVoltasJaCadastradas; i++){
		struct MelhorVolta volta = melhoresVoltasCadastradas[i];
		ehMenor = 0;
		
		if(minutos > volta.tempoRecorde.minutos){
			ehMenor = 1;
		} else if (minutos == volta.tempoRecorde.minutos){
			if(segundos > volta.tempoRecorde.segundos){
				ehMenor = 1;
			} else if(segundos == volta.tempoRecorde.segundos){
				if(milisegundos > volta.tempoRecorde.milisegundos){
					ehMenor = 1;
				}
			}
		}
		
		if(ehMenor = 1){
			printf("Equipe: %s\n", volta.equipe);
			printf("Id do circuito: %i\n", volta.idCircuito);
			printf("Id do piloto: %i\n", volta.idPiloto);
			printf("Data: %i/%i/%i\n", volta.data.dia, volta.data.mes, volta.data.ano);
			printf("Tempo: %i:%i,%i\n\n", volta.tempoRecorde.minutos, volta.tempoRecorde.segundos, volta.tempoRecorde.milisegundos);
		}
	}
	system("PAUSE");
}


// essa fun��o exibe todos os pilotos registrados, recebe o vetor de pilotos cadastrados e a quantidade de pilotos j� cadastrados
void exibePilotos(struct Piloto pilotos[MAX_PILOTO], int quantidadePilotos){
	int i;
	// para cada um dos pilotos que est�o dentro do vetor passado como argumento para a fun��o
	// ele imprime v�rias informa��es sobre o piloto em quest�o.
	system("CLS");
	printf("============= PILOTOS REGISTRADOS ============\n\n");

	for(i = 0; i < quantidadePilotos; i++){
		struct Piloto piloto = pilotos[i];
		// imprimindo o c�digo do piloto, nome, idade, pa�s de origem e sexo.
		printf("Piloto n�mero: %i\n", piloto.codigo);
		printf("Nome: %s\n", piloto.nome);
		printf("Idade: %d\n", piloto.idade);
		printf("Pa�s de origem: %s\n", piloto.paisOrigem);
		printf("Sexo: ");
		// verifica se o sexo salvo � f, ent�o o piloto � do sexo feminino, caso contr�rio, o sexo do
		// piloto em quest�o � masculino.
		if(piloto.sexo == 'f') 
			printf("feminino");
		else printf("masculino");
		printf("\n\n");
	}
	
	printf("\n============================================\n\n");
	
	// pausa o programa esperando uma entrada do usu�rio para prosseguir o programa normalmente.
	system("PAUSE");
}
void exibeCircuitos(struct Circuito circuitos[MAX_CIRCUITO],int qntdCircuitos){
	//fun��o que imprime os dados do circuito
	int i;
	system("CLS");
	printf("============= CIRCUITOS REGISTRADOS ============\n\n");

	for(i = 0; i < qntdCircuitos; i++){
		// imprimindo o c�digo,nome,pais e o tamanho do circuito
		printf("Circuito Numero: %d\n", circuitos[i].codigo);
		printf("Nome: %s\n", circuitos[i].nome);
		printf("Pais: %s\n", circuitos[i].pais);
		printf("Tamanho: %i KM", circuitos[i].tamanho);
		printf("\n\n");
	}
	
	printf("\n===============================================\n\n");
	
	// pausa o programa esperando uma entrada do usu�rio para prosseguir o programa normalmente.
	system("PAUSE");
}
	
int incluiNovoCircuito(struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados){
	printf("====== INCLUIR UM NOVO CIRCUITO ========\n\n");

	struct Circuito circuito;
	
	circuito.codigo = circuitosJaRegistrados;
	// entrada do tamanho do circuito a ser adicionado
	pedeNome(circuito.nome, "circuito");
	pedePais(circuito.pais, "circuito");
	printf("Digite o tamanho do circuito: ");
	scanf("%d", &circuito.tamanho);
	fflush(stdin);
	
	// falta incluir as melhores voltas do percurso, que ser� inclu�da em outra funcionalidade, por enquanto
	// o circuito ficar� sem uma melhor volta at� que o usu�rio insira uma em um circuito especifico.
	
	circuitosRegistrados[circuitosJaRegistrados] = circuito;
	
	//exibe mensagem de sucesso, deixa esperar 2 segundos e depois retorna o valor passado da quantidade de circuitos j� registrados no sistema somando 1
	printf("\n\nCircuito adicionado com sucesso!");
	Sleep(2000);
	return circuitosJaRegistrados + 1;
}

int incluiNovoPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados){
	printf("====== INCLUIR UM NOVO PILOTO ========\n\n");
	struct Piloto piloto;
	
	// preenche as informa��es do piloto que est� sendo cadastrado
	piloto.codigo = pedeIdPiloto(pilotosRegistrados, pilotosJaRegistrados);
	pedeNome(piloto.nome, "piloto");
	printf("Reino Unido\n Alemanha\n Brasil\n Argentina\n Fran�a\n �ustria\n Austr�lia\n Finl�ndia\n It�lia\n Espanha\n Estados Unidos\n Canad�\n �frica do Sul\n Nova Zel�ndia\n Pa�ses Baixos\n");	
	pedePais(piloto.paisOrigem, "piloto");
	piloto.idade = pedeIdade();
	piloto.sexo = pedeSexo();
	
	// adiciona o piloto criado nessa fun��o dentro do vetor de pilotos.
	pilotosRegistrados[pilotosJaRegistrados] = piloto;
	printf("\nPiloto Registrado com sucesso!");
	
	// o programa "espera" por 2 segundos para poder voltar ao menu.
	Sleep(2000);

	system("CLS");
	return pilotosJaRegistrados + 1;
}

int incluiMelhorVolta(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados, struct Circuito circuitosRegistrados[MAX_CIRCUITO], int circuitosJaRegistrados, struct MelhorVolta melhoresVoltasRegistradas[MAX_MELHORES_VOLTAS], int melhoresVoltasJaRegistradas){
	struct MelhorVolta melhorVolta;	
	int idPiloto, idCircuito, i;

	if(pilotosJaRegistrados == 0 || circuitosJaRegistrados == 0){
		printf("ERRO! Pilotos ou circuitos insuficiente para realizar a opera��o...\n\n");
		system("PAUSE");
		return 0;
	}
	
	// pedindo a data da melhor volta e o tempo de percurso dela
	printf("insira dia dd: ");
	scanf("%d",&melhorVolta.data.dia);
	printf("insira mes mm: ");
	scanf("%d",&melhorVolta.data.mes);
	printf("insira ano aaaa: ");
	scanf("%d",&melhorVolta.data.ano);
	printf("minutos: ");
	scanf("%d",&melhorVolta.tempoRecorde.minutos);
	printf("segundos: ");
	scanf("%d",&melhorVolta.tempoRecorde.segundos);
	printf("milisegundos: ");
	scanf("%d",&melhorVolta.tempoRecorde.milisegundos);
	
	printf("tempo recorde minuos, segundos, mili: %d, %d, %d\n", melhorVolta.tempoRecorde.minutos, melhorVolta.tempoRecorde.segundos, melhorVolta.tempoRecorde.milisegundos);

	
	printf("Digite o id do piloto que realizou essa volta: ");
	scanf("%d", &idPiloto);
	fflush(stdin);
	
	printf("Digite o id do circuito que foi realizado essa volta: ");
	scanf("%d", &idCircuito);
	fflush(stdin);
	
	printf("Digite a equipe do piloto que realizou essa volta: ");
	scanf("%s", &melhorVolta.equipe);
	fflush(stdin);
	
	// essa parte � para verificar se ambos os ids existem de fato:
	
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
		printf("Erro! Id passado � inv�lido...\n");
		incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, 
		circuitosJaRegistrados, melhoresVoltasRegistradas, melhoresVoltasJaRegistradas);
	}
	
	//2) verificar se o id do circuito existe: 
	// se o id passado � menor do que a quantidade de circuitos que j� foram registrados, ou id � menor que 0, ent�o o id passado � inv�lido.
	if(!(idCircuito < circuitosJaRegistrados && idCircuito >= 0)){
		system("PAUSE");
		printf("Erro! Id passado � inv�lido CIRCUITO...\n");
		incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados, circuitosJaRegistrados, melhoresVoltasRegistradas, melhoresVoltasJaRegistradas);
	}
	
	// essa parte existe para verificar se ambos os ids j� foram encontradas em outra melhor volta.
	for(i = 0; i < melhoresVoltasJaRegistradas; i++){
		// primeiro passo � verificar se a melhor volta dessa posi��o tem os mesmos ids da passada pelo usu�rio
		if(melhoresVoltasRegistradas[i].idPiloto == idPiloto && 
			melhoresVoltasRegistradas[i].idCircuito == idCircuito
		){
			if(melhorVolta.tempoRecorde.minutos > melhoresVoltasRegistradas[i].tempoRecorde.minutos){
				system("CLS");
				printf("N�o � a melhor volta que esse piloto j� fez nesse percurso...\n\n");
				system("PAUSE");
				system("CLS");
				return incluiMelhorVolta(pilotosRegistrados, pilotosJaRegistrados, circuitosRegistrados,
				circuitosJaRegistrados, melhoresVoltasRegistradas, melhoresVoltasJaRegistradas);
			}
		}
		
	}
	
	melhorVolta.idCircuito = idCircuito;
	melhorVolta.idPiloto = idPiloto;
	
	melhoresVoltasRegistradas[melhoresVoltasJaRegistradas] = melhorVolta;
	melhoresVoltasJaRegistradas++;
	
	printf("\n");
	system("PAUSE");
	return melhoresVoltasJaRegistradas;
}

void exibemelhoresVoltas(struct MelhorVolta volta[MAX_MELHORES_VOLTAS],int qntdvoltas){
	int i;
	system("CLS");
	printf("============= VOLTAS REGISTRADAS ============\n\n");

	for(i = 0; i < qntdvoltas; i++){
		// imprimindo o c�digo,nome,pais e o tamanho do circuito
		printf("data:%d/%d/%d", volta[i].data.dia,volta[i].data.mes,volta[i].data.ano);
		printf("piloto: %s\n", volta[i].idPiloto);
		printf("Pais: %s\n", volta[i].idCircuito);
		printf("equipe:", volta[i].equipe);
		printf("\n\n");
	}
	
	printf("\n===============================================\n\n");
	
	// pausa o programa esperando uma entrada do usu�rio para prosseguir o programa normalmente.
	system("PAUSE");
}

int pedeIdade(){
	int idade;
	
	// entrada da idade do piloto
	printf("Digite a idade do piloto: ");
	scanf("%i", &idade);
	fflush(stdin);
	
	// valida a idade passada pelo usu�rio, caso ela esteja nos padr�es, a fun��o retorna a idade passada
	// pelo usu�rio, caso contr�rio, o c�digo abaixo � executado
	if(idade > 0 && idade < 200) return idade;
	// limpa a tela e escreve que a idade � inv�lida e chama a mesma fun��o novamente.
	system("CLS");
	printf("Idade inv�lida! Tente novamente...\n");
	return pedeIdade();
}

int pedeIdPiloto(struct Piloto pilotosRegistrados[MAX_PILOTO], int pilotosJaRegistrados){
	
	// falta verificar se o id que o usu�rio passou j� foi inclu�do em algum momento, assim evitar a repeti��o do mesmo piloto
	int idPiloto, i;
	
	// pedindo a identifica��o do piloto
	printf("Numero de identificacao do piloto:");
	scanf("%i",&idPiloto);
	fflush(stdin);
	
	// verifica se o id do piloto est� no intervalo de 100 e 500 (n�o incluso) 
	
	for(i = 0; i < pilotosJaRegistrados; i++){
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
	
	// caso o contr�rio: limpa a tela, exibe a mensagem de valor inv�lido e repete a fun��o
	system("CLS");
	printf("Valor inv�lido! Tente novamente...\n");
	return pedeSexo();	
}

void pedePais(char paisOrigem[100], char pedido[100]){
	int i;
	// entrada do pa�s de origem
	printf("Digite o pa�s de origem do %s: ", pedido);
	scanf("%[^\n]s", paisOrigem);
	fflush(stdin);
	// essa vari�vel indica se o programa encontrou o nome do pa�s que o usu�rio digitou no vetor de pa�ses
	// 0 significa que n�o encontrou, 1 significa que encontrou o nome
	int achou = 0;

	//verifica se o pa�s de origem est� dentro da lista de pa�ses
	for(i = 0; i < 20; i++){
		if(strcmp(paisOrigem, paises[i]) == 0)
			achou = 1;
	}
	
	// se n�o achou o pa�s na lista, ent�o:
	if(achou == 0){
		// limpa a tela, imprime mensagem de erro e chama a fun��o novamente.
		system("CLS");
		printf("N�o conseguimos entender... tente novamente\n");
		pedePais(paisOrigem, pedido);	
	}
}

// fun��o feita para pedir algum nome, a string de pedido serve para se passar o que est� sendo pedido
void pedeNome(char nome[100], char pedido[50]){
	// entrada do nome
	printf("Digite o nome do %s: ", pedido);
	scanf("%[^\n]s", nome);
	fflush(stdin);
}
