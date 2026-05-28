# Algoritmo de Huffman

Implementação em C de um compactador e descompactador de arquivos usando o algoritmo de Huffman.

O programa funciona por linha de comando e possui dois modos:

- `-c`: compacta um arquivo de entrada e gera um arquivo `.huff`
- `-d`: descompacta um arquivo `.huff` e restaura o arquivo original

## Funcionamento básico

O programa recebe argumentos pelo terminal. Primeiro é necessário compilar o arquivo
`huffman.c`. Depois, o usuário escolhe um dos dois modos de execução:

- `-c` para compactar um arquivo e gerar um arquivo `.huff`
- `-d` para descompactar um arquivo `.huff` e restaurar o conteúdo original

Fluxo geral de uso:

1. Compilar o programa.
2. Executar o modo de compactação com `-c`.
3. Executar o modo de descompactação com `-d`.
4. Comparar o arquivo original com o arquivo restaurado para verificar se não houve
   perda de dados.

## Como compilar

No terminal, dentro da pasta do projeto, execute:

```bash
gcc huffman.c -o huffman
```

No Windows, o executável pode ser gerado como:

```powershell
gcc huffman.c -o huffman.exe
```

## Execução rápida no Windows

Compactar um arquivo:

```powershell
.\huffman.exe -c .\arquivos\entrada\dom_casmurro.txt .\arquivos\saida\dom_casmurro.huff
```

Descompactar o arquivo gerado:

```powershell
.\huffman.exe -d .\arquivos\saida\dom_casmurro.huff .\arquivos\restaurados\dom_casmurro_pequeno_restaurado.txt
```

Verificar se o arquivo restaurado ficou igual ao original:

```powershell
fc /b .\arquivos\entrada\dom_casmurro.txt .\arquivos\restaurados\dom_casmurro_pequeno_restaurado.txt
```

## Como compactar

Formato geral:

```bash
./huffman -c arquivo_de_entrada arquivo_compactado.huff
```

Exemplo no Windows:

```powershell
.\huffman.exe -c .\arquivos\entrada\dom_casmurro.txt .\arquivos\saida\dom_casmurro.huff
```

## Como descompactar

Formato geral:

```bash
./huffman -d arquivo_compactado.huff arquivo_restaurado
```

Exemplo no Windows:

```powershell
.\huffman.exe -d .\arquivos\saida\dom_casmurro.huff .\arquivos\restaurados\dom_casmurro_pequeno_restaurado.txt
```

## Como verificar se funcionou

Depois de descompactar, compare o arquivo original com o arquivo restaurado.

No Windows:

```powershell
fc /b .\arquivos\entrada\dom_casmurro.txt .\arquivos\restaurados\dom_casmurro_pequeno_restaurado.txt
```

Se os arquivos forem iguais, a compactação e a descompactação funcionaram corretamente.
No Windows, o comando `fc /b` informa quando não há diferenças entre os arquivos.

## Resultados de compactação

Os resultados dos testes foram registrados comparando o tamanho do arquivo original
com o tamanho do arquivo `.huff` gerado.

Data do teste: 27/05/2026.

Fórmula usada:

```text
Compactação (%) = (1 - tamanho_compactado / tamanho_original) * 100
```

Os tamanhos em KB foram calculados considerando `1 KB = 1024 bytes`.

| Arquivo de entrada | Tamanho original (bytes) | Tamanho original (KB) | Arquivo compactado | Tamanho compactado (bytes) | Tamanho compactado (KB) | Compactação | Restaurado igual ao original |
| --- | ---: | ---: | --- | ---: | ---: | ---: | --- |
| [`Alta_repetição.txt`](arquivos/entrada/Alta_repetição.txt) | 276 bytes | 0,27 KB | [`Alta_repetição.huff`](arquivos/saida/Alta_repetição.huff) | 162 bytes | 0,16 KB | 41,30% | Sim |
| [`capa_livro.jpg`](arquivos/entrada/capa_livro.jpg) | 59.976 bytes | 58,57 KB | [`capa_livro.huff`](arquivos/saida/capa_livro.huff) | 61.094 bytes | 59,66 KB | -1,86% | Sim |
| [`dom_casmurro.txt`](arquivos/entrada/dom_casmurro.txt) | 440.303 bytes | 429,98 KB | [`dom_casmurro.huff`](arquivos/saida/dom_casmurro.huff) | 248.562 bytes | 242,74 KB | 43,55% | Sim |
| [`dom_casmurro_grande.txt`](arquivos/entrada/dom_casmurro_grande.txt) | 1.048.521 bytes | 1.023,95 KB | [`dom_casmurro_grande.huff`](arquivos/saida/dom_casmurro_grande.huff) | 591.698 bytes | 577,83 KB | 43,57% | Sim |

## Arquivos restaurados

| Entrada | Arquivo restaurado |
| --- | --- |
| `Alta_repetição.txt` | [`Alta_repetição_restaurado.txt`](arquivos/restaurados/Alta_repetição_restaurado.txt) |
| `capa_livro.jpg` | [`capa_livro_restaurado.jpg`](arquivos/restaurados/capa_livro_restaurado.jpg) |
| `dom_casmurro.txt` | [`dom_casmurro_pequeno_restaurado.txt`](arquivos/restaurados/dom_casmurro_pequeno_restaurado.txt) |
| `dom_casmurro_grande.txt` | [`dom_casmurro_grande_restaurado.txt`](arquivos/restaurados/dom_casmurro_grande_restaurado.txt) |

## Observações

- O arquivo `dom_casmurro_grande.txt` teve a melhor redução, com 43,57% de
  compactação.
- O arquivo `dom_casmurro.txt` teve resultado muito próximo, com 43,55% de
  compactação.
- O arquivo `Alta_repetição.txt` também compactou bem, com 41,30% de redução.
- O arquivo `capa_livro.jpg` ficou 1,86% maior depois da compactação. Isso é
  esperado em alguns arquivos de imagem, pois o formato JPG já possui
  compactação própria.
- Todos os arquivos restaurados foram comparados com os originais e ficaram
  idênticos byte a byte.

## Autores

Este trabalho foi realizado por:

- Alana Farias: [https://github.com/AlanaF123/](https://github.com/AlanaF123/)
- Eduardo Henrique: [https://github.com/HelloKiw1](https://github.com/HelloKiw1)
