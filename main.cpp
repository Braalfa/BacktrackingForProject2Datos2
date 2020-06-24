#include <iostream>
#include <limits>
using namespace std;


/**
 * This function marks the neighborhood of (xi,yi) with mark, as long as it hasnt been marked
 * by previous steps
 * @tparam r Map rows
 * @tparam c Map columns
 * @param xi X position
 * @param yi Y position
 * @param map Map
 * @param mark New mark
 * @param step Step creating the mark
 */
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
 * @param xf Final x (goal)
 * @param yf Final y (goal)
 * @param step Number of current call to backtracking
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
        //The possible steps from here are marked so that they won't be
        //reached by future calls
        mark(xi, yi, map, step, step);
        //Object tries every possible path
        for (int i=-1;i<2;i++)
        {
            //Checking for border
            if(xi+i<r && xi+i>-1){
               for(int j=-1;j<2;j++){
                   //Checking for border, checking it's not gonna enter walls or previous marks
                    if((yi+j<c && yi+j>-1)&&map[xi+i][yi+j]==step){
                        backtracking2(xi+i, yi+j, xf, yf, step+1,map, done);
                        if(*done){
                            //Unmarks all marks made by this step because of success
                            mark(xi, yi, map, 0, step);
                            //Marks the right path with a 2
                            map[xi][yi]=2;
                            return;
                        }
                    }
                }
            }
        }
        //Unmarks all marks made by this step because it failed
        mark(xi, yi, map, 0, step);
    }
}

//Test function
void backtracking()
{
    //Test Map (1's are walls)
    int map[10][10]={{0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,0,0,1,1,1,1,0},
                     {0,0,1,0,1,1,0,0,0,0},
                     {0,0,1,0,0,1,1,0,0,0},
                     {0,0,1,0,0,0,1,0,0,0},
                     {0,0,1,0,1,0,1,0,0,0},
                     {0,0,1,0,1,0,0,0,0,0},
                     {0,0,1,1,1,1,1,0,0,0}};

    //Calling backtracking
    bool* done = new bool(false) ;
    //Note: Steps starts from 3 because 1 and 2 are taken for walls and final path
    backtracking2(0, 5, 4, 6,3, map, done);


    //Prints final map
    for(int i =0;i<10;i++){
        for(int j =0;j<10;j++){
            cout<<std::to_string(map[i][j])+" ";
        }
        cout<<""<<endl;
    }
}

template <size_t r, size_t c>
int* getClosestTrace(int numOfTraces, int (&map)[r][c]){
    for(int i =0;i<r;i++){
        for(int j =0;j<c;j++){
            if(map[i][j]==numOfTraces/2){

            }
        }
    }
}

template <size_t r, size_t c>
void breadcumbing(int xi, int yi, int (&map)[r][c]){
    int nextTrace=std::numeric_limits<int>::max();
    int nx;
    int ny;
    if(map[xi][yi]!=0){
        for (int i=-1;i<2;i++){
            if(xi+i<r && xi+i>-1){
                for(int j=-1;j<2;j++){
                    if(yi+j<c && yi+j>-1 ){
                        if(map[xi+i][yi+j]<nextTrace){
                            nextTrace=map[xi+i][yi+j];
                            nx=xi+i;
                            ny=yi+j;
                        }
                    }
                }
            }
        }
        //Move or something
        breadcumbing( nx, ny, map);
    }
}


int main() {
    backtracking();
    return 0;
}