/*业务逻辑实现*/

#include"implementation.h"

#include<stdio.h>
int versize=0;
int allEageWeights[500]={0};//因为文件里面的前versize行都是存放顶点0到顶点n的图结构情况，所以可以直接用一个数组把所有顶点0到其他任意车位的weight保存起来，方便后期调用
CarportInfo allCarInfo[500];//应该设置成全局变量更好

//初始化
void seq_init(SeqList *L)
{
	L->size=0;
}

int PrintData(SeqList *L)//逐个输出顺序表所有元素
{
	int i;
	if(L->size<0)
	{
		printf("无数据\n");
		return 0;
	}
	else
	{
		printf("数据元素如下\n");
		for(i=0;i<L->size;i++)
		{
			printf("%d\t",L->list[i]);
		}
		return 1;
	}
}

int ListFind(SeqList L,int x)//定位函数
{
	int i;
	if(L.size<0)
	{
		printf("无数据\n");
		return 0;
	}
	else
	{
		for(i=0;i<L.size;i++)
		{
			if(L.list[i]==x)
			{
				printf("已找到指定数据\n");
				return i;
			}
		}
		printf("未找到指定数据\n");
		return -1;
	}
}

int InsertData(SeqList *L,int i)//将数据元素i插入递增有序的顺序表L中，以保持该顺序表的有序性
{
	int j,k;//j遍历整个线性表，k为插入过程遍历部分线性表
	if(L->size<0)
	{
		printf("该顺序表无数据\n");
		return 0;
	}
	if(L->size>=MAXSIZE)
	{
		printf("顺序表已满无法插入\n");
		return 0;
	}
	else
	{
		for(j=0;j<L->size;j++);

				L->list[j]=i;
				L->size++;
				//printf("顺序表 L->size =%d\n",L->size);
				return 1;
			
		
		return 0;
	}
}

int getdata(SeqList L,int i,int *x){
	*x=L.list[i];
	return *x;
}

////////////////////////////////////////////////
//////////////图结构////////////////////////////
///////////////////////////////////////////////

//GraphOfMatrix邻接矩阵
//GraphOfList邻接表


//////////////////////////////////////////////////
//////////////////////邻接矩阵////////////////////
/////////////////////////////////////////////////

//初始化（邻接矩阵）
void init(GraphOfMatrix *G,int n){	//n为顶点数
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i==j){
				G->edge[i][j]=0;//对角线置0
			}
			else{
				G->edge[i][j]=MAXWEIGHT;
			}
		}
		G->edgecount=0;

		G->ver.size=0;//顺序表初始化
}


//插入顶点（邻接矩阵）
void arr_insertver(GraphOfMatrix *G,int vertex){	//vertex为顶点
	InsertData(&G->ver,vertex);//将vertex插入递增有序的顺序表L中
	//G->ver.size++;
	//printf("插入顶点成功，此时 G->ver.size为%d\n",G->ver.size);
}

//插入边（邻接矩阵）
void arr_insertedge(GraphOfMatrix *G,int v1,int v2,int weight){
	//if( v1<0 || v2<0 || v1>G->ver.size || v2>G->ver.size ){	//边存在
	//	printf("异常，无法插入边\n");
	//	return ;
	//}
	//else{
		G->edge[v1][v2]=weight;	//权值
		G->edgecount++;
	//}
}


/*********************************取第一个邻接顶点***************************************/
/*****************1.查询相邻的所有车位      2.查询下一个车位******************************/
/**************************************************************************************/

//1.用于查询相邻车位
//(考虑“上一个车位”/"下一个车位"---两个车位信息(列号)放在一个数组中)
//顶点v的第一个邻接顶点，就是邻接矩阵的顶点v行中从第一个矩阵元素开始的非0且非无穷大的顶点
int *GetFirstVex(GraphOfMatrix *G,int v){
	int col,okCol=0;
	int *vers;//全部初始化为0
	vers=(int *)malloc(sizeof(int)*2);
	if(v<0 || v>=G->ver.size){
		printf("参数v1越界出错\n");
		return NULL;
	}
	for(col=0;col<G->ver.size;col++){
		if(G->edge[v][col]>0 && G->edge[v][col]<MAXWEIGHT){
			vers[okCol]=col;
			//printf("找到第%d个相邻车位，车位号是%d\n",okCol+1,vers[okCol]);
			okCol++;
		}
	}
	return vers;
}


//2.只查询下一个车位，用于DFS遍历
int GetFirstVexWithOne(GraphOfMatrix *G,int v){
	int col;
	for(col=0;col<G->ver.size;col++){//遍历整条顺序表（第v行那条）
		if(G->edge[v][col]>0 && G->edge[v][col]<MAXWEIGHT){
			return col;
		}
		else
			return -1;
	}
}




//取下一个邻接顶点-(邻接矩阵的顶点v1行中从第v2+1个矩阵元素开始的非0且非无穷大的顶点)
//v1的邻接顶点v2的下一个邻接顶点
//DFS需要用到
int GetNextVex(GraphOfMatrix *G,int v1,int v2){
	int col;
	for(col=v2+1;col<G->ver.size;col++){//遍历顺序表，从v2+1这个点开始
		if(G->edge[v1][col]>0 &&G->edge[v1][col]<MAXWEIGHT){
			return col;
		}
		else
			return -1;
	}
}



//创建图	//rowcolweight edge[]为“图的边信息”结构体数组(邻接矩阵)
void creat_graph(GraphOfMatrix *G,int ver_arrs[],int ver_count,rowcolweight edge[],int edge_count){
	int i,j;
	init(G,ver_count);	//初始化，ver_count为顶点数

	for(i=0;i<ver_count;i++){	//创建顶点
		arr_insertver(G,ver_arrs[i]);
		//printf("顶点%d创建成功\n",i);
		versize=G->ver.size;
		//printf("versize=%d,G->ver.size=%d",versize,G->ver.size);
	}
	//if(i==ver_count)
		//printf("创建顶点成功\n");


	for(j=0;j<edge_count;j++){	//创建边
		arr_insertedge(G,edge[j].row,edge[j].col,edge[j].weight);
		//printf("边%d创建成功\n",j);
	}
	//if(j==edge_count)
	//	printf("创建边成功\n");

}
//输出（邻接矩阵）
void outputInfoOfMatrix(GraphOfMatrix *G,int versize){

	int i,j;
	printf("一共有%d个车位\n",G->ver.size);
	//printf("一共有%d个车位versize\n",versize);
	printf("\n");

	printf("车位的结构信息如下\n");
	for(i=0;i<versize;i++){
		for(j=0;j<G->ver.size;j++)
		{
			//printf("输出第%d条边",j);
			printf("%d\t",G->edge[i][j]);
		}
		printf("\n");
	}
}




///////////////////////////////////////////////////////
///////////////////邻接链表////////////////////////////
/////////////数组存储顶点，链表存储边信息///////////////
//////////////////////////////////////////////////////


/*
//上面有定义了
//创建图结构
typedef struct{
	int row;//行下标
	int col;//列下标
	int weight;//权值
}rowcolweight;//创建边信息结构体
*/

//初始化（邻接表）
void init_link(GraphOfList *G){
	int i;
	G->numofedges=0;
	G->numofverts=0;
	for(i=0;i<MAXVERTICES;i++){
		G->arr[i].adj=NULL;//置空
		G->arr[i].source=i;//初始化顶点各自对应的下标，从0开始
	}
}

//插入顶点-在数组操作（邻接表）
void arr_insertver_link(GraphOfList *G,int i,int vertex){
	if(i>=0 && i<MAXVERTICES){
		G->arr[i].data=vertex;
		G->numofverts++;
	}
	else{
		printf("插入顶点失败！\n");
		return ;
	}
}

//插入边-在链表操作（邻接表）
void arr_insertedge_link(GraphOfList *G,int v1,int v2,int weight){
	edge *e;//e为单链表表头
	e=(edge*)malloc(sizeof(edge));//edge结构体大小的空间
	e->dest=v2;//dest为邻接点的下标值(理解为（v1）指向v2)	///////	表示链接v1和v2
	e->next=G->arr[v1].adj;//新结点插入单链表的表头	////////表示链接e和v1
	G->arr[v1].adj=e;//头指针指向新的单链表表头	//这里没有next了
	G->numofedges++;
}

//创建图(邻接链表)
void creat_graph_link(GraphOfList *G,int ver_arrs[],int ver_count,rowcolweight edge[],int edge_count){
	int i,k;
	init_link(G);	//初始化

	for(i=0;i<ver_count;i++)
		arr_insertver_link(G,i,ver_arrs[i]);	//插入顶点

	for(k=0;k<edge_count;k++)
		arr_insertedge_link(G,edge[k].row,edge[k].col,edge[k].weight);	//插入边
}

//输出邻接表 
void outputInfoOfList(GraphOfList *G){
	int i;
	//printf("data\tsources\tadj\tdest next\n");
	printf("sources\tadj  dest next\n");
	//printf("G->numofverts=%d\n",G->numofverts);
	for(i=0;i<G->numofverts;i++){
		//printf("%d\t",G->arr[i].data);
		printf("%d\t",G->arr[i].source);
		if( G->arr[i].adj==NULL){//注意，不用next
			printf("^\n");
		}
		else{
			printf("  ");
			while(G->arr[i].adj!=NULL){//注意，不用next
				printf("--> ");
				printf("%d  ",G->arr[i].adj->dest);
				G->arr[i].adj=G->arr[i].adj->next;
			}
			printf("\n");
		}
	}
}









/*车位结构信息输出（图片）*/
int outputCarportOfPic(){
	//展示一张图片（车位结构图）
	int width=0,height=0;
	IMAGE carportImg;
	loadimage(&carportImg,_T("C:\\Users\\w1396\\Desktop\\carport.jpg"));//绝对路径+图片名
	width=carportImg.getwidth();
	height=carportImg.getheight();
	initgraph(width,height);
	BeginBatchDraw();
	putimage(0,0,&carportImg);
	EndBatchDraw();
	system("pause");
	closegraph();//close
	return 1;//利用返回值，使在关闭图片后不自动退出系统，而是回到主菜单
}





/*********************************空车位查询（使用邻接矩阵）*************************************/
/*****************1.根据车位号id查询      2.查询车库所有空车位情况（数组）**************************/
/**********************************************************************************************/

///////////////////1.根据用户指定车位号id查询//////////////////////////////////////
void searchNullPortOfselectId(int selectId){//selectId从0开始，对应顶点1（保持对应，selectId-1）
	if(selectId>versize-1){
		printf("车库无该车位\n");
		return ;
	}
	
	if(allCarInfo[selectId-1].carport_isFree==0){
		printf("车位%d空闲\n",selectId);
	}
	else{
		printf("该车位已有车辆\n");
		printf("该车位的车辆信息为：\n");
		printf("车牌号：%s\n",allCarInfo[selectId-1].car_id);
		printf("车辆颜色：%s\n",allCarInfo[selectId-1].car_color);
	}

}

///////////////////2.查询车库所有空车位情况（数组）//////////////////////////////////////
void searchNullPortOfAll(){
	int index=0;
	char nullport[500];
	for(index=0;index<versize-1;index++){
		if(allCarInfo[index].carport_isFree==0){//空闲
			nullport[index]=index;//从0开始
		}
		else
			nullport[index]=-1;
	}
	printf("正在查询中...\n");
	printf("查询成功,空闲车位如下：\n");
	for(index=0;index<versize;index++){//从1号车位开始
		if(nullport[index]>0)//有被赋值，即空闲车位
			printf("%d  ",index+1);//此时index==nullport[index]	//+1
	}
	printf("\n");
}








/*商场入口查询*/
//调用“最优路线综合查询”，找到车主一会要去停车的车位的车位号，根据该车位号去查询对应的商场入口距离
/*
	int carport_id;//车位号(顶点号)
	double entry_distance;//离商场入口距离
	int carport_isFree;
*/
double searchMarketEntry(GraphOfMatrix *G,int ver_arrs[200]){
	char *free="NULL";
	int carportId=0;
	printf("根据车位号查询，请输入车位号：");
	scanf("%d",&carportId);
	int wantCarportId=carportId-1;//最优路线查询，该函数返回车位id（顶点号）
	printf("该车位的情况为：\n");
	//printf("车位号wantCarportId：%d\n",wantCarportId);//wantCarportId返回的值是从0计数，车位号2时wantCarportId=1
	printf("车位号：%d\n",allCarInfo[wantCarportId].carport_id);//结构体变量carport_id返回的值就是车位号
	printf("该车位距最近商场入口的距离为：%.2f m\n",allCarInfo[wantCarportId].entry_distance);
	if(allCarInfo[wantCarportId].carport_isFree==0) free="isfree";
	else free="notisfree";
	printf("该车位空闲情况：%s\n",free);
	return 0;
}


/*相邻车位查询*/
//currentCarPortId:当前车位号（顶点号）
void searchNextPort(GraphOfMatrix *G,int currentCarPortId){
	int *vers;
	int i=0;
	char *free="NULL";
	vers=(int*)malloc(sizeof(int)*2);
	//取第一个邻接顶点(考虑“上一个车位”/"下一个车位")
	vers=GetFirstVex(G,currentCarPortId);
	//printf("****versize=%d***\n",versize);//versize==19
	for(i=0;i<2;i++){
		if((currentCarPortId==1) || (currentCarPortId==versize-1)){//优先级问题
			printf("相邻的车位号为：%d\n",vers[0]);

			if(allCarInfo[vers[0]].carport_isFree==0) free="isfree";
			else free="notisfree";
			printf("车位 %d 的空闲情况是：%s\n",vers[0],free);

			printf("车位 %d 与当前车位的距离是：%d m\n",vers[0],G->edge[currentCarPortId][vers[0]]);
			printf("\n");
			break;
		}
		printf("第 %d 个相邻的车位号为：%d\n",i+1,vers[i]);

		if(allCarInfo[vers[i]].carport_isFree==0) free="isfree";
		else free="notisfree";
		printf("车位 %d 的空闲情况是：%s\n",vers[i],free);

		printf("车位 %d 与当前车位的距离是：%d m\n",vers[i],G->edge[currentCarPortId][vers[i]]);
		printf("\n");
	}

}


//DFS算法
void DFS(GraphOfMatrix *G,int vex,int flag[]){//ver为初始顶点，flag[]标记是否已访问
	int midvex;
	printf("%d ",vex);
	flag[vex]=1;
	midvex=GetFirstVexWithOne(G,vex);//取第一个邻接顶点
	while(midvex!=-1){
		if(!flag[midvex])//没有被访问
		{
			DFS(G,midvex,flag);//将取到的“第一个邻接顶点”作为新的初始顶点
		}

		/*回溯：回溯到当前顶点的上一个顶点vex找vex的下一个顶点(除了midvex的顶点)，走其他线路遍历*/
		midvex=GetNextVex(G,vex,midvex);//这里的vex每次在递归调用时都被更新了
	}
	/*

	相当于这种情况
				   --> E
	   --> B -> D --  
	A--			   -->F
	   --> C
	
	相当于：
	D:	vex 
	E:	midvex
	F:	下一个邻接顶点

	*/



}
/*********************************车位最优路线综合查询*************************************/
/*****************1.根据当前位置离车位距离  2.根据目标车位离商场入口距离*********************/
/**************************************************************************************/

//1. 根据当前位置离车位距离
//DFS-----（测试结果：使用DFS在这个实际应用中体现不出优势，反而更麻烦）
//所以采用普通循环的方式，仍保留DFS参数的接口，便于后期维护
int searchBestRoad(GraphOfMatrix *G,int ver_arrs[200]){//最优路线查询，该函数返回车位id（顶点号）
	//int flag[200]={0};
	//DFS(G,ver_arrs[0],flag);
	int i=0;
	int free=-1;
	//allEageWeights[i]=edge[i].weight
	for(i=0;i<versize;i++){//把i限制在顶点数里面，减少allEageWeights的遍历次数
		
		if(allCarInfo[i].carport_isFree==0) free=0;//空闲
		else free=1;
	
		if(!free){
			printf("当前车位号是%d，它的状态为“空闲”\n",i+1);
			printf("您当前离该车位的距离是%d m\n",allEageWeights[i]);
			printf("目标车位离最近商场入口距离是%.2lf m\n",allCarInfo[i].entry_distance);
			return i;
		}
	}
	printf("抱歉，车库车位已满，没有找到空闲车位\n");
	return -1;//1代表顶点“2”（除去0号车位外，再从0开始算起）
}


//2.找到离商场入口最近的车位，如果那个车位有车
int searchBestRoadOfEnter(){
	int i,free=-1,minDistance=1,minCarport=-1,j;
	minDistance=allCarInfo[0].entry_distance;
	for(i=0;i<versize;i++){//把i限制在顶点数里面，减少allEageWeights的遍历次数
		//allCarInfo[0]存的是顶点1
		if(allCarInfo[i].carport_isFree==0) free=0;//空闲
		else free=1;

		if(allCarInfo[i].entry_distance < minDistance){
			minDistance=allCarInfo[i].entry_distance;
			minCarport=allCarInfo[i].carport_id;
		}
	}

	if(!allCarInfo[minCarport].carport_isFree){	//minCarport空闲
			printf("直接找到\n");
			printf("已为您寻找到距离商场入口最近的车位\n");
			printf("当前车位号是%d，它的状态为“空闲”\n",minCarport);
			printf("您当前离该车位的距离是%d m\n",allEageWeights[minCarport]);
			printf("目标车位离最近商场入口距离是%.2lf m\n",minDistance);
			return minCarport;
	}
	else{	//寻找相邻车位(利用系统遍历车位的特点（从近向远遍历），所以这里直接往minCarport后面的车位遍历)
		printf("寻找相邻车位\n");
		for(j=minCarport+1;j<versize;j++){
			if(!allCarInfo[j].carport_isFree){//minCarport空闲

				printf("已为您寻找到距离商场入口最近的车位\n");
				printf("当前车位号是%d，它的状态为“空闲”\n",j+1);
				printf("您当前离该车位的距离是%d m\n",allEageWeights[j]);
				printf("目标车位离最近商场入口距离是%.2lf m\n",allCarInfo[j].entry_distance);
				return j;
			}
		}		
	}
	printf("抱歉，车库车位已满，没有找到空闲车位\n");
	return -1;

}






/*输出车库所有车位相关信息*/
void outputCarportInfo(){//参数：Carportgraph *G
	int index;
	printf("车库所有车位的相关信息如下：\n");
	printf("车位号\t距离商场   是否空闲    车牌号   车辆颜色\n");
	for(index=0;index<versize-1;index++){
		printf("%d\t%.2lf m\t\t%d\t%s\t%s\n",allCarInfo[index].carport_id,allCarInfo[index].entry_distance,allCarInfo[index].carport_isFree,allCarInfo[index].car_id,allCarInfo[index].car_color);
		
	}
}




/*1.文件输入和输出-----------------------读入车位结构关系*/
//ver_arrs[200] 车位个数（顶点数）
//ver_count为实际顶点个数;edge_count为边条数
int readCartport(GraphOfMatrix *Gr,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count){
	FILE *fp;
	int index=0;
	if((fp=fopen("CarPark.txt","r"))==NULL){
		printf("打开文件出错\n");
		exit(0);
	}
	printf("定位到文件CarPark.txt，正在读取...\n");
	//printf("文件中的内容如下：\n");
	/*
0,1,1:0
0,2,2:0
0,3,3:0
0,4,4:0
0,5,5:0
0,6,6:0
0,7,7:0
0,8,8:0
0,9,9:0
0,10,10:0
0,11,11:0
0,12,12:0
0,13,13:0
0,14,14:0
0,15,15:0
0,16,16:0
0,17,17:0
0,18,18:0
1,2,1:1
2,1,1:2
2,3,1:2
3,2,1:3
3,4,1:3
4,3,1:4
4,5,1:4
5,4,1:5
5,6,1:5
6,5,1:6
6,7,1:6
7,6,1:7
7,8,1:7
8,7,1:8
8,9,1:8
9,8,1:9
9,10,1:9
10,9,1:10
10,11,1:10
11,10,1:11
11,12,1:11
12,11,1:12
12,13,1:12
13,12,1:13
13,14,1:13
14,13,1:14
14,15,1:14
15,14,1:15
15,16,1:15
16,15,1:16
16,17,1:16
17,16,1:17
17,18,1:17
18,17,1:18


*/
	while(!feof(fp)){
		/*注意：从文件读出信息要加 & */
		fscanf(fp,"%d,%d,%d:%d\n",&edge[index].row,&edge[index].col,&edge[index].weight,&ver_arrs[index]);
		//printf("index=%d : %d,%d,%d",index,edge[index].row,edge[index].col,edge[index].weight);
		//printf("\nver_arrs[%d]=%d\n\n",index,ver_arrs[index]);
		allEageWeights[index]=edge[index].weight;
		index++;
	}
	printf("读取文件成功\n");
	fclose(fp);

	//创建图
	creat_graph(Gr,ver_arrs,ver_count,edge,edge_count);
	creat_graph_link(Glist,ver_arrs,ver_count,edge,edge_count);
	return 0;
}




/*
CarInfo.txt
1,3,0,NULL NULL
2,2,0,NULL NULL
3,1,0,NULL NULL
4,1,0,NULL NULL
5,2,0,NULL NULL
6,3,0,NULL NULL
7,3,0,NULL NULL
8,2,0,NULL NULL
9,1,0,NULL NULL
10,1,0,NULL NULL
11,2,0,NULL NULL
12,3,0,NULL NULL
13,3,0,NULL NULL
14,2,0,NULL NULL
15,1,0,NULL NULL
16,1,0,NULL NULL
17,2,0,NULL NULL
18,3,0,NULL NULL
*/
/*2.文件输入和输出-----------------------读入车位信息（）*/
/*
结构体对象：CarportInfo
int carport_id		车位号（顶点号）
double entry_distance		车位离商场距离
int carport_isFree		车辆空闲情况(空闲为0)
char car_id[20]		车牌号
char car_color[20]	颜色
*/
//初始所有车位均空闲，有车出入后要保存新的车位信息到文件中（更新/重置）
int readCarInfo(){
	FILE *fp2;
	//CarportInfo allCarInfo[500];应该设置成全局变量更好
	int index=0;
	if((fp2=fopen("CarInfo.txt","r"))==NULL){
		printf("读取文件CarInfo失败\n");
		exit(0);
	}
	printf("定位到文件CarInfo.txt，正在读取...\n");
	printf("文件中的内容如下：\n");
	printf("车位号\t距离商场   是否空闲    车牌号   车辆颜色\n");

	while(!feof(fp2)){
		//注意：entry_distance是double型，%lf写成%d会造成下一个属性信息carport_isFree读取错误
		/*因为是字符串类型，系统可能将换行也识别成字符串的一部分，所以测试结果是只读了第一行然后就一直“烫...”,
		  将最后一个字符串加个 字符 作为结束符-----------------！！！这个方法也不行！！！*/
		/*还有一个问题：
		  1,3,0,NULL,NULL  比如这样写在一起，它把逗号也识别成了第一个char[]的字符串值，所以忽略了最后一个字符串
		  的读取，造成最后一个 %s 无法读取，所以就“烫...”*/

		/*
		最终解决方案：
			写成 1,3,0,NULL NULL 这种形式就行了（用空格分割两个字符串），注意最后普通换行即可，不用加空格什么的
		*/
		fscanf(fp2,"%d,%lf,%d,%s %s\n",&allCarInfo[index].carport_id,&allCarInfo[index].entry_distance,&allCarInfo[index].carport_isFree,allCarInfo[index].car_id,allCarInfo[index].car_color);//记得取址符 & (注意：后面两个char类型不用 & )
		//printf("allCarInfo[index].carport_isFree=%d\n",allCarInfo[index].carport_isFree);
		//printf("读取文件成功\n");
		printf("%d\t%.2lf m\t\t%d\t%s\t%s\n",allCarInfo[index].carport_id,allCarInfo[index].entry_distance,allCarInfo[index].carport_isFree,allCarInfo[index].car_id,allCarInfo[index].car_color);
		index++;
	}
	printf("读取文件成功\n");
	fclose(fp2);
	return 0;
}




/********************************************************/
/*****1.停车、2.取车函数、3.修改信息后的属性写入文件********/
/********************************************************/
/*
结构体对象：CarportInfo
int carport_id		车位号（顶点号）
double entry_distance		车位离商场距离
int carport_isFree		车辆空闲情况(空闲为0)
char car_id[20]		车牌号
char car_color[20]	颜色
*/

///////////////1.停车/////////////
/*
参数：
wantCarportId:传入想要停车的车位号（顶点号）
carId[20]:车牌号
carColor[20]:车辆颜色
*/
//在里面调用 更新保存文件函数lastestCarPortInfoFile()
void addCar(GraphOfMatrix *G,char carId[20],char carColor[20],int ver_arrs[200]){
	int op=-1;
	int wantCarportId=-1;
	printf("\n请输入优先以哪种形式匹配车位：");
	while(op!=0){
		MenuOfSearchBest();
		scanf("%d",&op);
		if(op==1){
			wantCarportId=searchBestRoad(G,ver_arrs);
			break;
		}//最优路线查询，该函数返回车位id（顶点号）
		else if(op==2){
			wantCarportId=searchBestRoadOfEnter();
			break;
		}
		else{
			printf("请重新输入\n");
			scanf("%d",&op);
		}
	}
	if(wantCarportId==-1) return ;
	//printf("\n\naddCar()测试\n");
	//printf("%d,%.2lf,%d,%s,%s\n",allCarInfo[0].carport_id,allCarInfo[0].entry_distance,allCarInfo[0].carport_isFree,allCarInfo[0].car_id,allCarInfo[0].car_color);
	allCarInfo[wantCarportId].carport_isFree=1;//停车，置为1，代表车位不空闲
	/*字符串拷贝*/
	strcpy(allCarInfo[wantCarportId].car_id,carId);
	strcpy(allCarInfo[wantCarportId].car_color,carColor);
	//更新文件（将车辆信息保存）-----------停车，所以deleteCarportId参数置0
	lastestCarPortInfoFile(wantCarportId,allCarInfo[wantCarportId].car_id,allCarInfo[wantCarportId].car_color,0);
	printf("已锁定车位，请您前往指定车位停车\n");
}


///////////////2.取车/////////////
/*
参数：
deleteCarportId:传入想要取车的车位号（顶点号）
*/
//在里面调用 更新保存文件函数lastestCarPortInfoFile()
void deleteCar(int deleteCarportId){
	if(allCarInfo[deleteCarportId-1].carport_isFree==0){
		printf("您输入的车位无车辆，请重新输入\n");
		return ;
	}
	allCarInfo[deleteCarportId-1].carport_isFree=0;//取车，将车位置为空闲
	/*字符串拷贝*/
	strcpy(allCarInfo[deleteCarportId-1].car_id,"NULL");//置为NULL，与初始值一样
	strcpy(allCarInfo[deleteCarportId-1].car_color,"NULL");
	//更新文件（将车辆信息保存）-----------取车，所以wantCarportId参数置0
	lastestCarPortInfoFile(0,allCarInfo[deleteCarportId-1].car_id,allCarInfo[deleteCarportId-1].car_color,deleteCarportId);
	printf("取车成功\n");
}


/////////////3.将停车/取车后的属性写入文件(只更新对应顶点相关的3个属性)/////////////
/*
carport_isFree:是否空闲
carId[20]:车牌号
carColor[20]:车辆颜色
*/
//sk：调用时传递默认参数给wantCarportId或deleteCarportId，以此区别是add还是delete
void lastestCarPortInfoFile(int wantCarportId,char carId[20],char carColor[20],int deleteCarportId){
	FILE *fp3;
	int index=0;
	if((fp3=fopen("CarInfo.txt","w"))==NULL){
		printf("打开文件失败\n");
		exit(0);
	}
	//printf("文件打开成功，正在执行写入操作...\n");

	/*刚开始测试“只写入一次（一行），不用while(!feof(fp3))”
	----------测试后发现，出错，
	--------只写入一行会将更新的那行数据直接覆盖整个文件，而不是更新原文件中某行的值
	--------应该采用整个文件内容重置的方法比较好，虽然比较繁杂
	*/

	//allCarInfo[]是全局变量，add和delete之后的新值都在里面了
		
		//add
		if(wantCarportId!=0 && deleteCarportId==0){//这两个参数只是来区分是add函数还是delete函数，无实际意义
			/*注意：写文件的结束符不能用eof，因为是不会结束的*/
			//while(!feof(fp3)){
			for(index=0;index<versize-1;index++){//-1是减去0号车位
				/*
				不能这样使用，这样就死循环，一直在更新wantCarportId行
				fprintf(fp3,"%d,%.2lf,%d,%s %s\n",allCarInfo[wantCarportId].carport_id,allCarInfo[wantCarportId].entry_distance,allCarInfo[wantCarportId].carport_isFree,allCarInfo[wantCarportId].car_id,allCarInfo[wantCarportId].car_color);
				*/

				//因为是更新（重写）整个文件，所以是从头开始，index=0开始
				fprintf(fp3,"%d,%lf,%d,%s %s\n",allCarInfo[index].carport_id,allCarInfo[index].entry_distance,allCarInfo[index].carport_isFree,allCarInfo[index].car_id,allCarInfo[index].car_color);
				//printf();
				
			}
		//	}
		}
		
		//delete
		if(wantCarportId==0 && deleteCarportId!=0){
			/*注意：写文件的结束符不能用eof，因为是不会结束的*/
			//while(!feof(fp3)){
			for(index=0;index<versize-1;index++){//-1是减去0号车位
				/*
				同上，不能这样使用，这样就死循环，一直在更新deleteCarportId行
				fprintf(fp3,"%d,%.2lf,%d,%s %s\n",allCarInfo[deleteCarportId].carport_id,allCarInfo[deleteCarportId].entry_distance,allCarInfo[deleteCarportId].carport_isFree,allCarInfo[deleteCarportId].car_id,allCarInfo[deleteCarportId].car_color);
				*/
				fprintf(fp3,"%d,%.2lf,%d,%s %s\n",allCarInfo[index].carport_id,allCarInfo[index].entry_distance,allCarInfo[index].carport_isFree,allCarInfo[index].car_id,allCarInfo[index].car_color);
			
			//printf();
				
			}
			//}
		}
		printf("文件写入成功,车库信息已更新\n");
		fclose(fp3);
}













/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


/*图形化用户界面*/



/*主菜单*/
void menu_main(){
	printf("\n*****************************欢迎使用停车场路线规划系统************************\n");
	printf("***  1.从文件读取停车场车位信息          2.停车场车位信息结构图             ***\n");
	printf("***  3.车位情况查询                      4. 我要停车(最优路线一键查询)      ***\n");
	printf("***  5. 我要取车                         6.车位结构图片                     ***\n");
	printf("***  7. 退出系统                                                            ***\n");
	printf("*******************************************************************************\n");
}

void MenuOfSearchBest(){
	printf("\n*****************************车位最优路线综合查询*****************************\n");
	printf("***  1.根据当前位置离车位距离               2.根据目标车位离商场入口距离   ***\n");
	printf("******************************************************************************\n");
}

void Menucarinfo(){
	printf("*****************************停车场车位信息结构图*******************************\n");
	printf("***  1.邻接矩阵形式输出                        2. 邻接链表形式输出          ***\n");
	printf("***  3. 返回上一层 			       4.退出系统      	            ***\n");
	printf("*******************************************************************************\n");

}


void Menucarsituation(){
	printf("*****************************车位情况查询**************************************\n");
	printf("***  1.输出车库所有车位的相关信息                        2. 空车位查询      ***\n");
	printf("***  3. 商场入口查询				         4.相邻车位查询     ***\n");
	printf("***  5.返回上一层 				         6.退出系统         ***\n");
	printf("*******************************************************************************\n");

}

void Menunullport(){
	printf("\n*****************************空车位查询****************************************\n");
	printf("***  1.根据指定车位号查询                     2.查询车库所有空车位情况      ***\n");
	printf("***  3. 返回上一层 			      4.退出系统    	            ***\n");
	printf("*******************************************************************************\n");
}


void nullPortSelectMenu(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count){
	int op=0;
	int selectId;

	Menunullport();
	
	while(op!=6){
		printf("请根据菜单提示输入选项：");
		scanf("%d",&op);
		switch(op){
			case 1:	//根据指定车位号查询
				printf("请输入想要查询的车位号\n");
				scanf("%d",&selectId);
				searchNullPortOfselectId(selectId);
				printf("\n");
				Menunullport();
				break;
			case 2:	//查询车库所有空车位情况
				searchNullPortOfAll();
				printf("\n");
				Menunullport();
				break;
			case 3:	//返回上一层
				printf("\n");
				interface_call(G,Glist,edge,ver_arrs,ver_count,edge_count);break;
			case 4:	//退出系统
				printf("欢迎再次使用该系统，再见\n");
				exit(0);
			default:
				printf("输出错误，请重试\n");
				scanf("%d",&op);
				break;
		}
	}


}

/*车位信息结构图 菜单*/
void menu_carinfo(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count){
	
	int op=0;
	Menucarinfo();//界面

	while(op!=6){
		printf("请根据菜单提示输入选项：");
		scanf("%d",&op);
		switch(op){
			case 1:	//邻接矩阵输出
				outputInfoOfMatrix(G,versize);
				printf("\n");
				Menucarinfo();
				break;
			case 2:	//邻接链表输出
				outputInfoOfList(Glist);
				printf("\n");
				Menucarinfo();
				break;
			case 3:	//返回上一层
				printf("\n");
				interface_call(G,Glist,edge,ver_arrs,ver_count,edge_count);break;
			case 4:	//退出系统
				printf("欢迎再次使用该系统，再见\n");
				exit(0);
			default:
				printf("输出错误，请重试\n");
				scanf("%d",&op);
				break;
		}
	}
}

/*车位情况查询 菜单*/
void menu_carsituation(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count){
	int op=0;
	int selectId;
	int currentCarPortId;


	Menucarsituation();
	
	while(op!=6){
		printf("请根据菜单提示输入选项：");
		scanf("%d",&op);
		switch(op){
			case 1:	//输出车库所有车位的相关信息
				outputCarportInfo();
				printf("\n");
				Menucarsituation();
				break;
			case 2:	//空车位查询
				nullPortSelectMenu(G,Glist,edge,ver_arrs,ver_count,edge_count);
				break;
			case 3:	//商场入口查询
				searchMarketEntry(G,ver_arrs);
				printf("\n");
				Menucarsituation();
				break;
			case 4:	//相邻车位查询
				printf("请输入当前车位号：");
				scanf("%d",&currentCarPortId);
				searchNextPort(G,currentCarPortId);
				Menucarsituation();
				break;
			case 5:	//返回上一层
				printf("\n");
				interface_call(G,Glist,edge,ver_arrs,ver_count,edge_count);break;
			case 6:	//退出系统
				printf("欢迎再次使用该系统，再见\n");
				exit(0);
			default:
				printf("输出错误，请重试\n");
				scanf("%d",&op);
				break;
		}
	}

}


/*菜单选项调用*/
void interface_call(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count){
	int op=0;//选项
	int deletecarid=0;
	char carId[20];//车牌号
	char carColor[20];//车辆颜色
	int test=-1;
	menu_main();
	
	
	while(op!=6){
		printf("请根据菜单提示输入选项：");
		scanf("%d",&op);
		switch(op){
			case 1:	//从文件中读取车位信息(结构信息+车位车辆信息)（读取两个文件）
				readCartport(G,Glist,edge,ver_arrs,ver_count,edge_count);
				readCarInfo();
				printf("\n");
				menu_main();
				break;
			case 2:	//调用停车场车位信息结构图菜单
				menu_carinfo(G,Glist,edge,ver_arrs,ver_count,edge_count);break;
			case 3:	//调用车位情况查询菜单
				menu_carsituation(G,Glist,edge,ver_arrs,ver_count,edge_count);break;
			case 4:	//我要停车(最优路线一键查询)
				printf("请输入您的车牌号、车辆颜色:");
				scanf("%s%s",carId,carColor);
				addCar(G,carId,carColor,ver_arrs);
				menu_main();
				//searchBestRoad();在addCar()里面调用最优路线查询（将查询到的顶点号传给addCar()）
				break;
			case 5:	//我要取车
				printf("请输入您停车的车位号：");
				scanf("%d",&deletecarid);
				deleteCar(deletecarid);
				printf("\n");
				menu_main();
				break;

			case 6:	//车位结构图片
				test=outputCarportOfPic();
				if(test=1) interface_call(G,Glist,edge,ver_arrs,ver_count,edge_count);
				break;
			case 7:	//退出系统
				printf("欢迎再次使用该系统，再见\n");
				exit(0);
			default:
				printf("输出错误，请重试\n");
				scanf("%d",&op);
				break;
		}
	}

}