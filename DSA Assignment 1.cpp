#include <bits/stdc++.h>
using namespace std;
struct poly
{
    int coeff;
    int exp;
    struct poly *next;
} *head1 = NULL, *head2 = NULL, *head3 = NULL;
struct poly *insert(struct poly *head, float coeff, int exp)
{
    struct poly *temp;
    struct poly *newP = new poly;
    newP->coeff = coeff;
    newP->exp = exp;
    newP->next = NULL;

    if (head == NULL || exp > head->exp)
    {
        newP->next = head;
        head = newP;
    }
    else
    {
        temp = head;
        while (temp->next != NULL && temp->next->exp >= exp)
            temp = temp->next;
        newP->next = temp->next;
        temp->next = newP;
    }
    return head;
}
struct poly *create(struct poly *head)
{
    int n, i;
    float coeff;
    int exp;
    cout << "Enter the number of terms: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the coefficient for term " << i + 1 << ": ";
        cin >> coeff;
        cout << "Enter the exponent for term " << i + 1 << ": ";
        cin >> exp;

        head = insert(head, coeff, exp);
    }
    return head;
}

void print(struct poly *head)
{
    if (head == NULL)
        cout << "No polynomial.";
    else
    {
        struct poly *temp = head;
        while (temp != NULL)
        {
            cout << temp->coeff << "x^" << temp->exp;
            temp = temp->next;
            if (temp != NULL)
                cout << " + ";
            else
                cout << endl;
        }
    }
}
void polyAdd(struct poly *head1, struct poly *head2)
{
    struct poly *ptr1 = head1;
    struct poly *ptr2 = head2;
    struct poly *head3 = NULL;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->exp == ptr2->exp)
        {
            head3 = insert(head3, ptr1->coeff + ptr2->coeff, ptr1->exp);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if (ptr1->exp > ptr2->exp)
        {
            head3 = insert(head3, ptr1->coeff, ptr1->exp);
            ptr1 = ptr1->next;
        }
        else if (ptr1->exp < ptr2->exp)
        {
            head3 = insert(head3, ptr2->coeff, ptr2->exp);
            ptr2 = ptr2->next;
        }
    }
    while (ptr1 != NULL)
    {
        head3 = insert(head3, ptr1->coeff, ptr1->exp);
        ptr1 = ptr1->next;
    }
    while (ptr2 != NULL)
    {
        head3 = insert(head3, ptr2->coeff, ptr2->exp);
        ptr2 = ptr2->next;
    }
    cout << "Added polynomial is: ";
    print(head3);
}
void polySub(struct poly *head1, struct poly *head2)
{
    struct poly *ptr1 = head1;
    struct poly *ptr2 = head2;
    struct poly *head3 = NULL;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->exp == ptr2->exp)
        {
            head3 = insert(head3, ptr1->coeff - ptr2->coeff, ptr1->exp);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if (ptr1->exp > ptr2->exp)
        {
            head3 = insert(head3, ptr1->coeff, ptr1->exp);
            ptr1 = ptr1->next;
        }
        else if (ptr1->exp < ptr2->exp)
        {
            head3 = insert(head3, ptr2->coeff, ptr2->exp);
            ptr2 = ptr2->next;
        }
    }
    while (ptr1 != NULL)
    {
        head3 = insert(head3, ptr1->coeff, ptr1->exp);
        ptr1 = ptr1->next;
    }
    while (ptr2 != NULL)
    {
        head3 = insert(head3, ptr2->coeff, ptr2->exp);
        ptr2 = ptr2->next;
    }
    cout << "Subtracted polynomial is: ";
    print(head3);
}
void polyMult(struct poly *head1, struct poly *head2)
{
    struct poly *ptr1 = head1;
    struct poly *ptr2 = head2;
    struct poly *head3 = NULL;
    if (head1 == NULL || head2 == NULL)
    {
        cout << "Zero polynomial";
        return;
    }
    while (ptr1 != NULL)
    {
        while (ptr2 != NULL)
        {
            head3 = insert(head3, ptr1->coeff * ptr2->coeff, ptr1->exp + ptr2->exp);
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
        ptr2 = head2;
    }

    struct poly *ptr3 = head3;
    struct poly *temp = NULL;
    while (ptr3->next != NULL)
    {
        if (ptr3->exp == ptr3->next->exp)
        {
            ptr3->coeff = ptr3->coeff + ptr3->next->coeff;
            temp = ptr3->next;
            ptr3->next = ptr3->next->next;
            delete temp;
        }
        else
            ptr3 = ptr3->next;
    }
    cout << "Multiplied Polynomial is: ";
    print(head3);
}
void polyErase(struct poly *p)
{
    int pos;
    cout << "Enter the position of term you want to delete: ";
    cin >> pos;
    struct poly *q;
    q = NULL;
    if (pos == 1)
    {
        head1 = head1->next;
        delete p;
    }
    else
    {
        pos--;
        while (pos--)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        delete p;
    }
    print(head1);
}
float polyEval(float a, struct poly *head)
{
    float sum = 0;
    while (head != NULL)
    {
        sum = sum + head->coeff * pow(a, head->exp);
        head = head->next;
    }
    return sum;
}
int main()
{
    float a;
    int choice;
    cout << "Enter polynomial 1--> \n";
    head1 = create(head1);
    cout << "Enter polynomial 2--> \n";
    head2 = create(head2);

    print(head1);
    print(head2);
    cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Erase or Delete a term\n5. Evaluate for a number\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        polyAdd(head1, head2);
        break;
    case 2:
        polySub(head1, head2);
        break;
    case 3:
        polyMult(head1, head2);
        break;
    case 4:
        polyErase(head1);
        break;
    case 5:
        cout << "Enter a floating point number: ";
        cin >> a;
        cout << "Evaluated Expression gives value --> " << polyEval(a, head1);
    }
}