## Autores

Este trabalho foi realizado por:

- Alana Farias: [https://github.com/AlanaF123/](https://github.com/AlanaF123/)
- Eduardo Henrique: [https://github.com/HelloKiw1](https://github.com/HelloKiw1)

# Algoritmo de Huffman

Implementacao em C de um compactador e descompactador de arquivos usando o algoritmo de Huffman.


O programa funciona por linha de comando e possui dois modos:

- `-c`: compacta um arquivo de entrada e gera um arquivo `.huff`
- `-d`: descompacta um arquivo `.huff` e restaura o arquivo original

## Funcionamento basico

O programa recebe argumentos pelo terminal. Primeiro e necessario compilar o arquivo
`huffman.c`. Depois, o usuario escolhe um dos dois modos de execucao:

- `-c` para compactar um arquivo e gerar um arquivo `.huff`
- `-d` para descompactar um arquivo `.huff` e restaurar o conteudo original

Fluxo geral de uso:

1. Compilar o programa.
2. Executar o modo de compactacao com `-c`.
3. Executar o modo de descompactacao com `-d`.
4. Comparar o arquivo original com o arquivo restaurado para verificar se nao houve
   perda de dados.

## Como compilar

No terminal, dentro da pasta do projeto, execute:

```bash
gcc huffman.c -o huffman
```

No Windows, o executavel pode ser gerado como:

```powershell
gcc huffman.c -o huffman.exe
```

## Execucao rapida no Windows

Compactar um arquivo:

```powershell
.\huffman.exe -c .\arquivos\dom_casmurro.txt .\resultados\dom_casmurro.huff
```

Descompactar o arquivo gerado:

```powershell
.\huffman.exe -d .\resultados\dom_casmurro.huff .\resultados\dom_casmurro_restaurado.txt
```

Verificar se o arquivo restaurado ficou igual ao original:

```powershell
fc /b .\arquivos\dom_casmurro.txt .\resultados\dom_casmurro_restaurado.txt
```

## Como compactar

Formato geral:

```bash
./huffman -c arquivo_de_entrada arquivo_compactado.huff
```

Exemplo no Windows:

```powershell
.\huffman.exe -c .\arquivos\dom_casmurro.txt .\resultados\dom_casmurro.huff
```

## Como descompactar

Formato geral:

```bash
./huffman -d arquivo_compactado.huff arquivo_restaurado
```

Exemplo no Windows:

```powershell
.\huffman.exe -d .\resultados\dom_casmurro.huff .\resultados\dom_casmurro_restaurado.txt
```

## Como verificar se funcionou

Depois de descompactar, compare o arquivo original com o arquivo restaurado.

No Windows:

```powershell
fc /b .\arquivos\dom_casmurro.txt .\resultados\dom_casmurro_restaurado.txt
```

Se os arquivos forem iguais, a compactacao e a descompactacao funcionaram corretamente.
No Windows, o comando `fc /b` informa quando nao ha diferencas entre os arquivos.

## Resultados de compactacao

Os resultados dos testes devem ser registrados comparando o tamanho do arquivo original com o tamanho do arquivo `.huff` gerado.

Os resultados dos testes com os arquivos da pasta `arquivos/entrada` estao em
[`RESULTADOS.md`](RESULTADOS.md).

Formula usada:

```text
Compactacao (%) = (1 - tamanho_compactado / tamanho_original) * 100
```
