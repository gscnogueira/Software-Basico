# Trabalho 1 (Montador + Ligador)

- Gabriel da Silva Corvino Nogueira (180113330)
- Rodrigo Silva Lopes Zedes (180139380)


## Observações

- As linhas indicadas nas mensagens de erro são referentes ao arquivo pré-processado (terminado com `_preprocessor.asm`)
- Foi utilizada a instrução `MUL`
- Sistema Operacional Utilizado: Linux

## Montador

### Compilando 

```sh
cd Montador/
make 
```

### Executando
Para montar um ou mais arquivos, deve-se fornecer apenas o seu nome, **sem a extensão**. Por exemplo, para montar os arquivos `mod_a.asm` e `mod_b.asm`, faça:

```sh
./montador mod_a mod_b 
```

No caso de módulos, serão gerados os arquivos `mod_a_preprocessor` e `mod_a_preprocessor`, que são os arquivos pré-processados, além dos arquivos `mod_a.obj` e `mod_b.obj`, os arquivos objeto.

No caso de programas que não são módulos (não possuem as diretivas `BENGIN` e `END`), será gerado um arquivo executável.
## Ligador

### Compilando 

```sh
cd Ligador/
make 
```

### Executando
Para ligar um ou mais arquivos, deve-se fornecer apenas o seu nome, **sem a extensão**. Por exemplo, para montar os arquivos `mod_a.obj` e `mod_b.obj`, faça:

```sh
./ligador mod_a mod_b 
```
