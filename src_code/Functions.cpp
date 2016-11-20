#include "Functions.h"

void split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

expr mk_add(expr_vector args) {
    expr r = args[0];
    for (int i = 1; i < (int)args.size(); i++)
        r = to_expr(args.ctx(), r + args[i]);
    return r;
}

void modelo_VM(vector<Server> sortedServers, vector <VM> VMList, int reqServers,vector <vector <int> > listaTrues){

    int nServers=reqServers;
    int nVMs=VMList.size();

    vector <int> RAM_SERVER;
    vector <int> CPU_SERVER;

    for (int w=0; w<nServers; w++) {
        RAM_SERVER.push_back(sortedServers[sortedServers.size()-w-1]._RAM);
        CPU_SERVER.push_back(sortedServers[sortedServers.size()-w-1]._CPU);
    }

    context c;

    expr zero = c.int_val(0);

    // Create matrix of sv and vm variables
    vector <vector<expr> > column;
    vector <expr> row;

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

    vector <expr> vm_ram;
    vector <expr> vm_cpu;

    for (int i = 0; i < nVMs; i++) {

        vm_ram.push_back(c.int_val(VMList[i]._RAM));
        vm_cpu.push_back(c.int_val(VMList[i]._CPU));
    }

    solver s(c);

    for (int i = 0; i < (int)column.size(); i++) {
        expr_vector line1(c);

        for (int j = 0; j < (int)column[0].size(); j++) {
                line1.push_back(column[i][j]);
        }
        //Cada tarefas e respectiva Virtual Machine tem de estar num servidor
        s.add(mk_or(line1));
    }

    for (int i = 0; i < (int)column.size(); i++){
        for (int j = 0; j < (int)column[0].size(); j++) {
            for (int k = 0; k < (int)column[0].size(); k++) {
                if (k == j ) {
                    continue;
                } else {
                    //Cada tarefas e respectiva Virtual Machine tem de estar apenas num servidor
                    s.add(implies(column[i][j], !column[i][k]));
                }
            }
        }
    }

    for (int i = 0; i < (int)listaTrues.size(); i++) {
        for (int j = 0; j < nServers; j++) {
            // Todas as tarefas e respectivas Virtual Machines que não podem estar no mesmo servidor por collocation
            s.add(implies(column[listaTrues[i][0]][j], !column[listaTrues[i][1]][j]));
        }
    }

    for (int j = 0; j < (int)column[0].size(); j++) {
        expr_vector line2(c);
        expr_vector line3(c);

        for (int i = 0; i < (int)column.size(); i++) {
            line2.push_back(ite(column[i][j],vm_cpu[i],zero));
            line3.push_back(ite(column[i][j],vm_ram[i],zero));
        }

        // O somatorio das CPU das tarefas/VM tem de ser menores que a CPU do servidor
        s.add(mk_add(line2) <= CPU_SERVER[j] && mk_add(line3) <= RAM_SERVER[j]);
    }
    if (s.check() == sat) {
        model m = s.get_model();
        cout << "o " << nServers << endl;
        for (int i = 0; i < nVMs; i++) {
            for (int j = 0; j < nServers; j++) {
                if (eq(m.eval(column[i][j]),c.bool_val(true)))  {
                    cout << VMList[i]._jobid << " " << VMList[i]._VMindex << " -> " << sortedServers[sortedServers.size()-j-1]._id << endl;
                }
            }
        }
        //cout << "SMT Feito!\n";
    } else {
        modelo_VM(sortedServers, VMList,reqServers +1, listaTrues);
    }
}
