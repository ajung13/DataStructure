#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

struct bitmapitem{
    int size;
    struct bitmap *bm;
};
struct list_elem *elem_init(int data);
static bool lessfunc (const struct list_elem *a, const struct list_elem *b, void *aux);

struct hash_elem *hashelem_init(int data);
static unsigned hashfunc (const struct hash_elem *h, void *aux);
static bool lesshash (const struct hash_elem *a, const struct hash_elem *b, void *aux);


int main(){
    char *oneline = (char*)malloc(40*sizeof(char));
    char *p;
    int input, input2;		//list inputs
    int a, b, c;		//integer inputs
    int i;

    struct list tlist[10];
    struct list_elem *e, *e1, *e2, *enew;

    struct hash thash[10];
    struct hash_elem *h, *hnew;
    struct hash_iterator Hi;

    struct bitmapitem tbit[10];
    struct bitmap *tb;
    struct elem_type *bt;

    for (i=0; i<10; i++)
        tbit[i].size = 0;


    while(1){
	fgets(oneline, 40, stdin);
	if((p=strchr(oneline, '\n'))!=NULL) *p = '\0';

	if(!strcmp(oneline, "quit"))
	    break;


	else if(!strncmp(oneline, "create list ", 12)){
	    sscanf(oneline, "%*12c %*4c %d", &input);
	    list_init(&tlist[input]);
	}

	else if(!strncmp(oneline, "create hashtable ", 17)){
	    sscanf(oneline, "%*17c %*4c %d", &input);
	    hash_init(&thash[input], &hashfunc, &lesshash, NULL);
	}
	else if(!strncmp(oneline, "create bitmap ", 14)){
	    sscanf(oneline, "%*14c %*2c %d %d", &input, &a);
	    tbit[input].bm = bitmap_create(a);
	    tbit[input].size = 0;
	}


	else if(!strncmp(oneline, "dumpdata ", 9)){
	    sscanf(oneline, "%*9c %[^\n]", oneline);
	    if(!strncmp(oneline, "list", 4)){
		    sscanf(oneline, "%*4c %d", &input);
		    i = 0;		//flag whether the list is empty or not.
		    for (e = list_begin(&tlist[input]); e != list_end(&tlist[input]); e = list_next(e)){
			printf("%d ", (list_entry(e, struct listitem, elem))->data);
			i = 1;
		    }
		    if(i==1)	printf("\n");
	    }
	    else if(!strncmp(oneline, "hash", 4)){
		sscanf(oneline, "%*4c %d", &input);
		i = 0;

		hash_first(&Hi, &thash[input]);
		while(hash_next(&Hi)){
		    printf("%d ", (hash_entry(hash_cur(&Hi), struct hashitem, elem))->data);
		    i = 1;
		}
		if(i==1)    printf("\n");
	    }
	    else if(!strncmp(oneline, "bm", 2)){
		sscanf(oneline, "%*2c %d", &input);
		tb = tbit[input].bm;
		a = bitmap_size(tb);
		if(a == 0)   continue;
		for(i = 0; i<a; i++)
		    printf("%d", bitmap_test(tbit[input].bm, i));
		printf("\n");
	    }
	}


	else if(!strncmp(oneline, "list_insert ", 12)){
	    //list_insert list0 1 2 <- 1번 자리에 2 넣기 (0이 시작)
	    sscanf(oneline, "%*12c %*4c %d %d %d", &input, &a, &b);
	    enew = elem_init(b);
	    e = list_begin(&tlist[input]);
	    for (i = 0; i < a; i++) e = list_next(e);
	    list_insert (e, enew);
	}

	else if(!strncmp(oneline, "list_push_front ", 16)){
	    sscanf(oneline, "%*16c %*4c %d %d", &input, &a);
	    enew = elem_init(a);
	    list_push_front(&tlist[input], enew);
	}
	else if(!strncmp(oneline, "list_push_back ", 15)){
	    sscanf(oneline, "%*15c %*4c %d %d", &input, &a);
	    enew = elem_init(a);
	    list_push_back(&tlist[input], enew);
	}
	else if(!strncmp(oneline, "list_pop_front ", 15)){
	    sscanf(oneline, "%*15c %*4c %d", &input);
	    list_pop_front(&tlist[input]);
	}
	else if(!strncmp(oneline, "list_pop_back ", 14)){
	    sscanf(oneline, "%*14c %*4c %d", &input);
	    list_pop_back(&tlist[input]);
	}

	else if(!strncmp(oneline, "list_front ", 11)){
	    sscanf(oneline, "%*11c %*4c %d", &input);
	    e = list_begin(&tlist[input]);
	    printf("%d\n", (list_entry(e, struct listitem, elem))->data);
	}
	else if(!strncmp(oneline, "list_back ", 10)){
	    sscanf(oneline, "%*10c %*4c %d", &input);
	    e = list_rbegin(&tlist[input]);
	    printf("%d\n", (list_entry(e, struct listitem, elem))->data);
	}


	else if(!strncmp(oneline, "list_size ", 10)){
	    sscanf(oneline, "%*10c %*4c %d", &input);
	    printf("%u\n", list_size(&tlist[input]));
	}
	else if(!strncmp(oneline, "list_empty ", 11)){
	    sscanf(oneline, "%*11c %*4c %d", &input);
	    if(list_empty(&tlist[input]))
		printf("true\n");
	    else    printf("false\n");
	}


	else if(!strncmp(oneline, "list_remove ", 12)){
	    sscanf(oneline, "%*12c %*4c %d %d", &input, &a);
	    e = list_begin(&tlist[input]);
	    for(i = 0; i < a; i++)  e = list_next(e);
	    list_remove(e);
	}



	else if(!strncmp(oneline, "delete ", 7)){
	    sscanf(oneline, "%*7c %[^\n]", oneline);
	    if(!strncmp(oneline, "list", 4)){
		sscanf(oneline, "%*4c %d", &input);
		while(!list_empty(&tlist[input]))
		   list_pop_front(&tlist[input]);
	    }
	    else if(!strncmp(oneline, "hash", 4)){
		sscanf(oneline, "%*4c %d", &input); 
		hash_first(&Hi, &thash[input]);
		while((h=hash_next(&Hi)) != NULL){
		    free( hash_delete(&thash[input], h));
		}
	    }
	    else if(!strncmp(oneline, "bm", 2)){
		sscanf(oneline, "%*2c %d", &input);
		bitmap_destroy(tbit[input].bm);
		tbit[input].size = 0;
	    }
	}


	else if(!strncmp(oneline, "list_splice ", 12)){
	    //list_splice list0 2 list1 1 4
	    //	list0의 2번째 자리 앞에 list1의 1~4번째 수를 넣는다
	    sscanf(oneline, "%*12c %*4c %d %d %*4c %d %d %d", &input, &a, &input2, &b, &c);
	    e = list_begin(&tlist[input]);
	    e1 = list_begin(&tlist[input2]);
	    e2 = list_begin(&tlist[input2]);
	    for(i = 0; i < a; i++)  e = list_next(e);
	    for(i = 0; i < c; i++){
		if(i < b)   e1 = list_next(e1);
		e2 = list_next(e2);
	    }
	    list_splice(e, e1, e2);
	}
	else if(!strncmp(oneline, "list_reverse ", 13)){
	    sscanf(oneline, "%*13c %*4c %d", &input);
	    list_reverse(&tlist[input]);
	}


	else if(!strncmp(oneline, "list_insert_ordered ", 20)){
	    sscanf(oneline, "%*20c %*4c %d %d", &input, &a);
	    enew = elem_init(a);
	    list_insert_ordered(&tlist[input], enew, &lessfunc, NULL);
	}
	else if(!strncmp(oneline, "list_max ", 9)){
	    sscanf(oneline, "%*9c %*4c %d", &input);
	    e = list_max (&tlist[input], &lessfunc, NULL);
	    printf("%d\n", (list_entry(e, struct listitem, elem))->data);
	}
	else if(!strncmp(oneline, "list_min ", 9)){
            sscanf(oneline, "%*9c %*4c %d", &input);
            e = list_min (&tlist[input], &lessfunc, NULL);
            printf("%d\n", (list_entry(e, struct listitem, elem))->data);
        }
	else if(!strncmp(oneline, "list_sort ", 10)){
	    sscanf(oneline, "%*10c %*4c %d", &input);
	    list_sort (&tlist[input], &lessfunc, NULL);
	}
	else if(!strncmp(oneline, "list_swap ", 10)){
	    sscanf(oneline, "%*10c %*4c %d %d %d", &input, &a, &b);
	    e1 = list_begin(&tlist[input]);
	    e2 = list_begin(&tlist[input]);
	    for (i=0; i<b; i++){
		if(i<a)	e1 = list_next(e1);
		e2 = list_next(e2);
	    }
	    list_swap(e1, e2);
	}
	else if(!strncmp(oneline, "list_unique ", 12)){
	    input2 = -1;
	    sscanf(oneline, "%*12c %*4c %d %*4c %d", &input, &input2);
	    if (input2 == -1)
		list_unique(&tlist[input], NULL, &lessfunc, NULL);
	    else{
		list_unique(&tlist[input], &tlist[input2], &lessfunc, NULL);
	    }
	}


	else if(!strncmp(oneline, "hash_insert ", 12)){
	    sscanf(oneline, "%*12c %*4c %d %d", &input, &a);
	    hnew = hashelem_init(a);
	    hash_insert(&thash[input], hnew);
	}

	else if(!strncmp(oneline, "hash_apply ", 11)){
	    a = 0;
	    sscanf(oneline, "%*11c %*4c %d %s", &input, oneline);
	    if(!strncmp(oneline, "triple", 6))	    a = 1;
	    else if(!strncmp(oneline, "square", 6)) a = 2;
	    else    continue;

	    hash_first(&Hi, &thash[input]);
	    while(h = hash_next(&Hi)){
		struct hashitem *tmph = hash_entry(h, struct hashitem, elem);
		if(a==1)    tmph->data = (tmph->data)*(tmph->data)*(tmph->data);
		else	    tmph->data = (tmph->data)*(tmph->data);
	    }

	}

	else if(!strncmp(oneline, "hash_delete ", 12)){
	    sscanf(oneline, "%*12c %*4c %d %d", &input, &a);
	    b = 0;	    //flag whether there is 'a' in hash table
	    hash_first(&Hi, &thash[input]);
	    while(h = hash_next(&Hi)){
		struct hashitem *tmph = hash_entry(h, struct hashitem, elem);
		if(tmph->data == a){
		    b = 1;
		    break;
		}
	    }
	    if(b == 1)		hash_delete(&thash[input], h);
	}

	else if(!strncmp(oneline, "hash_empty ", 11)){
	    sscanf(oneline, "%*11c %*4c %d", &input);
	    if(hash_empty(&thash[input]))
		printf("true\n");
	    else    printf("false\n");
	}

	else if(!strncmp(oneline, "hash_size ", 10)){
	    sscanf(oneline, "%*10c %*4c %d", &input);
	    printf("%d\n", hash_size(&thash[input]));
	}

	else if(!strncmp(oneline, "hash_clear ", 11)){
	    sscanf(oneline, "%*11c %*4c %d", &input);
	    hash_clear(&thash[input], NULL);
	}
	else if(!strncmp(oneline, "hash_find ", 10)){
	    sscanf(oneline, "%*10c %*4c %d %d", &input, &a);
	    hash_first(&Hi, &thash[input]);
	    b = 0;	    //flag whether there is 'a' in hash table
	    while((h = hash_next(&Hi))!=NULL){
		struct hashitem *tmph = hash_entry(h, struct hashitem, elem);
		if(tmph->data == a){
		    b = 1;
		    break;
		}
	    }
	    if(b==1)	printf("%d\n", a);
	}
	else if(!strncmp(oneline, "hash_replace ", 13)){
	    sscanf(oneline, "%*13c %*4c %d %d", &input, &a);
	    hnew = hashelem_init(a);
	    hash_replace(&thash[input], hnew);
	}



	else if(!strncmp(oneline, "bitmap_mark ", 12)){
	    sscanf(oneline, "%*12c %*2c %d %d", &input, &a);
	    tb = tbit[input].bm;
	    bitmap_mark(tb, a);
	    tbit[input].size++;
	}
	else if(!strncmp(oneline, "bitmap_all ", 11)){
	    sscanf(oneline, "%*11c %*2c %d %d %d", &input, &a, &b);
	    tb = tbit[input].bm;
	    if(bitmap_all(tb, a, b))
		printf("true\n");
	    else    printf("false\n");
	}
	else if(!strncmp(oneline, "bitmap_any ", 11)){
	    sscanf(oneline, "%*11c %*2c %d %d %d", &input, &a, &b);
	    tb = tbit[input].bm;
	    if(bitmap_any(tb, a, b))
		printf("true\n");
	    else    printf("false\n");
	}
	else if(!strncmp(oneline, "bitmap_contains ", 16)){
	    sscanf(oneline, "%*16c %*2c %d %d %d %s", &input, &a, &b, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		i = bitmap_contains(tb, a, b, true);
	    else if(!strncmp(oneline, "false", 5))
		i = bitmap_contains(tb, a, b, false);
	    else{
	    	printf("Input error\n");
		continue;
	    }
	    if(i == true)   printf("true\n");
	    else    printf("false\n");
	}
	else if(!strncmp(oneline, "bitmap_count ", 13)){
	    sscanf(oneline, "%*13c %*2c %d %d %d %s", &input, &a, &b, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
                i = bitmap_count(tb, a, b, true);
            else if(!strncmp(oneline, "false", 5))
                i = bitmap_count(tb, a, b, false);
            else{
                printf("Input error\n");
                continue;
            }
	    printf("%d\n", i);
	}
	else if(!strncmp(oneline, "bitmap_dump ", 12)){
	    sscanf(oneline, "%*12c %*2c %d", &input);
	    tb = tbit[input].bm;
	    bitmap_dump(tb);
	}
	else if(!strncmp(oneline, "bitmap_set_all ", 15)){
	    sscanf(oneline, "%*15c %*2c %d %s", &input, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		bitmap_set_all(tb, true);
	    else if(!strncmp(oneline, "false", 5))
		bitmap_set_all(tb, false);
	    else	printf("Input error\n");
	}
	else if(!strncmp(oneline, "bitmap_flip ", 12)){
	    sscanf(oneline, "%*12c %*2c %d %d", &input, &a);
	    tb = tbit[input].bm;
	    bitmap_flip(tb, a);
	}
	else if(!strncmp(oneline, "bitmap_none ", 12)){
	    sscanf(oneline, "%*12c %*2c %d %d %d", &input, &a, &b);
	    tb = tbit[input].bm;
	    if( bitmap_none(tb, a, b) )
		printf("true\n");
	    else    printf("false\n");
	}
	else if(!strncmp(oneline, "bitmap_reset ", 13)){
	    sscanf(oneline, "%*13c %*2c %d %d", &input, &a);
	    tb = tbit[input].bm;
	    bitmap_reset(tb, a);
	}
	else if(!strncmp(oneline, "bitmap_scan ", 12)){
	    sscanf(oneline, "%*12c %*2c %d %d %d %s", &input, &a, &b, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		i = bitmap_scan(tb, a, b, true);
	    else if(!strncmp(oneline, "false", 5))
		i = bitmap_scan(tb, a, b, false);
	    else        printf("Input error\n");
	    printf("%u\n", i);
	}
	else if(!strncmp(oneline, "bitmap_scan_and_flip ", 21)){
	    sscanf(oneline, "%*21c %*2c %d %d %d %s", &input, &a, &b, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		i = bitmap_scan_and_flip(tb, a, b, true);
	    else if(!strncmp(oneline, "false", 5))
		i = bitmap_scan_and_flip(tb, a, b, false);
	    else        printf("Input error\n");
	    printf("%u\n", i);
	}
	else if(!strncmp(oneline, "bitmap_set ", 11)){
	    sscanf(oneline, "%*11c %*2c %d %d %s", &input, &a, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		bitmap_set(tb, a, true);
	    else if(!strncmp(oneline, "false", 5))
		bitmap_set(tb, a, false);
	    else    printf("Input error\n");
	}
	else if(!strncmp(oneline, "bitmap_set_multiple ", 20)){
	    sscanf(oneline, "%*20c %*2c %d %d %d %s", &input, &a, &b, oneline);
	    tb = tbit[input].bm;
	    if(!strncmp(oneline, "true", 4))
		bitmap_set_multiple(tb, a, b, true);
	    else if(!strncmp(oneline, "false", 5))
		bitmap_set_multiple(tb, a, b, false);
	    else    printf("Input error\n");
	}
	else if(!strncmp(oneline, "bitmap_size ", 12)){
	    sscanf(oneline, "%*12c %*2c %d", &input);
	    tb = tbit[input].bm;
	    printf("%d\n", bitmap_size(tb));
	}
	else if(!strncmp(oneline, "bitmap_test ", 12)){
	    sscanf(oneline, "%*12c %*2c %d %d", &input, &a);
	    tb = tbit[input].bm;
	    if(bitmap_test(tb, a))
		printf("true\n");
	    else    printf("false\n");
	}
	else if(!strncmp(oneline, "bitmap_expand ", 14)){
	    sscanf(oneline, "%*14c %*2c %d %d", &input, &a);
	    tb = tbit[input].bm;
	    tbit[input].bm = bitmap_expand(tb, a);
	}


	else
	    printf("Input error\n");
   

    }

    return 0;
}


struct list_elem *elem_init(int data){
    struct listitem *tmp;
    tmp = (struct listitem*)malloc(sizeof(struct listitem));
    tmp->data = data;
    return &(tmp->elem);
}


static bool lessfunc (const struct list_elem *a, const struct list_elem *b, void *aux){
    int num1 = (list_entry(a, struct listitem, elem))->data;
    int num2 = (list_entry(b, struct listitem, elem))->data;
    
    return num1 < num2;
}



struct hash_elem *hashelem_init(int data){
    struct hashitem *tmp;
    tmp = (struct hashitem*)malloc(sizeof(struct hashitem));
    tmp->data = data;
    return &tmp->elem;
}

static unsigned hashfunc (const struct hash_elem *h, void *aux){
    int num = (hash_entry(h, struct hashitem, elem))->data;
    return hash_int(num);
}

static bool lesshash (const struct hash_elem *a, const struct hash_elem *b, void *aux){
    int num1 = (hash_entry(a, struct hashitem, elem))->data;
    int num2 = (hash_entry(b, struct hashitem, elem))->data;

    return num1 < num2;
}
