#include <iostream>
#include <fstream>
#include <sstream>
bool primerbase();
int calcularhe(int , int );
void horariosdeclase();
bool existemateria(char [100],int *);
int charaint(char [5]);
bool horariovalido(char , int , int);
char* intachar(int);
int contarmaterias();
bool existecodigo(char [100]);

using namespace std;

int main()
{
    cout<<"Bienvenido al preparador de horas de estudio"<<endl;
    bool mov=primerbase();
    if (mov){
        cout<<"Materias guardadas exitosamente"<<endl;
        horariosdeclase();

    }
}

bool primerbase()
{
    ofstream arch;
    arch.open("basedatosuno.txt",ios::trunc);
    arch.close();
    char datos[100];
    char c;
    bool ban=true, existe;
    int horas=0,acumh=0,creditos=0, he=0;
    while(ban){
        cout<<"Ingrese el codigo de la materia: ";
        cin>>datos;
        existe=existecodigo(datos);
        if(existe){
            ofstream arch2;
            arch2.open("basedatosuno.txt",ios::app);
            arch2<<datos;
            arch2<<':';
            cout<<"Ingrese el nombre de la materia: ";
            cin>>datos;
            arch2<<datos;
            arch2<<',';
            cout<<"Ingrese las horas asistidas por docente: ";
            cin>>horas;
            while(horas<0 || horas>83){
                cout<<"Ingrese una hora valida: ";
                cin>>horas;
            }
            arch2<<horas;
            arch2<<',';
            acumh+=horas;
            cout<<"Ingrese la cantidad de creditos: ";
            cin>>creditos;
            he=calcularhe(creditos,horas);
            while(he<=0){
                cout<<"Ingrese una cantidad de creditos validos: ";
                cin>>creditos;
                he=calcularhe(creditos,horas);
            }
            acumh+=he;
            arch2<<he;
            arch2<<',';
            arch2<<creditos;
            if (acumh>83){
                cout<<"El horario es muy pesado, cancele materias"<<endl;
                return false;
            }
            cout<<"Desea ingresar mas materias S para si y N para no: ";
            cin>>c;
            while(c!='s' && c!='S' && c!='N' && c!='n'){
                cout<<"Ingrese un movimiento valido: ";
                cin>>c;
            }
            if(c=='N' || c=='n'){
                ban=false;
            }
            arch2<<'\n';
            arch2.close();
        }
        else{
            cout<<"La materia ya fue ingresada"<<endl;
        }
    }
    return true;

}
bool existecodigo(char array[100])
{
    ifstream arch;
    char datos[200];
    int cont=0;
    arch.open("basedatosuno.txt");
    while(arch.good()){
        arch.getline(datos,200);
        cont=0;
        while(datos[cont]==array[cont]){
            cont+=1;
        }
        if(datos[cont]==':'){
            arch.close();
            return false;
        }
    }
    arch.close();
    return true;
}


int calcularhe(int a, int hd)
{
    a*=48;
    a/=16;
    a-=hd;
    return a;

}

void horariosdeclase()
{
    bool ban=true;
    char array[254];
    char dia='\0', N='\0';
    int horas=0, acumh=0, HI=0,HF=0;
    cout<<"Para ingresar dias cuando se solicite ingrese la inicial para miercoles sera w"<<endl;
    cout<<"Los horas estan en formato de 24 horas"<<endl;
    int materias=0, contm=0;
    materias=contarmaterias();
    while(ban){
        cout<<"Ingrese el codigo de la materia para asignar horarios: ";
        cin>>array;
        bool existe=existemateria(array,&horas);
        if (existe){
            cout<<"Materia encontrada"<<endl;
            acumh=0;
            contm+=1;
            while(acumh!=horas){
                cout<<"Tiene "<<horas-acumh<<" horas por ingresar"<<endl;
                cout<<"Ingrese el dia: ";
                cin>>dia;
                while(dia!='L' && dia!='l' && dia!='M' && dia!='m' && dia!='W' && dia!='w' && dia!='J' && dia!='j' && dia!='V' && dia!='v'){
                    cout<<"Ingrese una inicial valida: ";
                    cin>>dia;
                }
                cout<<"Ingrese la hora inicial de la clase: ";
                cin>>HI;
                while(HI<6 || HI>19){
                    cout<<"Ingrese una hora inicial valida: ";
                    cin>>HI;
                }
                cout<<"Ingrese la hora final de la clase: ";
                cin>>HF;
                while(HF<6 || HF>20){
                    cout<<"Ingrese una hora final valida: ";
                    cin>>HF;
                }
                if(HF-HI>0 && acumh+(HF-HI)<=horas){
                    if(dia=='l' || dia=='m' || dia=='w' || dia=='j' || dia=='v'){
                        dia-=32;
                    }
                    bool valido=horariovalido(dia,HI,HF);
                    if (valido){
                        acumh=acumh+(HF-HI);
                        ofstream arch;
                        arch.open("basedatosdos.txt",ios::app);
                        arch<<array;
                        arch<<'=';
                        arch<<dia;
                        arch<<':';
                        arch<<HI;
                        HI+=1;
                        while(HI<HF){
                            arch<<'-';
                            arch<<HI;
                            HI+=1;
                        }
                        arch<<'_';
                        arch<<HF;
                        arch<<'\n';
                        arch.close();
                    }
                    else{
                        cout<<"El horario ingresado se interpone a un horario ya antes ingresado"<<endl;
                    }
                }
                else{
                    cout<<"El horario ingresado supera las horas de la materia"<<endl;
                }
            }
        }
        else{
            cout<<"Materia no encontrada"<<endl;
        }
        if (contm==materias){
            cout<<"Totalidad de horarios de materias ingresados exitosamente"<<endl;
            ban=false;
        }
        else{
            cout<<"Desea ingresar más horarios para materias s para si, n para no: ";
            cin>>N;
            while(N!='s' && N!='S' && N!='N' && N!='n'){
                cout<<"Ingrese un movimiento valido: ";
                cin>>N;
            }
            if(N=='N' || N=='n'){
                cout<<"Horarios ingresados exitosamente"<<endl;
                ban=false;
            }
        }
    }
}

bool existemateria(char a[254], int *p)
{
    int cont=0,contin=0;
    char datos[254];
    char numeros[5];
    ifstream arch;
    bool existe;
    arch.open("basedatosuno.txt");
    while(a[contin]!='\0'){
        contin+=1;
    }
    while(arch.good()){
        arch.getline(datos,254);
        while(datos[cont]!=':'){
            cont+=1;
        }
        if (contin==cont){
            for(int i=0;i<cont;i++){
                if(a[i]!=datos[i]){
                    break;
                }
                else if(i==cont-1){
                    existe=true;
                    while(datos[cont]!=','){
                        cont+=1;
                    }
                    cont+=1;
                    contin=0;
                    while(datos[cont]!=','){
                        numeros[contin]=datos[cont];
                        cont+=1;
                        contin+=1;
                    }
                    *p=charaint(numeros);
                    return existe;
                }
            }
        }
    }
    arch.close();
    existe=false;
    return existe;

}

int charaint(char array[5])
{
    int numero=0, auxnum=0;
    numero=array[0];
    numero-=48;
    auxnum=array[1];
    auxnum-=48;
    if (auxnum>=0 && auxnum<=9){
        numero=(numero*10)+auxnum;
    }
    return numero;
}

bool horariovalido(char d, int HI, int HF)
{
    ifstream arch;
    arch.open("basedatosdos.txt");
    char *CHI=intachar(HI);
    char *CHF=intachar(HF);
    char array[200];
    int cont=0;
    while(arch.good()){
        arch.getline(array,200);
        cont=0;
        if(array[cont]=='\0'){
            arch.close();
            delete[] CHI;
            delete[] CHF;
            return true;
        }
        while(array[cont]!='='){
            cont+=1;
        }
        cont+=1;
        if (array[cont]==d){
            cont+=2;
            if(array[cont]==CHI[0] && (array[cont+1]<48 || array[cont+1]>57) ){
                arch.close();
                delete[] CHI;
                delete[] CHF;
                return false;
            }
            else if(array[cont]==CHI[0] && array[cont+1]==CHI[1]){
                arch.close();
                delete[] CHI;
                delete[] CHF;
                return false;
            }
            while(array[cont]!='-' && array[cont]!='_'){
                cont+=1;
            }
            while(array[cont]!='_'){
                cont+=1;
                if(array[cont]==CHI[0] && (array[cont+1]<48 || array[cont+1]>57)){
                    arch.close();
                    delete[] CHI;
                    delete[] CHF;
                    return false;
                }
                else if(array[cont]==CHI[0] && array[cont+1]==CHI[1]){
                    arch.close();
                    delete[] CHI;
                    delete[] CHF;
                    return false;
                }
                if(array[cont]==CHF[0] && (array[cont+1]<48 || array[cont+1]>57)){
                    arch.close();
                    delete[] CHI;
                    delete[] CHF;
                    return false;
                }
                else if(array[cont]==CHF[0] && array[cont+1]==CHF[1]){
                    arch.close();
                    delete[] CHI;
                    delete[] CHF;
                    return false;
                }
                while(array[cont]!='-' && array[cont]!='_'){
                    cont+=1;
                }
            }
            cont+=1;
            if(array[cont]==CHF[0] && (array[cont+1]<48 || array[cont+1]>57)){
                arch.close();
                delete[] CHI;
                delete[] CHF;
                return false;
            }
            else if(array[cont]==CHF[0] && array[cont+1]==CHF[1]){
                arch.close();
                delete[] CHI;
                delete[] CHF;
                return false;
            }

        }

    }
    arch.close();
    delete[] CHI;
    delete[] CHF;
    return true;
}

char* intachar(int N)
{
    int res=0;
    char* array= new char[3];
    char c='\0';
    if (N/10>=1){
        res=N%10;
        res+=48;
        c=res;
        array[1]=c;
        N/=10;
        res=N%10;
        res+=48;
        c=res;
        array[0]=c;
        array[2]='\0';
        return array;
    }
    else if(N/10==0){
        res=N%10;
        res+=48;
        c=res;
        array[0]=res;
        array[1]='\0';
        return array;
    }
}

int contarmaterias(){
    ifstream arch;
    int N=0;
    char array[150];
    arch.open("basedatosuno.txt");
    while(arch.good()){
        arch.getline(array,150);
        if (array[0]!='\0'){
            N+=1;
        }
    }
    arch.close();
    return N;
}
