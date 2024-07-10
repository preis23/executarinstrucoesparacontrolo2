Tendo por base o código desenvolvido no trabalho prático 1, pretende-se com o presente trabalho prático efetuar a restruturação do que já foi desenvolvido em três vertentes, a saber:
• Considerar os requisitos funcionais que não foram totalmente satisfeitos no trabalho prático 1 e implementá-los convenientemente;
• Considerar a adaptação de alguns dos requisitos funcionais do trabalho prático 1, bem como os novos requisitos funcionais, com base no presente enunciado;
• Considerar a implementação com recurso a funções da linguagem de programação em C, bem como outros tópicos do programa da unidade curricular entretanto abordados nas aulas.
As instruções podem agora ter parâmetros opcionais, que aparecem sempre depois dos parâmetros obrigatórios. Por exemplo se a instrução ligar tiver um máximo de cinco parâmetros, dois dos quais opcionais, então serão válidos os seguintes comandos: ligar Ana 10 20 (comando ligar sem parâmetros opcionais)
ligar Ana 10 20 Carlos 50.2 (comando ligar com dois parâmetros opcionais) e serão inválidos os seguintes comandos:
ligar Ana 10 (comando ligar sem os parâmetros obrigatórios) ligar Ana 10 20 Carlos 50.2 Teste (comando ligar com parâmetros em excesso) Os parâmetros também passam a ter tipo, podendo ser um dos três tipos seguintes:
• String: para sequências de carateres alfanuméricos;
• Inteiro: para números inteiros (int);
• Real: para números reais (float).
Por exemplo, o comando ligar com dois parâmetros, o primeiro do tipo String e o segundo do tipo Real pode ter a seguinte invocação válida:
ligar Ana 10.5 (comando ligar com ordem dos tipos de parâmetros correta)
e as seguintes invocações inválidas:
ligar 10.5 Ana ligar Ana Carlos
(comando ligar com ordem dos tipos de parâmetros errada) (comando ligar com tipo do segundo parâmetro errado)

Sempre que um comando é executado, deverá ser registada uma nova linha num ficheiro de texto com os dados dessa tentativa de execução, nomeadamente a data/hora em que ocorreu; o comando e respetivos parâmetros; e o resultado da sua execução.
A aplicação deverá ainda considerar a possibilidade de guardar em ficheiro o estado da aplicação (todos os dados considerados relevantes) de forma a poder recuperá-lo numa nova execução.
Relativamente ao resultado das execuções, o programa deverá possibilitar ver os seguintes dados:
• O número de instruções executadas sem erro;
• O número de instruções executadas com erro total; com erro por número
incorreto de parâmetros; com erro por tipo de parâmetros errado;
• O número de vezes que um comando é executado corretamente com recurso a
parâmetros opcionais;
• A instrução ou instruções mais utilizada;
• As instruções que nunca foram utilizadas;
O resultado das estatísticas pode ser exportado para ficheiro tipo CSV de forma a poder ser aberto noutras aplicações, como por exemplo o MS Excel.
