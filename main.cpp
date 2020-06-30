#include <iostream>
#include <limits>
#include "TList.h"
#include "math.h"
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

double f(int xi, int yi, int xf, int yf, int currentSteps){
    return currentSteps+sqrt(pow(xf-xi,2) +pow(yf-yi,2));
}

template <size_t r, size_t c>
int A(int xi, int yi, int xf, int yf, int (&map)[r][c]){
    double min =std::numeric_limits<double>::max();
    double minTemp;

    int xmin;
    int ymin;

    int xtemp;
    int ytemp;

    int indexPos;
    string nodeValue;


    TList paths=*new TList;
    TList open=*new TList;
    TList close=*new TList;
    TList steps=*new TList;

    steps.addLast("0");
    paths.addLast(to_string(xi) + ";" + to_string(yi));
    open.addLast(to_string(xi) + ";" + to_string(yi));

    while(open.largo!=0){
        min =std::numeric_limits<double>::max();
        for(int i=0;i<open.largo;i++){

            nodeValue=open.getNodoPos(i)->getValue();
            indexPos=nodeValue.find_first_of(';');
            xtemp=std::stoi(nodeValue.substr(0,indexPos));
            ytemp=std::stoi(nodeValue.substr(indexPos+1,nodeValue.length()-indexPos));
            minTemp=f(xtemp, ytemp, xf, yf, stoi(steps.getNodoPos(i)->getValue()));

            if(min>minTemp){
                xmin=xtemp;
                ymin=ytemp;
                min=minTemp;
            }
        }

        int parentPos=open.getPos(to_string(xmin)+";"+to_string(ymin));
        open.deletePos(parentPos);
        close.addLast(to_string(xmin)+";"+to_string(ymin));
        map[xmin][ymin]=3;

        if(abs(xmin-xf)<2 &&abs(ymin-yf)<2){
            string path= paths.getNodoPos(parentPos)->getValue()+";";
            /* while (!path.empty()){
                indexPos=path.find_first_of(';');
                xtemp=std::stoi(path.substr(0,indexPos));
                path=path.substr(indexPos+1, path.length()-indexPos);
                indexPos=path.find_first_of(';');
                ytemp=std::stoi(path.substr(0,indexPos));
                path=path.substr(indexPos+1, path.length()-indexPos);
                map[xtemp][ytemp]=2;
            }
             */
            return 0;
        } else{
            string nodeText;
            for (int i=-1;i<2;i++){
                if(xmin+i<r && xmin+i>-1){
                    for(int j=-1;j<2;j++){
                        if(ymin+j<c && ymin+j>-1 ) {
                            if(map[xmin + i][ymin + j] != 1) {
                                nodeText = to_string(xmin + i) + ";" + to_string(ymin + j);
                                if (open.getNodoVal(nodeText) == nullptr
                                    && close.getNodoVal(nodeText) == nullptr) {

                                    map[xmin+i][ymin+j]=2;

                                    open.addLast(nodeText);
                                    paths.addLast(paths.getNodoPos(parentPos)->getValue()
                                                  + ";" + nodeText);
                                    steps.addLast(
                                            to_string(stoi(steps.getNodoPos(parentPos)->getValue())+1));
                                }
                            }
                        }
                    }
                }
            }
            for(int i =0;i<10;i++){
                for(int j =0;j<10;j++){
                    cout<<std::to_string(map[i][j])+" ";
                }
                cout<<""<<endl;
            }
            cout<<""<<endl;
            cout<<""<<endl;

            paths.deletePos(parentPos);
            steps.deletePos(parentPos);
        }
    }
    return-1;
}


int main() {

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
    A(0, 5, 4, 6, map);

    for(int i =0;i<10;i++){
        for(int j =0;j<10;j++){
            cout<<std::to_string(map[i][j])+" ";
        }
        cout<<""<<endl;
    }
    return 0;
}