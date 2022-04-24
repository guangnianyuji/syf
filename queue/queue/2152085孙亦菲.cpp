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
		return elems[head];//����ɾ����ջ��Ԫ��
	}
	T Stackhead() {//ȡջ��Ԫ�صĺ���
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
		while (!stackA.isEmpty()) {//��stackA��Ԫ�ص��Ž�stackB����stackA��pop��Ԫ��push��stackB
			stackB.push(stackA.pop());
		}
		T temp = stackB.pop();//�ú��������ر�ɾ��Ԫ��
		while (!stackB.isEmpty()) {//��stackB��Ԫ�ص��Ž�stackA����stackB��pop��Ԫ��push��stackA
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

istream& operator>>(istream& cin, Point& P) {//��������ȡ�����
	cin >> P.ix;
	if (cin.fail()) {
		cerr << "wrong put!!" << endl;
		exit(-3);
	}
	char ch;
	cin.get(ch);//�Ѷ��Ŵӻ������ж���
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

ostream& operator<<(ostream& cout, const Point& P) {//���������������
	cout << "(" << P.ix << "," << P.iy << ")";
	return cout;
}

istream& operator>>(istream& cin, string& str) {//�����������ַ���������ȡ���������Ϊcin>>���Կո�Ϊ�ָ���
	cin.get();//��ָ�������֮��Ŀո����
	getline(cin, str);
	return cin;
}

template <typename T>
void fnFunction(Queue<T>& queue) {
	int iOrder;
	cout << "������ָ���������1��ջ��2��ջ��0������������֮������Ӣ�Ķ��ţ�" << endl;
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
				cin.ignore(1024, '\n');//������뻺����,ȷ����һ����������
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
	cout << "������0��1��2�ֱ����int,string,Point" << endl;
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