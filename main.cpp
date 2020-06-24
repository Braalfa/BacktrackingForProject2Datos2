#include <iostream>
using namespace std;



template <size_t r, size_t c>
void mark(int xi, int yi, int (&map)[r][c], int mark, int step){
    int tmp;
    for (int i=-1;i<2;i++){
        if(xi+i<r && xi+i>-1){
            for(int j=-1;j<2;j++){
                tmp= map[xi+i][yi+j];
                if(yi+j<c && yi+j>-1 && (tmp==0 || tmp==step)){
                    map[xi+i][yi+j]=mark;
                }
            }
        }
    }
}
/**
 *
 * @param xi Current x
 * @param yi Current y
 * @param lsi Last x step taken (-1,0,1)
 * @param lsj Last y step taken (-1,0,1)
 * @param xf Final x (goal)
 * @param yf Final y (goal)
 * @param map
 * @param done Boolean pointer that indicates if the goal has been reached
 * @return
 */

// create a function template
template <size_t r, size_t c>
void backtracking2(int xi, int yi, int xf, int yf, int step,int (&map)[r][c], bool* done)
{

    //If object is on goal, exists
    if (xi==xf && yi==yf) {
        *done = true;
        map[xi][yi]=2;
        return;
    } else if(map[xi][yi]==1){
        return;
    }else{
        //Object tries every possible path
        mark(xi, yi, map, step, step);
        for (int i=-1;i<2;i++)
        {
            if(xi+i<r && xi+i>-1){
               for(int j=-1;j<2;j++){
                    if((i!=0 || j!=0)&&(yi+j<c && yi+j>-1)&&map[xi+i][yi+j]==step){
                        backtracking2(xi+i, yi+j, xf, yf, step+1,map, done);
                        if(*done){
                            mark(xi, yi, map, 0, step);
                            map[xi][yi]=2;
                            return;
                        }
                    }
                }
            }
        }
        mark(xi, yi, map, 0, step);
    }
}


void backtracking()
{
    int map[10][10]={{0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,1,1,1,1,0},
                     {0,0,1,0,1,1,0,0,0,0},
                     {0,0,1,0,1,0,0,0,0,0},
                     {0,0,1,0,1,0,0,0,0,0},
                     {0,0,1,0,1,1,1,0,0,0},
                     {0,0,1,0,0,0,1,0,0,0},
                     {0,0,1,1,1,1,1,0,0,0}};
    bool* done = new bool(false) ;
    backtracking2(0, 5, 8, 5,3, map, done);

    for(int i =0;i<10;i++){
        for(int j =0;j<10;j++){
            cout<<std::to_string(map[i][j])+" ";
        }
        cout<<""<<endl;
    }
}



int main() {
    backtracking();
    return 0;
}