#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Estrutura com todos os dados da agenda*/
struct Pessoa{
    char nome[105];
    char telefone[20];
    char email[50];
    char sexo;
    int idade;
    float peso;
    float altura;
    int ok;
};
typedef struct Pessoa pessoa;

void visualizar(){
    /*Abrinso o arquivo e verificando se ele é valido*/
   FILE *arquivo = fopen("cliente.txt","r");
    pessoa contato, aux, *pessoas;
   int total = 0, k = 0, i, j;
    if (arquivo != NULL){
        /*Esse bloco verifica a quantidade de registros e salva no vetor*/    
        while(fread(&contato,sizeof(pessoa),1,arquivo))
            if (contato.ok == 1)
                total++;
        if (total != 0){
            pessoas = malloc(total*sizeof(pessoa));
            rewind(arquivo);

            while(fread(&contato,sizeof(pessoa),1,arquivo))
                if (contato.ok == 1)
                    pessoas[k++] = contato;

            fclose(arquivo);
            /*Ordenando o vetor e imprimindo na tela*/  
            printf("****VISUALIZAR TODOS OS CONTATOS****\n");  
            for(i=0 ; i< total ; i++)
                for(j=0 ; j < total; j++)
                    if(strcmp(pessoas[i].nome, pessoas[j].nome) == -1){
                        aux = pessoas[i];
                        pessoas[i] = pessoas[j];
                        pessoas[j] = aux;
                    }
                        

                for(i=0; i < total; i++){
                    printf("%s\n%s\n%s\n%c\n", pessoas[i].nome, pessoas[i].telefone, pessoas[i].email, pessoas[i].sexo);
                    printf("%d\n%.2f\n%.2f\n",pessoas[i].idade,pessoas[i].peso,pessoas[i].altura);
                }
        }
        else
            printf("****Agenda Vazia!****\n");
    }
    else
        printf("Arquivo não encontrado");
}
void pesquisar(){
/*Abrindo o arquivo*/
    FILE *arquivo = fopen("cliente.txt","r");
    pessoa contato;
    char chave[102];
    int flag=1;
    
    printf("****PESQUISAR CONTATO****\n");
    printf("Digite o nome da busca:\n");
    /*Lendo o nome para busca*/
    if (arquivo != NULL){
        setbuf(stdin,0);
        fflush(stdin);
        while(getchar() != '\n');
        fgets(chave, 102, stdin);
        strtok(chave,"\n");
        /*Verificando se o nome digitado pelo usuario consta salvo no arquivo*/
        while(fread(&contato,sizeof(pessoa),1,arquivo))
            if (contato.ok == 1)
                if (strcmp(chave,contato.nome)==0){
                    printf("%s\n%s\n%s\n%c\n",contato.nome, contato.telefone, contato.email,contato.sexo);
                    printf("%d\n%.2f\n%.2f\n",contato.idade,contato.peso,contato.altura);
                    flag=0;
                    break;
                }
        if (flag==1)
            printf("****Nome nao encontrado!****\n");
        fclose(arquivo);
    }
    else
        printf("Arquivo não encontrado");
}

void excluir(){
    FILE *arquivo = fopen("cliente.txt", "r+");
    char chave[102];
    int flag = 1;
    pessoa contato;
    /*Recebe o nome que deve ser excluido*/
    printf("****EXCLUIR CONTATO****\n");
    printf("Digite o nome da exclusão:\n");
    setbuf(stdin,0);
    fgets(chave, 102, stdin);
    strtok(chave,"\n");
    /*Verifica queo nome que deve ser exluido consta salvo no arquivo*/
    while(fread(&contato, sizeof(pessoa), 1, arquivo))
        if (contato.ok == 1)
            if (strcmp(chave,contato.nome)==0){
                contato.ok = 0;
                fseek(arquivo, -1*sizeof(pessoa), SEEK_CUR);
                fwrite(&contato, sizeof(pessoa), 1, arquivo);
                flag = 0;
                break;
            }
    if (flag==1)
        printf("****Nome nao encontrado!****\n");

    fclose(arquivo);
}

void adicionar(){
    FILE *arquivo; 
    pessoa contato;
    /*Recebe todas as informações dos contatos*/
    printf("****ADICIONAR CONTATO****\n");
    printf("Digite o nome:\n");
    setbuf(stdin,0);
    fflush(stdin);
    while(getchar() != '\n');
    fgets(contato.nome, 105, stdin);
    strtok(contato.nome,"\n");
    printf("Digite o telefone (formato: (XX) XXXX-XXXX):\n");
    fgets(contato.telefone, 20, stdin);
    strtok(contato.telefone,"\n");
    printf("Digite e-mail:\n");
    fgets(contato.email,50,stdin);
    strtok(contato.email,"\n");
    printf("Digite o sexo:\n");
    scanf(" %c", &contato.sexo);
    printf("Digite a idade:\n");
    scanf("%d", &contato.idade);
    printf("Digite o peso:\n");
    scanf("%f", &contato.peso);
    printf("Digite a altura:\n");
    scanf("%f",&contato.altura);
    contato.ok = 1;
    arquivo = fopen ("cliente.txt", "a+"); 
    if (arquivo == NULL) {
        printf("Arquivo CLIENTE.TXT nao pode ser aberto.");
    } 
    else {
        fwrite(&contato,sizeof(pessoa),1,arquivo);
        fclose (arquivo);

    }

}

int main(){

    int op;
     /*Bloco de comandos em que o usuario escolhe a opção desejada*/   
    do{
    
        printf("****MENU AGENDA ELETRONICA****\n");
        printf("1: Adicionar contato\n");
        printf("2: Excluir contato\n");
        printf("3: Pesquisar contato\n");
        printf("4: Visualizar todos os contatos\n");
        printf("0: Sair!\n");
        
        scanf("%d", &op);
        
        setbuf(stdin,0);
        fflush(stdin);

        switch (op)
            {
            case 1: adicionar();break; 
            case 2: excluir();break;
            case 3: pesquisar();break;
            case 4: visualizar();break;
            case 0: remove("cliente.txt"); break;
            default:printf("****Opcao Invalida, tentar novamente****\n");break;
            }     
    
    
        }while(op!=0);          
    
            
return 0;
}

