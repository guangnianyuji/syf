#include<iostream>
#include<string>
#define SIZE 5
using namespace std;

template <typename T>
struct Stack {
	T elems[SIZE];
	int head = 0;
	void push(T elem) {
		elems[head] = elem;
		head++;
	}
	T pop() {
		head--;
		return elems[head];//返回删除的栈顶元素
	}
	T Stackhead() {//取栈顶元素的函数
		return elems[head - 1];
	}
	bool isEmpty() {
		return head == 0;
	}
	bool isFull() {
		return head == SIZE;
	}
	void print() {
		cout << "[";
		for (int i = 0; i < head; i++) {
			cout << elems[i] << ",";
		}
		cout << "]" << endl;
	}
};

template <typename T>
struct Queue {
	Stack<T> stackA;
	Stack<T> stackB;
	void inQueue(T elem) {
		stackA.push(elem);
	}
	T deQueue() {
		while (!stackA.isEmpty()) {//把stackA中元素倒放进stackB，即stackA中pop的元素push进stackB
			stackB.push(stackA.pop());
		}
		T temp = stackB.pop();//该函数将返回被删除元素
		while (!stackB.isEmpty()) {//把stackB中元素倒放进stackA，即stackB中pop的元素push进stackA
			stackA.push(stackB.pop());
		}
		return temp;
	}
	T Queuehead() {
		return stackA.Stackhead();
	}
	bool isEmpty() {
		return stackA.isEmpty();
	}
	bool isFull() {
		return stackA.isFull();
	}
	void print() {
		stackA.print();
	}
};

struct Point {
	friend istream& operator>>(istream& cin, Point& P);
	friend ostream& operator<<(ostream& cout,const Point& P);
private:
	int ix;
	int iy;
};

istream& operator>>(istream& cin, Point& P) {//重载流提取运算符
	cin >> P.ix;
	if (cin.fail()) {
		cerr << "wrong put!!" << endl;
		exit(-3);
	}
	char ch;
	cin.get(ch);//把逗号从缓冲区中读掉
	if (ch != ',') {
		cerr << "wrong put!!" << endl;
		exit(-3);
	}
	cin >> P.iy;
	if (cin.fail()) {
		cerr << "wrong put!!" << endl;
		exit(-3);
	}
	return cin;
}

ostream& operator<<(ostream& cout, const Point& P) {//重载流插入运算符
	cout << "(" << P.ix << "," << P.iy << ")";
	return cout;
}

istream& operator>>(istream& cin, string& str) {//重载了输入字符串的流提取运算符，因为cin>>会以空格为分隔符
	cin.get();//把指令与变量之间的空格读掉
	getline(cin, str);
	return cin;
}

template <typename T>
void fnFunction(Queue<T>& queue) {
	int iOrder;
	cout << "请输入指令与变量，1入栈，2出栈，0结束（点坐标之间请用英文逗号）" << endl;
	while (1) {
		cin >> iOrder;
		if (cin.fail()) {
			cerr << "wrong input!!" << endl;
			exit(-2);
		}
		if (iOrder == 0) {
			queue.print();
			break;
		}
		else if (iOrder == 1) {
			if (queue.isFull()) {
				cout << "Queue is full!" << endl;
				cin.ignore(1024, '\n');//清空输入缓冲区,确保下一次输入正常
			}
			else {
				T elem;
				cin >> elem;
				if (cin.fail()) {
					cerr << "wrong input!!" << endl;
					exit(-2);
				}
				queue.inQueue(elem);
			}
		}
		else if (iOrder == 2) {
			if (queue.isEmpty()) {
				cout << "Queue is empty!" << endl;
			}
			else {
				cout << queue.Queuehead() << " " << "is deQueued!" << endl;
				queue.deQueue();
			}
		}
		else {
			cout << "wrong input!!" << endl;
			exit(-3);
		}
	}
};

int main() {
	cout << "请输入0，1，2分别代表int,string,Point" << endl;
	int iType;
	cin >> iType;
	if (iType < 0 || iType>2 || cin.fail()) {
		cerr << "wrong input!!" << endl;
		exit(-1);
	}
	switch (iType) {
	case 0: {Queue<int> queue; fnFunction(queue); break; }
	case 1: {Queue<string>queue; fnFunction(queue); break; }
	case 2: {Queue<Point> queue; fnFunction(queue); break; }
	}
	return 0;
}