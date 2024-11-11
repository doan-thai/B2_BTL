#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct node{
	int data;
	node * left;
	node * right;
};

typedef struct node NODE;
typedef NODE * Tree;

class Cay{
	private:
		Tree t;
	public:
		Cay(){ t = NULL ; }
		Tree& getTree(){
			return t;
		}
		void insert(Tree &t,int x);
		void intangdan(Tree t);
		void ingiamdan(Tree t);
		void erase(Tree &t,int x);
		bool find(Tree t, int x);
		NODE* Nodemaxright(NODE * p);
};

void Cay::insert(Tree &t,int x){
	if(t == NULL){
		NODE * p = new NODE;
		p->data = x;
		p->left = NULL;
		p->right = NULL;
		t = p;
	}else{
		if(t->data > x){
			insert(t->left, x);
		}
		else if(t->data < x){
			insert(t->right, x);
		}
	}
}

void Cay::intangdan(Tree t){
	if(t != NULL){
		intangdan(t->left);
		cout << t->data << " ";
		intangdan(t->right);
	}
}

void Cay::ingiamdan(Tree t){
	if(t != NULL){
		ingiamdan(t->right);
		cout << t->data << " ";
		ingiamdan(t->left);
	}
}

NODE* Cay::Nodemaxright(NODE * p){
	if(p->right != NULL){
		return Nodemaxright(p->right);
	}	
	return p;
}

void Cay::erase(Tree &t,int x){
	if(t == NULL){
		return ;
	}else{
		if(x < t->data){
			erase(t->left , x);
		}else if(x > t->data){
			erase(t->right, x);
		}else{
			if(t->left == NULL && t->right == NULL){
				delete t;
				t = NULL;
			}else{
				if(t->left == NULL){
					NODE *p = t;
					t = t->right;
					delete p;
				}else if(t->right == NULL){
					NODE *p = t;
					t = t->left;
					delete p;
				}else{
					NODE *p = Nodemaxright(t->left);
					t->data = p->data;
					erase(t->left, p->data);
				}
			}
		}
	}
}

bool Cay::find(Tree t, int x){
	if(t == NULL){
		return false;
	}else{
		NODE * p = t;
		while(p != NULL){
			if(p->data == x){
				return true;
			}else if(p->data < x){
				p = p->right;
			}else if(p->data > x){
				p = p->left;
			}
		}
		return false;
	}
}

void docFile(string filename, vector<int> &v){
	ifstream doc(filename);
	if(!doc.is_open()){
		cout << "Khong mo duoc !" << endl;
		return;
	}else{
		int n;
		while(doc >> n){
			v.push_back(n);
		}
	}
	doc.close();
}

int main(){
	vector<int> A, B, C;
	Cay TR;

	docFile("A.txt", A);
	docFile("B.txt", B);
	docFile("C.txt", C);
	
	for(int i= 0 ; i < A.size() ; i++){
		TR.insert(TR.getTree(),A[i]);
	}
	for(int i = 0 ; i < B.size() ; i++){
		TR.insert(TR.getTree(),B[i]);
	}
	for(int i = 0 ; i < C.size() ; i++){
		TR.erase(TR.getTree(),C[i]);
	}
	TR.intangdan(TR.getTree());
	return 0;
}