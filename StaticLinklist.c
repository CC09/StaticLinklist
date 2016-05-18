// 静态链表 的实现与测试
 #include <stdio.h>

 #define MAXN 16 // capacity of list.
 typedef int element; // element type.

 // define boolean type:
 typedef int bool;
 #define true -1
 #define false 0

 #define NPTR -1 // null pointer definition. can not between 0 to MAXN-1.
 typedef int pointer;

 #define DEBUGVAL(x) printf("%s: %d\n", #x, (x)); // a macro for debug.

 struct __node
 {
     element data;
     pointer next;
 }SLList[MAXN];
 pointer ifree, idata;

 #define nextof(p) SLList[p].next
 #define dataof(p) SLList[p].data

 #define _alloc(d) ifree; dataof(ifree)=(d); ifree != NPTR ? ifree=nextof(ifree) : NPTR
 #define _free(p)  nextof(p)=ifree; ifree = p

 void init()
 {
     int i;
     ifree = 0;
     idata = NPTR;
     for( i=0; i < MAXN-1; i++) 
         nextof(i) = i+1;
     nextof(i) = NPTR;
 }

 // clear all nodes.
 void clear() { init(); }

 // push val to front.
 bool push_front(element val)
 {
     pointer tmp, np;
     if( ifree != NPTR ) {
         np = _alloc(val);
         nextof(np) = idata;
         idata = np;
         return true;
     }
     return false;
 }

 // push val to end of list.
 bool push_back(element val)
 {
     if( idata == NPTR ) { // 空表，直接写入
         idata = _alloc(val);
         nextof(idata) = NPTR;
         return true;
     }
     if( ifree != NPTR ) { // 非空，先找到最后一个节点
         pointer last = idata, np;
         while( nextof(last) != NPTR ) last = nextof(last);        
         np = _alloc(val);
         nextof(np) = NPTR;
         nextof(last) = np;
         return true;
     }
     return false;
 }

 // insert val to after p pointed node.
 bool insert_after(pointer p, element val)
 {
     if( ifree != NPTR && p != NPTR ) {
         pointer pn = _alloc(val);
         nextof(pn) = nextof(p);
         nextof(p)  = pn;        
         return true;
     }
     return false;
 }

 // insert to the position in front of p.
 bool insert(pointer ptr, element val)
 {
     if( ifree == NPTR ) return false;  // 没有结点，直接返回
     if( ptr == idata ) { // 有一个节点
         pointer np = _alloc(val);
         nextof(np) = idata;
         idata = np;    
         return true;
     }
     else { // 其他情况，先找 ptr 的前驱，再插入
         pointer p = idata;
         while(  p != NPTR ) {
             if( nextof(p) == ptr ) { // find p -- the prev node of ptr.
                 return insert_after(p, val); // insert val after p.            
             }
            p = nextof(p);
         }
     }
     return false;
 }

 // find element, return the prev node pointer.
 pointer find_prev(element val)
 {
     pointer p = idata;
     while(  p != NPTR ) {
         if( dataof( nextof(p) ) == val )
             return p;
         p = nextof(p);
     }
     return NPTR;
 }

 // find element, return the node  pointer.
 pointer find(element val)
 {
     pointer p = idata;
     while(  p != NPTR ) {
         if( dataof(p) == val ) return p;
         p = nextof(p);
     }
     return NPTR;
 }

 // pop front element.
 void pop_front()
 {
     if( idata != NPTR ) { // 将 data list 最前面的节点 移到 free list 上
 #if 0
         pointer p = idata;        
         idata = nextof(idata); // idata = nextof(idata);
         nextof(p) = ifree;  // SLList[p].next = ifree;
         ifree = p; 
 #else
         pointer p = idata;
         idata = nextof(idata);
         _free(p);
 #endif
     }
 }

 // pop back element.
 void pop_back()
 {
     if( idata == NPTR ) return;
     if( nextof(idata) == NPTR ) { // only 1 node.
         nextof(idata) = ifree;
         ifree = idata;
         idata = NPTR;
     }
     else { // 找到最后一个节点 p，以及它的前驱 q.
         // TODO: find the last node p, and it's perv node q. 
         pointer p = idata, q; 
         while( nextof(p) != NPTR ) {
             q = p;
             p = nextof( p );
         }
         // remove *p to free list, update nextof(q) to NPTR.
         nextof(p) = ifree;
         ifree = p;
         nextof(q) = NPTR;
     }
 }

 void show()
 {
     pointer p = idata;
     for( ; p != NPTR; p = nextof(p) ) {
         printf(" %3d ", dataof(p) );
     }
     printf("\n");
 }

 #define INFOSHOW
 void info()
 {
 #ifdef INFOSHOW
     int i;    
     DEBUGVAL(ifree);
     DEBUGVAL(idata);
     puts("====================\n"
         "index\tdata\tnext\n"
         "--------------------");
     for(i=0; i<MAXN; i++) {
         printf("%d\t%d\t%d\n", i, SLList[i].data, SLList[i].next);
     }
     puts("====================\n");
 #endif
 }

 /*
     测试程序：
 */
 int main()
 {
     int i;
     init();

 #if 1  // push_front test:
     puts("push_front test:");
     for(i=0; i<MAXN+2; i++)    {
         push_front(2*i+1);
         show();    
     }

     puts("pop_front test:");
     for(i=0; i<MAXN+2; i++)    {
         pop_front();
         show();
     }
 #endif

 #if 1 // push_back test:
     puts("push_back test:");
     for(i=0; i<MAXN+2; i++)    {
         push_back((i+1)*10);
         show();    
     }

     puts("pop_back test:");
     for(i=0; i<MAXN+1; i++)
     {
         pop_back();
         show();
     }
 #endif

 #if 1 // insert test:
     puts("insert test:");
     for(i=0; i<MAXN+2; i++)
     {
         insert(idata, (i+1)*10);
         show();
     }
     puts("clear...\n");
     clear();
 #endif

 #if 1 // insert_after test:
     puts("insert_after test:");
     push_back(-99);
     for(i=0; i<MAXN+1; i++) {
         insert_after(idata, i+1);
         show();
     }
     puts("clear...\n");
     clear();
 #endif

 #if 1 // find test:
     puts("find test:");
     for(i=0; i<MAXN/2; i++) {
         push_front(MAXN-i);
         push_back(MAXN/2-i);
         //show();
     }
     show();
     info();
     for(i=0; i<MAXN; i++) {
         int val = rand()%(2*MAXN);
         pointer p = find(val);
         if( p != NPTR )
             printf("%3d %3d found at %d\n", val, dataof(p), p);
         else
             printf("%3d not found\n", val);
     }
 #endif

 #if 1
     puts("\nfind_prev test:");
     for(i=0; i<MAXN; i++) {
         int val = rand()%(2*MAXN);
         pointer p = find_prev(val);
         if( p != NPTR )
             printf("%3d %3d found at %d's next.\n", val, dataof(nextof(p)), p);
         else
             printf("%3d not found\n", val);
     }
 #endif 

 #if 1 // find_prev and insert_after test:
     clear();
     puts("\nfind_prev and insert_after test:");
     for(i=0; i<MAXN/2; i++)    {
         push_front(MAXN/2-i);
     }
     show();
     for(i=0; i<MAXN/2; i++) {
         int val = rand()%(2*MAXN), n=-(i+1);
         pointer p = find_prev(val);
         if( p != NPTR ) {
             printf("insert %d to front of %d:", n, val);
             insert_after(p, n);
             show();
         }
     }    
 #endif    

 #if 1 // find and insert test:
     clear();
     puts("\nfind and insert test:");
     for(i=0; i<MAXN/2; i++)    {
         push_front(MAXN/2-i);
     }
     show();
         for(i=0; i<MAXN/2; i++) {
         int val = rand()%MAXN, n=-(i+1);
         pointer p = find(val);
         if( p != NPTR ) {
             printf("insert %d to after of %d:", n, val);
             insert_after(p, n);
             show();
         }
     }
 #endif

     puts("end of main().");    
     return 0;
 }
