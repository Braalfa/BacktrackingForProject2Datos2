#include <iostream>

int main() {
    return 0;
}

void backtracking()
{

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
bool backtracking2(int xi, int yi, int lsi=0, int lsj =0,  int xf, int yf, int map[][], bool* done)
{

    //If object is on goal, exists
    if (xi==xf && yi==yf)
    {
        *done=true;
        return;
    }else{
        t=int;
        //Object tries every possible path
        for (i=-1;i<2;i++)
        {
            for(j=-1;j<2;j++){
                if((i!=0 || j!=0)&&(i!=-1*lsi || j!=-1*lsj)){
                    backtracking2(xi+i, yi+j, xi, j, i, yf, map);
                    if(*done){
                        return;
                    }
                }
            }
        }
    }
}