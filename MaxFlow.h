/* Bellicano Fabrizio
 * 3257630
 * Classe per il calcolo del maxflow. 
 * Non è una classe "general purpose" che userei in un programma completo, 
 * ma è una classe specificamente designata per l'applicazione nel contesto "progettino PAA"
 */

//#include<iostream> //(già incluso nel main)
#include<cstring> // stringhe
#include<sstream> // stringstream per prendere i token nelle stringhe
#include<fstream> // lettura del file
#include<vector> // matrice dei flussi
#include<queue> // per la BFS

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

using namespace std;


class MaxFlow{

private:  

vector < vector < int > > graph;
vector < int > parent;

int V, E;
int s, t;
int totalFl;


public:
    
  MaxFlow(){  
    totalFl=0;
  }
  
  ~MaxFlow(){}


int getflow(){return totalFl;}
//solo per completezza; in realtà mi serve solo MaxFlow::getflow()
void sets(int num){s=num;}
void sett(int num){t=num;}
void setE(int num){E=num;}
void setV(int num){V=num;}
int gets(){return s;}
int gett(){return t;}
int getE(){return E;}
int getV(){return V;}


//visita BFS che mi da anche il flusso
int reachable() {

   int forward,current;
   
   queue<int> q;

   for(int i=0;i<V;i++) parent[i]=-1; // tutti non sono stati visitati

   q.push(s);
   parent[s] = s; //modo in cui segnalerò, quando percorrerò all'indietro il cammino, che sono tornato alla sorgente
   int min;
   
   while(!q.empty()){
      forward=q.front();
      q.pop();
      for(int i=0; i<V; i++) { 
	  //parent indica il predecessore; se non sono stato visitato non ho predecessori e il mio genitore è -1
         if(graph[forward][i] && parent[i] == -1) {//-1 significa non visitato
	   q.push(i);
            parent[i] = forward;
            
            if(i == t) {
		min = graph[parent[t]][t];
		current = t;
		while(parent[current] != current) {//dopo che tutti sono stati visitati, per riconoscere la sorgente devo cercare l'antenato di se stesso
		    if(graph[parent[current]][current] < min)
			min = graph[parent[current]][current];
		    current = parent[current];
		}
			return min;
            }
         }
      }
   }
   return 0;
}

void calculatemaxflow() {
   int vertex, flow;
   while((flow=reachable())) {
       // Aggiorno i flussi per poi ripartire con reachable
       vertex = t;
       while(parent[vertex] != vertex) {
          graph[parent[vertex]][vertex] -= flow;
          graph[vertex][parent[vertex]] += flow;
          vertex = parent[vertex];
       }
       totalFl += flow;
   }
  // return totalFl; //più corretto usare (dall'esterno) il MaxFlow::getflow() quindi commento
}


int Parser (char* filename){
    
		ifstream file;
		file.open(filename);
		if (!file) {
		    cout << "Impossibile aprire il file. ";
		    cout << "Abbiamo gia mandato una squadra di scimmie ";
		    cout << "altamente addestrata per risolvere il problema" << endl;
		    return EXIT_FAILURE;
		}
		//cout<<"ok file aperto: "<<filename<<endl;
		string input;   // Linea per linea del file
		stringstream buffer; // Per il tokenizer della stringa qui sopra dichiarata
		char type;           // Viene usato per "bruciare" l'etichetta della linea (tranne in case 'n' in cui conterrà l'etichetta s o t per il pozzo o la sorgente)
		while (file.good()){  // Finchè non ho EOF..
		    getline(file,input);  // ..effettuo parsing linea per linea, e separerò volta per volta i token
		    if (!input.empty()){  // Salto eventuali linee vuote
			switch (input[0]) {  // Vedo l'etichetta della linea per effettuare le varie operazioni
				
				case 'p': // Definizione di V ed E
					buffer<<input;  // inserisco la stringa nello stringstream..
					buffer>>type>>input>>V>>E;  // ..per poi inserire i token nelle variabili
					// N.B il dato sugli archi è utile solo per il controllo di correttezza (E>V)
					// dal momento che assumiamo la correttezza del grafo esso è omesso
					input.clear();
					buffer.clear();
					//cout<<"ok V e E: " <<V<<" "<<E<<endl;
					parent.resize(V,-1);  //resize della matrice dei predecessori
					graph.resize(V);   // resize delle righe della matrice
					for (int i=0; i<V; i++)  graph[i].resize(V,0);  // resize delle colonne
					break;

				case 'n':    //  Definizione source o sink
					int value;
					buffer<<input;  // come sopra, inserisco la stringa nello stringstream per parsare i token
					buffer>>type>>value>>type; //l'ultimo type è quello significativo, il primo contiene solo la lettera n
					input.clear();
					buffer.clear();
					if (type=='s') s=--value;//cambio gli indici per le matrici
					else t=--value;         //cambio gli indici per le matrici
					//cout<<"ok s o t:"<<value<<endl;
					break;

				case 'a':   // Definizione arco
					int v1, v2, val;                                         
					buffer<<input;   // come sopra
					buffer>>type>>v1>>v2>>val;
					graph[--v1][--v2]=val; //cambio gli indici per le matrici
					input.clear();
					buffer.clear();
					//cout<<"v1: "<<v1<<" v2: "<<v2<<" val: "<<val<<endl;
					break;

			}
		    }
		}
file.close();
return EXIT_SUCCESS;
}


//per il debug dei primi grafi piccoli.. stampavo la matrice delle adiacenze
/*
void debugger(){
  for(int i=0;i<V;i++){
      for(int k=0;k<V;k++)
      cout<<graph[i][k]<<" ";
      cout<<endl;
    }
}
*/

};