//#include"seqlist.h"
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#define MAXVERTICES 200//图的顶点最大个数
#define MAXWEIGHT 9999

extern int versize;
//extern CarportInfo allCarInfo[500];//应该设置成全局变量更好（不能写extern，结构体原因？）

//seqlist
#define MAXSIZE 500
typedef struct {
	int list[MAXSIZE];
	int size;
}SeqList;



//车位信息结构体
//车位信息：车位号（顶点号），离商场的距离，车位空闲情况
typedef struct Carport{
	int carport_id;//车位号(顶点号)
	double entry_distance;//离商场入口距离
	int carport_isFree;//车位空闲情况(由于c语言没有bool类型，c++才有，这里用int代替bool用法)
	
	/*如果该停车位上有车,添加这两个属性（如果没车，置为NULL），初始为NULL*/
	char car_id[20];//车牌号
	char car_color[20];//颜色

}CarportInfo;


/*
该结构体合并到“车位信息结构体”（方便处理）

//车辆信息结构体
//车牌号，车身颜色
typedef struct Car{
	char car_id[20];//车牌号
	char car_color[20];//颜色
}CarInfo;

*/


//创建图结构(共用)
typedef struct{
	int row;//行下标
	int col;//列下标
	int weight;//权值
	//int entry_distance;//add--车位距商场入口的距离(ERR:不能在这个结构体设计，因为这个结构体是存储边信息的，
											//而entry_distance是关于点信息的)
}rowcolweight;//创建边信息结构体



////////////////////////
//////邻接矩阵//////////
///////////////////////
typedef struct{
	SeqList ver;//线性表结构体成员，该顺序表用于存放顶点
	int edge[MAXVERTICES][MAXVERTICES];//存放边的邻接矩阵
	int edgecount;//边条数
}GraphOfMatrix;


//初始化（邻接矩阵）
void init(GraphOfMatrix *G,int n);		//删去extern--6.13 22：46


//插入顶点（邻接矩阵）
void arr_insertver(GraphOfMatrix *G,int vertex);



//插入边（邻接矩阵）
void arr_insertedge(GraphOfMatrix *G,int v1,int v2,int weight);


//取第一个邻接顶点(考虑“上一个车位”/"下一个车位")
//1.用于查询相邻车位
int *GetFirstVex(GraphOfMatrix G,int v);
//2.只查询下一个车位，用于DFS遍历
int GetFirstVexWithOne(GraphOfMatrix *G,int v);


//取下一个邻接顶点
int GetNextVex(GraphOfMatrix *G,int v1,int v2);

//创建图	//rowcolweight edge[]为“图的边信息”结构体数组(邻接矩阵)
void creat_graph(GraphOfMatrix *G,int ver_arrs[],int ver_count,rowcolweight edge[],int edge_count);






////////////////////////
//////邻接链表//////////
///////////////////////

typedef struct Node{
	int dest;//邻接边的顶点下标
	int weight;//权值
	struct Node *next;
}edge;//边信息，链表

typedef struct{
	int data;
	int source;//当前顶点对应的下标值
	edge *adj;//邻接边的头指针
}arr_edge;//点信息，数组

typedef struct{
	arr_edge arr[MAXVERTICES];	//图的顶点最大个数 / MAXVERTICES代表存储所有点的数组的个数
	int numofverts;//顶点个数
	int numofedges;//边条数
}GraphOfList;//（总）邻接表结构体-图



//初始化（邻接表）
void init_link(GraphOfList *G);




//插入顶点-在数组操作（邻接表）
void arr_insertver_link(GraphOfList *G,int i,int vertex);




//插入边-在链表操作（邻接表）
void arr_insertedge_link(GraphOfList *G,int v1,int v2,int weight);






//创建图(邻接链表)
void creat_graph_link(GraphOfList *G,int ver_arrs[],int ver_count,rowcolweight edge[],int edge_count);



//输出（邻接矩阵）
void outputInfoOfMatrix(GraphOfMatrix *G,int versize);

//输出（邻接链表）
void outputInfoOfList(GraphOfList *G);
//again















/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////



#include<stdio.h>
#include<stdlib.h>
//#include"implementation.h"//不能再引入，否则会出现结构体类型重定义（错误	10	error C2011: “Node”:“struct”类型重定义）
/*菜单控制*/
void interface_call(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count);				//删去extern--6.13 22：46


/*菜单界面*/
void menu_main();//主菜单
void Menucarinfo();//界面
void menu_carinfo(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count);//车位信息结构图 菜单
void Menucarsituation();
void menu_carsituation(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count);//车位情况查询 菜单
void Menunullport();
void nullPortSelectMenu(GraphOfMatrix *G,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count);//空车位查询菜单
void MenuOfSearchBest();


/*车位结构信息输出*/
int outputCarportOfPic();


/*空车位查询*/
//使用邻接矩阵
void searchNullPortOfselectId(int selectId);//1.根据用户指定车位号id查询
void searchNullPortOfAll();//2.查询车库所有空车位情况（数组）



/*商场入口查询*/
double searchMarketEntry(GraphOfMatrix *G,int ver_arrs[200]);//参数：Carportgraph *G，int j


/*相邻车位查询*/
void searchNextPort(GraphOfMatrix *G,int currentCarPortId);


/*********************************车位最优路线综合查询*************************************/
/*****************1.根据当前位置离车位距离  2.根据目标车位离商场入口距离*********************/
/**************************************************************************************/
//1.根据当前位置离车位距离
int searchBestRoad(GraphOfMatrix *G,int ver_arrs[200]);//最优路线查询，该函数返回车位id（顶点号）
// 2.根据目标车位离商场入口距离
int searchBestRoadOfEnter();



/*输出车库所有车位相关信息*/
void outputCarportInfo();


/*
//车位结构信息输出
void outputInfoOfMatrix();//邻接矩阵输出
void outputInfoOfList();//邻接链表输出
*/






/*文件输入和输出*/
/*1.文件输入和输出-----------------------读入车位结构关系*/
//ver_count为实际顶点个数;edge_count为边条数
int readCartport(GraphOfMatrix *Gr,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count);


/*2.文件输入和输出-----------------------读入车位信息（）*/
int readCarInfo();


/*1.停车、2.取车函数、3.修改信息后的属性写入文件*/
//1.停车
void addCar(GraphOfMatrix *G,char carId[20],char carColor[20],int ver_arrs[200]);

//2.取车
void deleteCar(int deleteCarportId);

//3.将停车/取车后的属性写入文件
void lastestCarPortInfoFile(int wantCarportId,char carId[20],char carColor[20],int deleteCarportId);


