# Resultados dos testes

Este arquivo registra os testes feitos com os arquivos da pasta
[`arquivos/entrada`](arquivos/entrada).

Data do teste: 27/05/2026.

Formula usada:

```text
Compactacao (%) = (1 - tamanho_compactado / tamanho_original) * 100
```

## Resumo

| Arquivo de entrada | Tamanho original | Arquivo compactado | Tamanho compactado | Compactacao | Restaurado igual ao original |
| --- | ---: | --- | ---: | ---: | --- |
| [`Alta_repetição.txt`](arquivos/entrada/Alta_repetição.txt) | 276 bytes | [`Alta_repetição.huff`](arquivos/saida/Alta_repetição.huff) | 162 bytes | 41,30% | Sim |
| [`capa_livro.jpg`](arquivos/entrada/capa_livro.jpg) | 59.976 bytes | [`capa_livro.huff`](arquivos/saida/capa_livro.huff) | 61.094 bytes | -1,86% | Sim |
| [`dom_casmurro.txt`](arquivos/entrada/dom_casmurro.txt) | 440.303 bytes | [`dom_casmurro.huff`](arquivos/saida/dom_casmurro.huff) | 248.562 bytes | 43,55% | Sim |

## Arquivos restaurados

| Entrada | Arquivo restaurado |
| --- | --- |
| `Alta_repetição.txt` | [`Alta_repetição_restaurado.txt`](arquivos/restaurados/Alta_repetição_restaurado.txt) |
| `capa_livro.jpg` | [`capa_livro_restaurado.jpg`](arquivos/restaurados/capa_livro_restaurado.jpg) |
| `dom_casmurro.txt` | [`dom_casmurro_restaurado.txt`](arquivos/restaurados/dom_casmurro_restaurado.txt) |

## Observacoes

- O arquivo `dom_casmurro.txt` teve a melhor reducao entre os arquivos maiores,
  com 43,55% de compactacao.
- O arquivo `Alta_repetição.txt` tambem compactou bem, com 41,30% de reducao.
- O arquivo `capa_livro.jpg` ficou 1,86% maior depois da compactacao. Isso e
  esperado em alguns arquivos de imagem, pois o formato JPG ja possui
  compactacao propria.
- Todos os arquivos restaurados foram comparados com os originais usando
  `fc /b` e ficaram identicos byte a byte.
