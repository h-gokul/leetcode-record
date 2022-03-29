#include <bits/stdc++.h>
using namespace std;

// ////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////// Factory Design pattern //////////////////////////////////////
// ///////  Create an abstract class as a blue print and use it as an image processor.  ///////
// ////////////////////////////////////////////////////////////////////////////////////////////

int globalvar;
// Base class
class ICVLib{
    public:
        int i_var = 10;
        ICVLib() {printf("icvlib alive\n");}
        virtual void printItem()=0;
        // virtual void process()=0;
        virtual void process(){
            printf("base class process \n");
        }
        virtual ~ICVLib() {printf("icvlib dead\n");}
};

// 2 image processor products.
class smoothen: public ICVLib{
    private:
        int m_var;
    public:    
        smoothen() {printf("icv::smoothen start\n");}
        smoothen(const smoothen &obj): m_var(obj.m_var) {printf("smooth copied\n");} // copy constructor
        smoothen(const smoothen &&obj): m_var(obj.m_var) {printf("smooth moved\n");} // move constructor
        
        void printItem() {
            cout << " Smoothening function \n";
        } 
        void process() {
            cout << " cv2.smoothen() \n";
        }     
        ~smoothen() {printf("icv::smoothen end\n");}
};
class sharpen: public ICVLib{
    public:
        static int p_var;
        sharpen() {printf("icv::sharpen start\n");}
        void printItem() {
            cout << " Sharpening function \n";
        } 
        void process() {
            cout << " cv2.sharpen() operation \n"; p_var+=1;
        }     
        ~sharpen() {printf("icv::sharpen end\n");}
};
int sharpen::p_var=10;
// factory class
enum ProcessType : int{
     smoothen_type, sharpen_type, blur
};
class CVFactory{
    
    public :       
    static ICVLib* createProcess(ProcessType type){  
   
        ICVLib* processObject=NULL;
        switch(type){
            case 0: { // ProcessType::smoothen
                printf("smooth\n");
                // return new smoothen;
                processObject = new smoothen(); break;
            }
            case 1: { // ProcessType::sharpen
                printf("sharp\n");
                // return new sharpen;
                processObject = new sharpen(); break;
            }
            default: return NULL; break;
        }

        return processObject;
    }

};

typedef unsigned int uint;
template<typename T>
class shared_pointer{
    public:
        T* m_var = nullptr;
        uint* refCount = nullptr;
    public:
        shared_pointer(): m_var(nullptr), refCount(new uint(0)) {} // default constructor
        shared_pointer(T* ptr): m_var(ptr), refCount(new uint(1)) { // param constructor
            cout<<"[debug]: pcnst="<< *refCount<<'\n';
            } 

        ////// copy constructors ////
        void _copyconst_(const shared_pointer &obj){ // helper
            this->m_var = obj.m_var;
            this->refCount = obj.refCount;
            if (this->m_var) (*this->refCount)++;
        }

        shared_pointer(const shared_pointer &obj){
            _copyconst_(obj);
        }
        // copy constructor: operator overload
        shared_pointer& operator=(const shared_pointer &obj){
            _cleanup_();
            _copyconst_(obj);
        }

        ////// move semantics //////
        // void _moveconst_(const shared_pointer &&obj){
        //     printf("Moved\n");
        //     this->m_var = obj.m_var;
        //     this->refCount = obj.refCount;
        //     obj.m_var =nullptr; obj.refCount = 0;

        // } 
        shared_pointer(const shared_pointer &&obj){
            // _moveconst_(obj);
            printf("Moved\n");
            this->m_var = obj.m_var;
            this->refCount = obj.refCount;
            obj.m_var =nullptr; obj.refCount = nullptr;

        }
        //move semantics: operator overload
        shared_pointer& operator=(const shared_pointer &&obj){
            _cleanup_();
            printf("Moved\n");
            this->m_var = obj.m_var;
            this->refCount = obj.refCount;
            obj.m_var =nullptr; obj.refCount = nullptr;
        }

        //// output: -> and * operators ////
        T* operator->() const {
            return this->m_var;
        }
        
        T& operator*() const {
            return *(this->m_var);
        }
        uint getCount() const{
            return *refCount;
        }

        ~shared_pointer(){
            _cleanup_();
        }

        //// destruct object
        private:
            void _cleanup_(){
                (*refCount)--;            
                if (*refCount == 0){
                    if (m_var != NULL) delete m_var;
                    delete refCount; 
                }
            }
};

#define sharedPTR

// client call.
int main(){    
    #ifdef sharedPTR
    {
    cout << "---class type shared ptr---"<< endl;    
    // parameterised constructor: works
    shared_pointer<sharpen> obj1(new sharpen());  
    // arrow operator:  works
    obj1->process(); 
    
    // copy constructor operator overload
    shared_pointer<sharpen> obj2= obj1;
    
    // star operator works
    (*obj1).printItem(); 
    cout << (*obj1).i_var << endl;

    }
    {
        cout << "---Integer shared ptr---"<< endl;
        shared_pointer<int> int_var1(new int(10));
        cout << *int_var1 <<' '<< int_var1.getCount()<< endl;

    }    

    // regular object    
    // ICVLib* obj = new sharpen();    
    // obj->process();
    // delete obj;
    return 0;
    #endif
    
    ICVLib* processObject = CVFactory::createProcess(ProcessType::sharpen_type);
    if (processObject){
        processObject->process();
        delete processObject;
    }
    else cout << "NULL return \n"; 
    
    
}