#include <algorithm>
#include <ctime>

#include "Functions.h"
#include "importTXT.h"
#include "List.h"


int main(int argc, char** argv) {

	string path;

	if (argc<2){
        cout<<"Please insert filepath:\n";
        cin>>path;
	}else{
        path=argv[1];
    }

	//Auxiliares...
	importTXT txtFile(path);
	ifstream filetoread;
	//cout << path << endl;

	List ipList;

	txtFile.readFile();

	ipList = List(txtFile._VMList, txtFile._serverList);

	ipList._reqServers=ipList.calc_maxVMIndex();

	vector <vector <int> > listaTrues;

    vector <int> aux;

    //Criar lista de Trues
    for (int w1 = 0; w1 < ipList._nVM; w1++) {
        for (int w2 = 0; w2 < ipList._nVM; w2++) {
        if ((ipList._VMList[w1]._jobid == ipList._VMList[w2]._jobid) && ipList._VMList[w1]._Collo == true && ipList._VMList[w2]._Collo == true && w1!=w2)
            {
            aux.push_back(w1);
            aux.push_back(w2);
            listaTrues.push_back(aux);
            aux.clear();
            }
        }
    }

    modelo_VM(ipList._sortedServerList, ipList._VMList,ipList._reqServers, listaTrues);

	return 0;
}


