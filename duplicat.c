#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int size;
} List;

List *creatlist() {
    List *p = (List*)malloc(sizeof(List));
    if (p == NULL) {
        fprintf(stderr, "Erreur!\n");
        return NULL;
    }
    p->head = NULL;
    p->size = 0;
    return p;
}

Node *creatNode(int value) {
    Node *p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        fprintf(stderr, "Erreur!\n");
        return NULL;
    }
    p->data = value;
    p->next = NULL;
    return p;
} 

void insertdebut(List *list, int value) {
    if (list == NULL) {
        fprintf(stderr, "Erreur!\n");
        return;
    }
    
    Node *p = creatNode(value);
    if (p == NULL) return;
    if(list->head==NULL){
        list->head=p;
        return;
    }
    p->next = list->head;
    list->head = p;
    list->size++;
}

void desplay(List *list) {
    if (list == NULL || list->head == NULL) {
        printf("Liste vide\n");
        return;
    }

    Node *temp = list->head;
    while (temp != NULL) {
        printf("[%d]->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freelist(List *list) {
    if (list == NULL) return;

    Node *current = list->head;
    Node *nextNode;
    
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(list);
}

void insertend(List *list, int value) {
    if (list == NULL) {
        fprintf(stderr, "Erreur!\n");
        return;
    }

    Node *imp = creatNode(value);
    if (list->head == NULL) {
        list->head = imp;
    } else {
        Node *pr = list->head;
        while (pr->next != NULL) {
            pr = pr->next;
        }
        pr->next = imp;
    }
    list->size++;
}

int removebegining(List *list) {
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "Erreur: Liste vide\n");
        return -1;
    }

    Node *imp = list->head;
    int data = imp->data;

    list->head = imp->next;
    free(imp);
    list->size--;

    return data;
}

int getat(List *list, int index) {
    if (list == NULL || list->head == NULL || index < 0 || index >= list->size) {
        printf("Erreur\n");
        return -1;
    }

    Node *imp = list->head;
    for (int i = 0; i < index; i++) {
        imp = imp->next;
    }
    return imp->data;
}

bool empty(List *list) {
    return (list == NULL || list->head == NULL);
}

void addposition(List *list, int value, int position) {
    if (list == NULL || position < 0 || position >= list->size) {
        fprintf(stderr, "Erreur!\n");
        return;
    }
    Node *node = creatNode(value);

    if (position == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        Node *imp = list->head;
        for (int i = 0; i < position - 1; i++) {
            imp = imp->next;
        }
        node->next = imp->next;
        imp->next = node;
    }
    list->size++;
}

void removeAt(List *list, int position) {
    if (list == NULL || list->head == NULL || position < 0 || position >= list->size) {
        fprintf(stderr, "Erreur: Position invalide\n");
        return;
    }

    Node *current = list->head;

    if (position == 0) {
        list->head = current->next;
        free(current);
        list->size--;
        return;
    }

    Node *previous = NULL;
    for (int i = 0; i < position; i++) {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    free(current);
    list->size--;
}

int taille(List *list) {
    return (list == NULL) ? 0 : list->size;
}

void reverse(List *list){
   if(list==NULL){
    fprintf(stderr,"erreur");
    return;
   }
    Node *temp=NULL;
    Node *temp2;
    while(list->head!=NULL){
          temp2=list->head->next;
          list->head->next=temp;
          temp=list->head;
          list->head=temp2;
}
    list->head=temp;
}
List *concatenation(List *list1, List *list2) {
    if (list1 == NULL || list2 == NULL) return NULL;

    if (list1->head == NULL) return list2;
    if (list2->head == NULL) return list1;

    Node *imp = list1->head;
    while (imp->next != NULL) {
        imp = imp->next;
    }
    imp->next = list2->head;
    list1->size += list2->size;

    return list1;
}

void detectioncycle(List *list) {
    if (list == NULL || list->head == NULL) {
        printf("Votre liste chaînée n'est pas cyclique\n");
        return;
    }

    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow) {
            printf("\n Votre liste chaine est cyclique\n");
            return;
        }
    }
    printf("\n Votre liste chaine pas cyclique\n");
}

Node *findMiddle(List *list) {
    Node *slow = list->head;
    Node *fast = list->head;
    while(fast->next!=NULL && slow!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}

void removdeplucated(List *list){
    Node *tete=list->head;
    Node *prev,*temp,*current;
    current=tete;
    while(current!=NULL && current->next!=NULL){
        temp=current->next;
        prev=current;
        while(temp!=NULL){
            if(current->data==temp->data){
                prev->next=temp->next;
                free(temp);
                temp=prev->next;
            }
            else{
                prev=temp;
                temp=temp->next;
            }
        }
        current=current->next;
    }
}

void tribull(List *list){
    Node *tete=list->head;
    if(tete==NULL || tete->next==NULL)
     return;
     Node *dernier=NULL;
     int imp;
     int echange;
     Node *current;
     do{
        current=tete;
        echange=0;
         while(current->next!=dernier){
            if(current->data>current->next->data){
                 imp=current->data;
                 current->data=current->next->data;
                 current->next->data=imp;
                 echange=1;
            }
            current=current->next;
         }
         dernier=current;
     }while(echange==1);
}

void triselection(List *list){
    Node *tete=list->head;
    if(tete==NULL || tete->next==NULL){
        return;
    }
   int valuemin;
   Node *current;
   Node *imp,*min;
   for(current=tete;current->next!=NULL;current=current->next){
          min=current;
          valuemin=current->data;
         for(imp=current->next;imp!=NULL;imp=imp->next){
            if(imp->data<valuemin){
                min=imp;
                valuemin=imp->data;
            }
            if(valuemin!=current->data){
                imp->data=current->data;
                current->data=valuemin;
            }
        }
   }
}
 
Node *fusion(Node *gauche, Node *droite) {
    if (gauche==NULL) return droite;
    if (droite==NULL) return gauche;

    Node *resultat = NULL;

    if (gauche->data < droite->data) {
        resultat = gauche;
        resultat->next = fusion(gauche->next, droite);
    } else {
        resultat = droite;
        resultat->next = fusion(gauche, droite->next);
    }
    return resultat;
}

void divise(Node *tete, Node **gauche, Node **droite) {
    if (!tete || !tete->next) {
        *gauche = tete;
        *droite = NULL;
        return;
    }

    Node *slow = tete, *fast = tete->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *gauche = tete;
    *droite = slow->next;
    slow->next = NULL; 
}


Node *trifusion(Node *tete) {
    if (!tete || !tete->next) return tete; 

    Node *gauch, *droit;
    divise(tete, &gauch, &droit); 

    gauch = trifusion(gauch); 
    droit = trifusion(droit); 

    return fusion(gauch, droit); 
}

void sortList(List *list) {
    if (!list || !list->head) return; 
    list->head = trifusion(list->head);
}

int main() {
    List *list = creatlist();
    if (list == NULL) return 1;

    insertdebut(list, 23);
    insertdebut(list, 88);
    insertdebut(list, 56);
    insertdebut(list, 90);
    insertdebut(list, 33);
    insertdebut(list, 88);

    desplay(list);

    printf("\nAjout en fin de liste:\n");
    insertend(list, 2005);
    desplay(list);

    int data = removebegining(list);
    printf("\nValeur supprimee en debut: %d\n", data);
    desplay(list);
    int pos;
    do {
        printf("\nEntrez la position pour inserer un noeud: ");
        scanf("%d", &pos);
    } while (pos < 0 || pos > list->size);

    addposition(list, 1999, pos);
    desplay(list);
 
    printf("\n your data get at from position %d is %d \n",pos,getat(list,pos));
    printf("\nSuppression d un noeud a la position %d\n", pos);
    removeAt(list, pos);
    desplay(list);

    printf("\nListe inversee:\n");
    reverse(list);
    desplay(list);

    detectioncycle(list);
     
    List *list1= creatlist();
    if (list == NULL) return 1;

    insertdebut(list, 33);
    insertdebut(list, 33);
    insertdebut(list,56);
    printf("\n concatenation de votre deux listes : \n");
    list=concatenation(list,list1);
    desplay(list);
    Node *middle=findMiddle(list);
    printf("\n your data middle is %d \n",middle->data);

    printf("\n\n your minled liste remove deplucated : \n");
    removdeplucated(list);
    desplay(list);

    printf("\n votre liste trie par bull :\n ");
    tribull(list);
    desplay(list);
   
    printf("\n\n votre liste trie par selection:\n");
    triselection(list);
    desplay(list);

    printf("\n\n votre liste trie par fusion :\n");
    sortList(list);
    desplay(list);
    freelist(list);
    return 0;
}