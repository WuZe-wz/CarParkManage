/*主函数*/


#include"implementation.h"
//#include"G_Interface.h"

int main(){
	GraphOfMatrix Gr;
	//GraphOfMatrix G;
	GraphOfList Glist;
	/*设置ver_count,edge_count是因为一个停车场的车位数和位置相对固定，一般不会出现临时增减车位数的情况*/
	int i,j,ver_count=19,edge_count=52;//ver_count为实际顶点个数;edge_count为边条数(18个顶点，52条边)
	//int ver_arrs[MAXVERTICES];//MAXVERTICES为图的最大顶点个数
	//rowcolweight edge[]={{0,1,10},{0,2,6},{0,3,15},{1,4,7},{2,4,12},{2,5,7},{3,6,16},{4,7,9},{5,6,3},{6,7,6}};//8个顶点，10条边
	rowcolweight edge[200];
	//int ver_arrs[]={1,2,3,4,5,6,7,8};//8个顶点
	int ver_arrs[200];
	char user_name[50];
	char password[50];
	int flag=0;
	//int readCartport(GraphOfMatrix *Gr,GraphOfList *Glist,rowcolweight edge[200],int ver_arrs[200],int ver_count,int edge_count)
	//readCartport(&Gr,&Glist,edge,ver_arrs,ver_count,edge_count);
	//////////////////////////////
	//邻接矩阵
	/////////////////////////////

	
	//创建图
	//init(&Gr,ver_count);
	//creat_graph(&Gr,ver_arrs,ver_count,edge,edge_count);
	//creat_graph_link(&Glist,ver_arrs,ver_count,edge,edge_count);//List
	//printf("main函数执行 outputInfoOfMatrix(&Gr) 函数\n");
	//outputInfoOfMatrix(&Gr,versize);
	//printf("\n\n");
	//readCarInfo();
	//addCar(carId,carColor);//测试





	printf("欢迎使用停车场路线规划系统\n");
	printf("请输入用户名:");
	scanf("%s",user_name);
	printf("请输入密码:");
	scanf("%s",password);
	while(!flag){
		if((!strcmp(user_name,"cars")) && (!strcmp(password,"123456"))){//字符串相同返回0
			interface_call(&Gr,&Glist,edge,ver_arrs,ver_count,edge_count);
			flag=1;
			break;
		}
		else{
			printf("用户名或密码输入错误,请重新输入\n");
			printf("请输入用户名:");
			scanf("%s",user_name);
			printf("请输入密码:");
			scanf("%s",password);
		}
	}

	
	
	return 0;
}