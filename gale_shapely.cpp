#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;

struct Student{
    vector<uint> classement;
    vector<uint> preference;
};
//Student == pair<vector<uint>,vector<uint>>
void gale_shapely(const vector<Student>& students,const vector<uint>&Clas_cap){
    list<uint> pending_student;
    vector<map<uint/*classemnt*/,uint/*id*/>> affectation(Clas_cap.size());// one map for each class
    for (size_t i = 0; i < students.size(); i++) pending_student.push_back(i);
    while (pending_student.size()){
        int curr_student_id=pending_student.front(); pending_student.pop_front();
        const Student & curr_student=students[curr_student_id];
        cerr<<"Student: "<<curr_student_id<<endl;
        for(uint class_id:curr_student.preference){
            if(affectation[class_id].size()<Clas_cap[class_id]){
                affectation[class_id].insert({curr_student.classement[class_id],curr_student_id});
                cerr<<"\taccepted in: "<<class_id<<endl;
                break;
            }else {
                //auto curr_last=affectation[class_id].rbegin(); 
                //doesn't work because it returns a reverse iterator and erase needs a forward itterator
                auto curr_last=std::prev( affectation[class_id].end() );
                if(curr_student.classement[class_id]< curr_last->first){
                    cerr<<"\tStudent "<<curr_last->second<<" kicked out"<<endl;
                    pending_student.push_back(curr_last->second);
                    affectation[class_id].erase(curr_last);
                    affectation[class_id].insert({curr_student.classement[class_id],curr_student_id});
                    cerr<<"\taccepted in Class: "<<class_id<<endl;
                    break;
                }
            }
            cerr<<"\tnot accepted in Class:"<<class_id<<endl;
        }
    }
    cout<<endl<<endl<<"--------"<<endl;
    cout<<"results:"<<endl;
    cout<<"--------"<<endl;
    for (size_t i = 0; i < Clas_cap.size(); i++){
        cout<<"Class: "<<i<<endl;
        cout<<"Students: ";
        for(auto& p:affectation[i]){
            cout<<p.second<<' ';
        }
        cout<<endl<<endl;
    }

}

int main(int argc, char const *argv[])
{
    vector<uint> Clas_cap{2,3};
    vector<Student> students={
        {{1,5},{1,0}},
		{{6,1}, {0, 1}},
		{{3,3}, {0, 1}},
		{{5,4}, {1, 0}},
		{{4,6}, {1, 0}},
		{{2,2}, {1, 0}}
    };
    gale_shapely(students,Clas_cap);

    return 0;
}
