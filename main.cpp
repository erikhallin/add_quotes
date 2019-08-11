#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;

int main()
{
    cout<<"START\n";

    DIR *dirp;
    struct dirent *dp;

    //open dir
    if((dirp = opendir(".")) == NULL)
    {
        cout<<"ERROR: Could not open current directory\n";
        return 1;
    }

    //read dir
    do
    {
        if( (dp=readdir(dirp)) != NULL )
        {
            //cout<<dp->d_name<<endl;
            string file_name(dp->d_name);

            //find dot
            for(int i=0;i<(int)file_name.size();i++)
            {
                if(file_name[i]=='.')
                {
                    //cout<<"DOT\n";
                    bool read_this_file=false;
                    //test .txt
                    if(i==(int)file_name.size()-4)
                    {
                        //cout<<"SIZE\n";
                        if(file_name[i+1]=='t' && file_name[i+2]=='x' && file_name[i+3]=='t')
                        {
                            read_this_file=true;
                            //cout<<".txt\n";

                            //cancel read if starts with new_
                            if( file_name[0]=='n' && file_name[1]=='e' && file_name[2]=='w' && file_name[3]=='_' )
                            {
                                read_this_file=false;
                            }
                        }

                    }

                    //read number of \n
                    if(read_this_file)
                    {


                        //cout<<"read\n";
                        ifstream file_in(dp->d_name);
                        if(file_in==0)
                        {
                            cout<<"ERROR: Could not read the file: "<<dp->d_name<<endl;
                            return 1;
                        }
                        string new_file_name("new_");
                        new_file_name.append(dp->d_name);

                        ofstream file_out(new_file_name.c_str());
                        if(file_out==0)
                        {
                            cout<<"ERROR: Could not read the file: "<<new_file_name<<endl;
                            return 1;
                        }

                        string line;
                        while(getline(file_in,line))
                        {
                            file_out<<"\""<<line<<"\\n\""<<endl;
                        }

                        file_in.close();
                        file_out.close();
                    }
                }
            }
        }
    }
    while(dp != NULL);

    //done
    closedir(dirp);

    cout<<"COMPLETE\n";

    return 0;
}
