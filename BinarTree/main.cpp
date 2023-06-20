#include <iostream>
using namespace std;

class node {
public:
    int data;
    string letters;
    node* LeftBranch;
    node* RightBranch;

    //указываем значения узла (конструктор узла)
    node(string letters = "", int data = 0, node* LeftBranch = nullptr, node* RightBranch = nullptr) {//nullptr - нулевой указатель
        this->letters = letters;//присваиваем текущему узлу значения, описанные выше (в конструкторе)
        this->data = data;//присваиваем текущему узлу значения, описанные выше
        this->LeftBranch = LeftBranch;//присваиваем текущему узлу значения, описанные выше
        this->RightBranch = RightBranch;//присваиваем текущему узлу значения, описанные выше
    }
};

class Tree {
public:

    int cmpare(node* A1, node* A2) {//для сравнения элементов
        if (A1->letters < A2->letters) return 1;//выводим 1, когда элемент А1 меньше А2
        else if ((A1->letters == A2->letters) && (A1->data < A2->data)) return 1;
        if (A1->letters > A2->letters) return 2;//выводим 2, когда элемент А1 больше А2
        else if ((A1->letters == A2->letters) && (A1->data > A2->data)) return 2;
        else return 0;//выводим 0, когда элементы А1 и А2 равны
    }

    node* head; //объявляем голову дерева
    Tree() {
        head = nullptr;//задали значение при помощи конструктора
    }
    void Add(string letters, int data) {
        if ((data >= 1000) && (data <= 9999)) {
            node *currentParent = head;
            node *tmp = new node(letters, data);
            if (head == nullptr) {//если голова пустая, то создаем новый ПЕРВЫЙ узел = head (корень дерева)
                head = new node(letters, data);
            } else {//если голова НЕ пустая, то добавляем узлы
                node *current = head; //присваиваем текущий элемент голове
                bool ElAdded = false; //объявляем логическую переменную для проверки на добавление этого элемента

                while (ElAdded == false) {//до тех пор, пока элемент не добавлен
                    if (cmpare(tmp, current) == 2) {//если новый элемент больше текущего значения, то
                        //cout << (tmp->letters > current->letters);
                        //cout << (tmp->letters == current->letters) && (tmp->data > current->data);
                        currentParent = current;
                        current = current->RightBranch;//переходим к правому элементу
                    } else if (cmpare(tmp, current) == 1) {//если новый элемент меньше текущего значения, то
                        currentParent = current;
                        current = current->LeftBranch;//переходим к левому элементу
                    } else {//если новый элемент равен текущему, то выводим следующее сообщение
                        cout << "Элемент " << letters << data << " уже был добавлен\n";
                        ElAdded = true;
                    }

                    if (current == nullptr) { //если узел пустой, то добавляем на его место новый элемент
                        current = tmp;
                        if (cmpare(tmp, currentParent) == 2) {//сравиванем элементы для уточнения
                            currentParent->RightBranch = current;//каким потомком элемент должен быть (правым или левым)
                        } else if (cmpare(tmp, currentParent) == 1) {//сравиванем элементы для уточнения
                            currentParent->LeftBranch = current;//каким потомком элемент должен быть (правым или левым)
                        }
                        ElAdded = true; //узел добавлен
                    }
                }
            }
       }
       else cout << "Введены неверные данные";
    }

    void Delete(string letters, int data) {
        if (head == nullptr) {//если голова пустая
            cout << "Дерево пустое\n";
        }
        else {
            node* temporary = new node(letters, data);//переменная для сравнения
            node* current = head;
            node* tmp = nullptr; //переменная для хранения текущего элемента
            node* tmpParent = nullptr;//переменная для хранения родителя элемента
            node* rmbrLeftBranch = head->LeftBranch; //remember LeftBranch
            bool ElFinded = false;//логическая переменная для нахождения элемента

            if ((head->LeftBranch == nullptr) && (head->RightBranch == nullptr)) {
                head = nullptr;
                cout <<  "Дерево пустое\n";
            }
            else {
                while (ElFinded == false) {

                    if (current == nullptr) { //если узел пуст
                        cout << "Элемент " << letters << data << " не был найден\n";
                        ElFinded = true;
                    }
                    else {
                        if (cmpare(current, temporary) == 0) {//если текущий элемент равен тому элементу, к-ый мы ищем
                            tmp = current;
                            ElFinded = true;
                        }
                        if (cmpare(temporary, current) == 2) {//если новый элемент больше текущего значения, то (см. на строку 61)
                            tmpParent = current; //запоминаем родителя
                            current = current->RightBranch;//переходим к правому элементу
                        }
                        else if (cmpare(temporary, current) == 1) {//если новый элемент меньше текущего значения, то (см. на строку 65)
                            tmpParent = current; //запоминаем родителя
                            current = current->LeftBranch;//переходим к левому элементу
                        }//благодаря данным действия мы находим нужный нам элемент
                    }
                }
                if (tmp != nullptr) {//если текущий элемент не пустой
                    current = tmp->RightBranch; //current присваиваем элементу, наход-ся справа от tmp
                    if (current == nullptr) {
                        if (tmp->LeftBranch == nullptr) {//если левый эл-т от tmp пустой
                            delete (tmp);//удаляем число (узел)
                            //tmpParent->LeftBranch = nullptr;//убираем мусор после удаления
                            tmpParent->RightBranch = nullptr;//убираем мусор после удаления
                        }
                        else {
                            if (tmpParent == nullptr) {//если родителей нет, те tmp - корень дерева
                                head = tmp->LeftBranch;//корнем (головой) становится левый потомок tmp
                                delete (tmp);//удаляем число (узел)
                            }
                            else {
                                if (cmpare(tmpParent->LeftBranch, tmp) == 0) { //если tmp явл-ся левым потомком родителя
                                    tmpParent->LeftBranch = tmp->LeftBranch;//переприсваиваем потомки tmp к родителю tmp (левые)
                                }
                                else {//если tmp явл-ся правым потомком родителя
                                    tmpParent->RightBranch = tmp->LeftBranch;//переприсваиваем потомки tmp к родителю tmp (правые)
                                }
                                delete (tmp);//удаляем число (узел)
                            }
                        }
                    }
                    else {
                        current = tmp;
                        if (current->LeftBranch == nullptr) {//если левых потомков нет
                            if (tmpParent == nullptr) {//если родителей нет, те tmp - корень дерева
                                head = tmp->RightBranch;//корнем (головой) становится левый потомок tmp
                                delete (tmp);//удаляем число (узел)
                            }
                            else {
                                tmpParent = current;
                                current = current->RightBranch;
                                while (current->LeftBranch != nullptr) {//ищем минимальный левый элемент от правого потомка (tmp)
                                    tmpParent = current;
                                    current = current->LeftBranch;
                                }
                                node* test; //переменная для переприсвоения данных
                                test = current->RightBranch;
                                int change = current->data;//меняем местами current и tmp
                                current->data = tmp->data;
                                tmp->data = change;
                                string change2 = current->letters;//меняем местами current и tmp
                                current->letters = tmp->letters;
                                tmp->letters = change2;
                                tmpParent->RightBranch = nullptr;
                                delete (current);//удаляем число (узел)
                                tmpParent->RightBranch = test;
                            }
                            //tmpParent->RightBranch = tmp->RightBranch;//переприсваиваем родителю tmp правые потомки tmp
                            //delete (tmp);//удаляем число (узел)
                        }
                        else {
                            tmpParent = current;
                            current = current->RightBranch;
                            while (current->LeftBranch != nullptr) {//ищем минимальный левый элемент от правого потомка (tmp)
                                tmpParent = current;
                                current = current->LeftBranch;
                            }
                            node* test;//переменная для переприсвоения данных
                            test = current->RightBranch;//запоминем потомка, с к-ым будем менять
                            int change = current->data;//меняем местами current и tmp
                            current->data = tmp->data;
                            tmp->data = change;
                            string change2 = current->letters;//меняем местами current и tmp
                            current->letters = tmp->letters;
                            tmp->letters = change2;
                            tmpParent->RightBranch = nullptr;
                            //tmpParent->LeftBranch = nullptr;
                            delete (current);//удаляем число (узел)
                            tmpParent->RightBranch = test;
                        }
                    }
                }
            }
        }
    }

    void DeleteAllTree(node* root) {//удаление всего дерева через рекурсию
        if (head != nullptr) {
            if (root->RightBranch)  DeleteAllTree(root->RightBranch);//идя пошагово по веткам спускаемся до
            if (root->LeftBranch)  DeleteAllTree(root->LeftBranch);//листьев дерева
            Delete(root->letters, root->data);//удаляем дерево снизу вверх
            //head = nullptr;
        }
    }
};

//функция вывода дерева
void showLine(char* c, int p, int s) {
    int t=s; for(int i=0; i<p; i++)
    {
        printf(t&1 ? "|  " : "   ");
        t/=2;
    }
    printf(c);
}

void showTree(node* wood, int p, int s) {
    if (wood == nullptr) return;
    cout<< wood->letters <<wood->data<<endl;

    if (wood->LeftBranch!= nullptr) {
        showLine("|\n", p, s);
        showLine("L: ", p, s);
        showTree(wood->LeftBranch, p+1, s + ((wood->RightBranch== nullptr? 0 : 1)<<p));
    }
    if (wood->RightBranch!= nullptr) {
        showLine("|\n", p, s); showLine("R: ", p, s);
        showTree(wood->RightBranch, p+1, s);
    }
}

void PreOrderTravers(node* root) {//прямой обход (КЛП)
    if (root == nullptr) return;
    cout << root->letters << root->data << " ";
    PreOrderTravers(root->LeftBranch);
    PreOrderTravers(root->RightBranch);
}

void InOrderTraversLR(node* root) {//симметричный обход (ЛКП)
    if (root == nullptr) return;
    InOrderTraversLR(root->LeftBranch);
    cout << root->letters << root->data << " ";
    InOrderTraversLR(root->RightBranch);
}

void InOrderTraversRL(node* root) {//симметричный обход (ПКЛ)
    if (root == nullptr) return;
    InOrderTraversRL(root->RightBranch);
    cout << root->letters << root->data << " ";
    InOrderTraversRL(root->LeftBranch);
}

void PostOrderTravers(node* root) {//обратный обход (ЛПК)
    if (root == nullptr) return;
    PostOrderTravers(root->LeftBranch);
    PostOrderTravers(root->RightBranch);
    cout << root->letters << root->data << " ";
}

int main() {
    /*
     Основные функции:
     number->Add("oi", 6964); - добавление элемента
     number->Delete("oi", 6964); - удаление элемента
     number->DeleteAllTree(number->head); - очистка всего дерева
     showTree(number->head,0,0); - вывод дерева
     PreOrderTravers(number->head); - прямой обход (КЛП)
     InOrderTraversLR(number->head); - //симметричный обход (ЛКП)
     InOrderTraversRL(number->head); - симметричный обход (ПКЛ)
     PostOrderTravers(number->head); - обратный обход (ЛПК)
     */
    setlocale(LC_ALL, "ru");
    Tree* number = new Tree();
    //cout << endl;
    for (int data = 1000; data < 1010; data += 2) {
    number->Add("df", data);
    };
    number->Add("df", 1001);
    showTree(number->head,0,0);
    /*for (int data = 1000; data < 1020; data++) {
        number->Delete("df", data);
    }*/
    number->Delete("df", 1000);
    //number->DeleteAllTree(number->head);
    showTree(number->head,0,0);

    /*for (int data = 1015; data > 1001; data--) {
        number->Add("df", data);
    };*/
    //showTree(number->head,0,0);
    cout << endl;
    //number->Delete("oi", 6964);
    //number->DeleteAllTree(number->head);
    //showTree(number->head,0,0);
    cout << endl;
    PreOrderTravers(number->head);
    cout << endl;
    InOrderTraversLR(number->head);
    cout << endl;
    InOrderTraversRL(number->head);
    cout << endl;
    PostOrderTravers(number->head);
    return 0;
}