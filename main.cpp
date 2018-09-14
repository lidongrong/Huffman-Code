#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

struct element {//元素类，存储子节点，父节点，权重，pickable用于标记在建立树，挑选最小值中已被选过的元素
	int weight;
	int parent;
	int lchild;
	int rchild;
	bool pickable = true;
	element() {//构造函数
		weight = 0;
		parent = -1;
		lchild = -1;
		rchild = -1;
		pickable = true;
	}
};


void InitHuffmanTree(element * &ht, int n) {//建立一个空的霍夫曼树数组
	ht = new element[n];
}


/*
选出数组中最小的两个元素，放在min1,min2中，因此使用引用
*/
void Select(element tree[], int n, int &min1, int &min2) {
	struct number {   //number结构体用于存储数字和它相应的位置
		int num;
		int pos;
		number() { num = 0; pos = 0; }
	};
	number small;
	small.num = 10000000; small.pos = 0;  //把num先设成超大，反正是选最小的，到时候自然会变小
	for (int i = 0; i < n; i++) {
		if (tree[i].weight <= small.num&&tree[i].weight != 0&&tree[i].pickable==1) {
			small.num = tree[i].weight;
			small.pos = i;
		}

	}
	min1 = small.pos;
	tree[small.pos].pickable = 0;//最小元素状态被设置为无法被挑选
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

void HuffmanTree(element * &HuffTree, int w[], int n) {//建立霍夫曼树
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
		//上面被注释的代码仅用于测试，懒得删了说不定以后用得到。这段代码输出整棵树
		
	}
}


/*
霍夫曼编码使用结构体HuffmanCode存储
ch用于存储字母
code数组用于存储编码，先将全部值默认设为7，这样就可以在输出的时候以7作为条件跳过不是0，1的单元
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
	for (int i = 0; i < n; i++) {//分配字符
		hf[i].ch = c[i];
	}
	for (int i = 0; i < n; i++) {//分配霍夫曼编码
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



void PrintCode(HuffmanCode alpha) {//输出某个字符对应的霍夫曼编码
	for (int i = 0; i < 12; i++) {
		if (alpha.code[i] != 7) {
			cout << alpha.code[i];
		}
	}
	cout << " ";
}

bool IsIn(char ch, char alphabet[],int n) {//判断一个值是否在字母表中
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


		//把大写字母转换为小写字母
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


