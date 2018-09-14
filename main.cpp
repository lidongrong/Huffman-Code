#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

struct element {//Ԫ���࣬�洢�ӽڵ㣬���ڵ㣬Ȩ�أ�pickable���ڱ���ڽ���������ѡ��Сֵ���ѱ�ѡ����Ԫ��
	int weight;
	int parent;
	int lchild;
	int rchild;
	bool pickable = true;
	element() {//���캯��
		weight = 0;
		parent = -1;
		lchild = -1;
		rchild = -1;
		pickable = true;
	}
};


void InitHuffmanTree(element * &ht, int n) {//����һ���յĻ�����������
	ht = new element[n];
}


/*
ѡ����������С������Ԫ�أ�����min1,min2�У����ʹ������
*/
void Select(element tree[], int n, int &min1, int &min2) {
	struct number {   //number�ṹ�����ڴ洢���ֺ�����Ӧ��λ��
		int num;
		int pos;
		number() { num = 0; pos = 0; }
	};
	number small;
	small.num = 10000000; small.pos = 0;  //��num����ɳ��󣬷�����ѡ��С�ģ���ʱ����Ȼ���С
	for (int i = 0; i < n; i++) {
		if (tree[i].weight <= small.num&&tree[i].weight != 0&&tree[i].pickable==1) {
			small.num = tree[i].weight;
			small.pos = i;
		}

	}
	min1 = small.pos;
	tree[small.pos].pickable = 0;//��СԪ��״̬������Ϊ�޷�����ѡ
	number small2;
	small2.num = 100000000; small2.pos = 0;
	for (int i = 0; i < n; i++) {
		if (tree[i].weight <= small2.num&&tree[i].weight != 0&&tree[i].pickable==1) {
			small2.num = tree[i].weight;
			small2.pos = i;
		}

	}
	min2 = small2.pos;
	tree[min2].pickable = 0;

}

void HuffmanTree(element * &HuffTree, int w[], int n) {//������������
	int min1=0;
	int min2=0;
	InitHuffmanTree(HuffTree, 2 * n - 1);
	int m = 2 * n - 1;
	for (int i = 0; i < n; i++) {
		HuffTree[i].weight = w[i];
	}
	
	for (int k = n; k < m; k++) {
		Select(HuffTree, m, min1, min2);
		//cout << min1 << " " << min2;
		//system("pause");
		HuffTree[min1].parent = k;
		HuffTree[min2].parent = k;
		HuffTree[k].lchild = min1;
		HuffTree[k].rchild = min2;
		HuffTree[k].weight = HuffTree[min1].weight + HuffTree[min2].weight;
		HuffTree[k].pickable = 1;
		HuffTree[min1].pickable = 0;
		HuffTree[min2].pickable = 0;
		/*for (int i = 0; i < m; i++) {
			cout << HuffTree[i].weight << " " << i << " " << HuffTree[i].parent <<
				" " << HuffTree[i].lchild << " " << HuffTree[i].rchild <<" "<<HuffTree[i].pickable<< endl;
		}
		system("pause");*/
		//���汻ע�͵Ĵ�������ڲ��ԣ�����ɾ��˵�����Ժ��õõ�����δ������������
		
	}
}


/*
����������ʹ�ýṹ��HuffmanCode�洢
ch���ڴ洢��ĸ
code�������ڴ洢���룬�Ƚ�ȫ��ֵĬ����Ϊ7�������Ϳ����������ʱ����7��Ϊ������������0��1�ĵ�Ԫ
*/
struct HuffmanCode {
	char ch;
	int code[12];
	HuffmanCode() {
		for (int i = 0; i < 12; i++) {
			code[i] = 7;
		}
	}
};

void CreateCode(element * HuffmanTree, HuffmanCode * &hf, int n, char c[]) {
	hf = new HuffmanCode[n];
	for (int i = 0; i < n; i++) {//�����ַ�
		hf[i].ch = c[i];
	}
	for (int i = 0; i < n; i++) {//�������������
		int start = 11;
		int k = i;
		int copy = i;
		element temp = HuffmanTree[i];
		while (temp.parent >= 0) {
			if (k == HuffmanTree[temp.parent].lchild) {
				hf[i].code[start] = 0;
			}
			if (k == HuffmanTree[temp.parent].rchild) {
				hf[i].code[start] = 1;
			}
			start--;
			k = temp.parent;
			temp = HuffmanTree[temp.parent];
			
		}
		i = copy;
	}
}



void PrintCode(HuffmanCode alpha) {//���ĳ���ַ���Ӧ�Ļ���������
	for (int i = 0; i < 12; i++) {
		if (alpha.code[i] != 7) {
			cout << alpha.code[i];
		}
	}
	cout << " ";
}

bool IsIn(char ch, char alphabet[],int n) {//�ж�һ��ֵ�Ƿ�����ĸ����
	for (int i = 0; i < n; i++) {
		if (ch == alphabet[i]) {
			return 1;
		}
	}
	return 0;
}

char alphabet[27] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
'p','q','r','s','t','u','v','w','x','y','z'};

int weight[26] = {8167,1492,2782,4253,12702,2228,2015,6094,6966,153,772,4025,2406,
6749,7507,1929,95,5987,6327,9056,2758,978,2360,150,1974,74};

char ALPHABET[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


int main() {
	while (1) {
		string text;
		cout << "this program transform a text into Huffman codes." << endl;
		cout << "Now please enter a text. End with '#'" << endl;
		cout << endl;
		getline(cin, text, '#');


		//�Ѵ�д��ĸת��ΪСд��ĸ
		for (int j = 0; j < text.size(); j++) {
			if (IsIn(text[j], ALPHABET, 26)) {
				text[j] = char(text[j] + 32);
			}

		}


		element * Tree;
		HuffmanCode * Codes;


		HuffmanTree(Tree, weight, 26);
		CreateCode(Tree, Codes, 26, alphabet);


		cout << endl;
		cout << "the Huffman code of this text is: " << endl;
		cout << endl;
		for (int i = 0; i < text.size(); i++) {
			if (IsIn(text[i], alphabet, 26)) {
				for (int j = 0; j < 26; j++) {
					if (text[i] == Codes[j].ch) {
						PrintCode(Codes[j]);
					}
				}
			}
			else {
				cout << text[i];
			}
		}
		delete [] Tree;
		delete [] Codes;
		cout << endl;
		system("pause");
	}
}


