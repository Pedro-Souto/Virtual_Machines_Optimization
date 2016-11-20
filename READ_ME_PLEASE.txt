/* @IST MEIC 2016/2017

		Algoritmos para Lógica Computacional - Projecto 2
====================================================================
Grupo:

- Pedro Souto - 	IST186332
- Tomás Carvalho -  IST186264

====================================================================
Especificações:

1 - Liguagem usada - c++
2 - API usado - Z3
3 - Versão do Software - z3 4.5.0
4 - Ambiente de Desenvolvimento - Unix (Linux)

====================================================================
Como Correr o Programa:

1 - cd $(shell pwd)/2nd_Project_ALC
2 - make
3 - make run

NOTA: Ao fazer make run o programa vai correr todas as instâncias
disponibilizadas na página da cadeira de forma gradativa, isto é,
grau fácil, médio e avançado.

NOTA_2: EM termos de tempo de espera, é expectável que as primeiras 10
instâncias não demorem mais que 1/3 segundos. A partir da 10ª o tempo
de espera pode ser bastante elevado.

====================================================================
Métodos usado:

1 - leitura do ficheiro de input;

2 - Calculo do número mínimo de Servidores;

3 - Ordenação dos servidores por rank de MaxMin:
	
	Rank = Max(Min(CPU,RAM));

4 - Criação das variáveis:

    for (int i = 0; i < nVMs; i++) {

        for (int j = 0; j < nServers; j++) {
            std::stringstream name;
            name << "vm_" << i << "_sv_" << j;
            row.push_back(c.bool_const(name.str().c_str()));
        }
        //expr result=y;
        column.push_back(row);
        row.clear();
    }

Em que VM_i_SV_j diz-nos que a VM i está no servidor j;

5 - Cada tarefas e respectiva Virtual Machine tem de estar num servidor:

    s.add(mk_or(line1));

6 - Cada tarefas e respectiva Virtual Machine tem de estar apenas num servidor:
    
    s.add(implies(column[i][j], !column[i][k]));

7 - Todas as tarefas e respectivas Virtual Machines que não podem estar no
	mesmo servidor por collocation:

    s.add(implies(column[listaTrues[i][0]][j], !column[listaTrues[i][1]][j]));

8 - O somatorio das CPU das tarefas/VM tem de ser menores que a CPU do servidor:
    
    s.add(mk_add(line2) <= CPU_SERVER[j] && mk_add(line3) <= RAM_SERVER[j]);

9 - Se for SAT, gerar report (Exemplo):

	o 2
	0 0 -> 3
	0 1 -> 1
	1 0 -> 1
	2 0 -> 1
	2 1 -> 3
	2 2 -> 3
	3 0 -> 3
	3 1 -> 1

10 - Se For Unsat, volta ao ponto 4 com mais 1 Servidor:

	modelo_VM(sortedServers, VMList,reqServers +1, listaTrues);

============================FIM=====================================