# TP1

Autores: Paulo Vitor Callegari Dalvi e Ryan Lima Peçanha.

Construído em: C.

Executando o programa:

1. Abra o programa "Main.exe".

2. O programa quando iniciar irá dar 3 opções para manusear uma imagem ppm (OBS: Caso não tiver uma imagem ppm p2 ou p3, disponibilizamos uma denominada "sample.ppm" no repositório ).

Carregando imagem:

1. Execute a opção número 1 ( um ) para você carregar uma imagem.

2 Agora, o programa irá te pedir para inserir o caminho de uma imagem ppm p2 ou p3 de sua preferência ou executar a padrão ( basta apertar enter para a opção padrão ).

3 Executando a imagem padrão ou a que você especificar o caminho, o programa irá retornar ao menu principal te oferecendo novamente 3 opções e uma mensagem indicando que ocorreu tudo certo.

Convertendo imagem para tons de cinza:

1. Ao digitar como opção o número 2 ( dois ), a imagem que você carregou préviamente terá as cores convertidas para tons de cinza e também irá aparecer uma mensagem indicando que ocorreu tudo certo. 

Gravando imagem:

1. Ao digitar como opção o número 3 ( três ) o programa irá te pedir um caminho e também um nome para um novo arquivo que será gerado. O arquivo gerado será a sua imagem carregada porém em tons de cinza e também irá retornar ao menu principal. ( OBS: Também há a opção do caminho e nome padrão, ao selecionar essa opção, apenas apertando enter quando for pedido, o programa irá gerar dentro da pasta do projeto um arquivo denominado "output.ppm", que será sua imagem convertida. )

Sair:

1. Digitando 4 ( quatro ) como opção, o programa irá fechar.

Exemplos:

Exemplos de input para carregar imagem específica: C:\Users\ryan\Desktop\sua_imagem.ppm

Exemplo de input para gravar a imagem de maneira específica: C:\Users\ryan\Desktop\sua_imagem_em_tons_de_cinza.ppm

Principais decisões de implementação:

Estrutura do Programa:

O programa principal opera em um loop infinito (while(1)) que exibe um menu para o usuário e aguarda a entrada da escolha do usuário. O loop permite que o usuário realize múltiplas operações sem sair do programa.

Alocação e Liberação de Memória:

Antes de carregar uma nova imagem, o programa verifica se uma imagem anterior foi carregada e libera a memória associada a ela, evitando vazamentos de memória.

Comentários:

O código contém comentários que explicam as seções importantes do código, o que torna mais fácil entender o que cada parte do programa está fazendo.

Loop Infinito e Encerramento:

O programa continua a operar em um loop infinito até que o usuário escolha a opção "Sair". Quando o usuário escolhe sair, o programa libera a memória alocada e encerra.
