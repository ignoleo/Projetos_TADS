# Sistema para Adoção e Resgate de Animais - SARA

Aplicação de console desenvolvida em linguagem C para cadastrar, pesquisar, remover e listar fichas de animais. Os registros são armazenados em `cadastro_de_fichas.txt` para permanecerem disponíveis quando o programa for encerrado e executado novamente.

## Funcionalidades

- **Cadastrar ficha:** registra os dados de um animal.
- **Pesquisar ficha:** localiza uma ficha pelo código de identificação.
- **Remover ficha:** remove uma ficha usando seu código.
- **Gerar relatório:** exibe o total e os dados das fichas cadastradas.
- **Armazenamento em arquivo:** salva os registros em `cadastro_de_fichas.txt` e carrega os dados ao iniciar o programa.

## Dados armazenados

Cada ficha contém código, nome, espécie, raça, idade, sexo (`M` ou `F`) e condições médicas. O programa define um limite de **1024 fichas** (`NUM_MAX_CAD`).

## Como funciona o armazenamento

O arquivo `cadastro_de_fichas.txt` é criado na pasta de execução do programa, caso ainda não exista.

Ao iniciar, o programa inicializa o vetor, verifica/cria o arquivo e carrega os registros existentes. Depois de um cadastro válido ou de uma remoção, o arquivo é atualizado. Ao sair, o programa também salva os dados.

**Importante:** O arquivo `cadastro_de_fichas.txt` deve ser mantido na pasta de execução do programa. Se o arquivo for movido ou apagado, o programa poderá criar um novo arquivo sem os registros anteriores

## Instalação do Code::Blocks e do compilador C 

O **Code::Blocks é um ambiente de desenvolvimento (IDE)**. Ele permite editar o código e organizar projetos, mas precisa de um compilador C, como o **GCC**, para transformar o código-fonte em um programa executável.

Página oficial: <https://www.codeblocks.org/downloads/binaries/>

### Windows

Para iniciantes, a opção mais simples é instalar o Code::Blocks junto com o MinGW/GCC.

1. Acesse a [página oficial de versões binárias](https://www.codeblocks.org/downloads/binaries/).
2. Na seção **Microsoft Windows (64 bit)**, baixe o instalador cujo nome termina em `mingw-setup.exe` (por exemplo, `codeblocks-25.03mingw-setup.exe`).
3. Execute o arquivo `.exe`.
4. Siga as etapas do instalador e mantenha os componentes padrão selecionados. Confirme que o MinGW/GCC será instalado.
5. Ao terminar, abra o Code::Blocks.
6. Se aparecer uma janela para escolher o compilador, selecione **GNU GCC Compiler** e confirme.

### macOS

**Atenção:** a página oficial informa que a versão Code::Blocks 25.03 para macOS está instável devido à falta de desenvolvedores para essa plataforma. A instalação pode não funcionar corretamente em todos os Macs.

Se quiser tentar:

1. Acesse a [página oficial de versões binárias](https://www.codeblocks.org/downloads/binaries/).
2. Na seção **Mac**, baixe o arquivo `.dmg` disponibilizado.
3. Abra o `.dmg` e siga as instruções de instalação.
4. Para instalar as ferramentas de linha de comando da Apple, abra o **Terminal** e execute:

   ```bash
   xcode-select --install
   ```

5. Siga a janela de instalação. Essas ferramentas disponibilizam o compilador Clang.
6. Abra o Code::Blocks e confira em **Settings > Compiler** se há um compilador configurado. Caso a IDE não reconheça o compilador ou não abra corretamente, consulte a documentação e os fóruns oficiais; a versão para macOS possui limitações conhecidas.

### Linux

No Linux, o Code::Blocks e o GCC podem ser instalados pelo gerenciador de pacotes. Abra o Terminal e use o comando correspondente à sua distribuição.

**Ubuntu, Debian e distribuições derivadas:**

```bash
sudo apt update
sudo apt install codeblocks build-essential gdb
```

**Fedora:**

```bash
sudo dnf install codeblocks gcc gcc-c++ gdb
```

**Arch Linux e distribuições derivadas:**

```bash
sudo pacman -S codeblocks gcc gdb
```

Se o pacote `codeblocks` não estiver disponível no repositório da sua distribuição, consulte a [página oficial de versões binárias](https://www.codeblocks.org/downloads/binaries/) e as instruções específicas da distribuição.

Depois da instalação:

1. Abra o Code::Blocks pelo menu de aplicativos ou pelo Terminal, digitando `codeblocks`.
2. Se a IDE solicitar a escolha de um compilador, selecione **GNU GCC Compiler**.
3. Caso necessário, acesse **Settings > Compiler** e confira se o GCC foi detectado.

**Os comandos variam conforme a distribuição e sua versão. Em algumas distribuições, pode ser necessário habilitar um repositório adicional.**

## Como abrir e executar um arquivo C no Code::Blocks

Há uma diferença entre **abrir um arquivo** para editar e **compilar/executar** um programa. Para compilar, é recomendado utilizar um projeto.

### Opção 1 — Abrir um arquivo `.c` para visualizar ou editar

1. Abra o Code::Blocks.
2. No menu superior, clique em **File > Open**.
3. Localize a pasta onde está salvo o arquivo com extensão `.c` ou `.cbp`.
4. Selecione o arquivo e clique em **Open**.
5. O código será exibido no editor e poderá ser alterado.
6. Para salvar, utilize **File > Save** ou `Ctrl + S` (no macOS, `Command + S`).

> Abrir um arquivo dessa maneira permite visualizá-lo e editá-lo, mas não garante que ele esteja configurado para compilação. Para compilar e executar, siga a opção abaixo.

### Opção 2 — Criar um projeto C e utilizar seu arquivo `.c`

1. Abra o Code::Blocks.
2. Clique em **File > New > Project**.
3. Selecione **Console application** e clique em **Go**.
4. Na tela seguinte, selecione **C** (não C++) e avance.
5. Informe um nome para o projeto e escolha a pasta onde ele será salvo.
6. Na etapa de seleção do compilador, escolha **GNU GCC Compiler**.
7. Conclua a criação do projeto.
8. O Code::Blocks criará um arquivo chamado `main.c`. Abra-o pelo painel **Projects**.
9. Para usar um código existente, abra o arquivo `.c` original em outra aba, copie seu conteúdo e substitua o conteúdo de `main.c`. Outra opção é usar **Project > Add files...** para adicionar o arquivo existente ao projeto. Não mantenha dois arquivos com funções `main()` no mesmo projeto.
10. Salve as alterações com `Ctrl + S` (ou `Command + S` no macOS).
11. Clique em **Build > Build and Run** ou pressione **F9**.
12. Confira a janela **Build log** ou **Build messages**. Se houver erros, corrija-os e compile novamente.

### Teste rápido do compilador

Para verificar se o compilador está funcionando, crie um projeto de Console Application em C e utilize:

```c
#include <stdio.h>

int main(void)
{
    printf("O compilador C está funcionando!\\n");
    return 0;
}
```

Use **Build > Build and Run** (F9). Se a mensagem aparecer no console sem erros de compilação, o ambiente está configurado.

## Estrutura principal do código

- `Ficha`: estrutura que representa os dados de um animal.
- `vetor_fichas`: vetor que armazena até 1024 fichas durante a execução.
- `total_fichas`: quantidade de fichas cadastradas.
- `cadastro_inicializar()`: prepara o vetor e zera o contador.
- `cadastro_inicializar_arquivo()`: define o nome do arquivo e cria-o caso necessário.
- `cadastro_carregar_dados_arquivo()`: recupera as fichas gravadas.
- `cadastro_salvar_dados_arquivo()`: grava no arquivo as fichas ativas.
- `cadastro_inserir_fichas()`: verifica duplicidade e insere uma ficha.
- `cadastro_pesquisar_fichas()`: pesquisa pelo código.
- `cadastro_remover_fichas()`: remove uma ficha pelo código.
- Funções `tela_`: apresentam o menu e as operações ao usuário.
- Funções `leia_`: recebem e validam os dados digitados.

## Referências oficiais

- [Site oficial do Code::Blocks](https://www.codeblocks.org/)
- [Downloads oficiais do Code::Blocks](https://www.codeblocks.org/downloads/)
- [Versões binárias para Windows, Linux e macOS](https://www.codeblocks.org/downloads/binaries/)
- [Documentação oficial do Code::Blocks](https://www.codeblocks.org/docs/main_codeblocks_en3.html)

---

Projeto acadêmico/educacional desenvolvido em linguagem C.
