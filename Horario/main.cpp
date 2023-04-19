#include <iostream>
#include <fstream>
#include <sstream>
void primerbase();
bool existecodigo(char [100]);
int calcularhe(int , int );
bool tomarmaterias();
void horariosdeclase();
void imprimirnombre(char [100]);
bool existemateria(char [100],int *,int *,char [254]);
int charaint(char [5]);
bool horariovalido(char , int , int);
char* intachar(int);
void generarmatriz(char ***);
int valordia(char);

using namespace std;

int main()
{
    int m=0;
    bool ban=true,ban2=true;
    cout<<"Bienvenido al preparador de horas de estudio"<<endl;
    while(ban){
        cout<<"Ingrese 1 para ingresar como administrador, 2 para usuario, 3 para cerrar programa: ";
        cin>>m;
        while(m<1 || m>3){
            cout<<"Ingrese un movimiento valido: ";
            cin>>m;
        }
        if(m==1){
            primerbase();
        }
        else if (m==2){
            ban2=tomarmaterias();
            if(ban2){
                ofstream arch;
                arch.open("basedatosdos.txt",ios::trunc);
                arch.close();
                horariosdeclase();
                char*** matriz = new char**[5];
                for (int i = 0; i < 5; i++) {
                    matriz[i] = new char*[18];
                    for (int j = 0; j < 18; j++) {
                        matriz[i][j] = new char[20];
                    }
                }
                generarmatriz(matriz);
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 18; j++) {
                        delete[] matriz[i][j];
                    }
                    delete[] matriz[i];
                }
                delete[] matriz;
            }
        }
        else if(m==3){
            ban=false;
        }

    }
}

void primerbase()
{
    char datos[100];
    bool ban=true, existe;
    int horas=0, creditos=0, he=0, m=0;
    while(ban){
        cout<<"Ingrese 1 para agregar materia al pensum, 2 para regresar: ";
        cin>>m;
        while(m<1 || m>2){
            cout<<"Ingrese un movimiento valido";
            cin>>m;
        }
        if(m==1){
            cout<<"Ingrese el codigo de la materia: ";
            cin>>datos;
            existe=existecodigo(datos);
            if(existe){
                ofstream arch;
                arch.open("basedatosuno.txt",ios::app);
                arch<<datos;
                arch<<':';
                cout<<"Ingrese el nombre de la materia: ";
                cin>>datos;
                arch<<datos;
                arch<<',';
                cout<<"Ingrese las horas asistidas por docente: ";
                cin>>horas;
                while(horas<0 || horas>12){
                    cout<<"Ingrese una horas validas: ";
                    cin>>horas;
                }
                arch<<horas;
                arch<<',';
                cout<<"Ingrese la cantidad de creditos: ";
                cin>>creditos;
                he=calcularhe(creditos,horas);
                if(he<0){
                    he=0;
                }
                arch<<he;
                arch<<',';
                arch<<creditos;
                arch<<'\n';
                arch.close();
            }

            else{
                cout<<"La materia ya fue ingresada"<<endl;
            }
        }
        else if(m==2){
            ban=false;
        }
    }
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
bool tomarmaterias()
{
    int acumhoras=0;
    int he=0, hp=0;
    char array[254], datos[254];
    bool ban=true, mov=true;
    ofstream arch;
    char N='\0';
    arch.open("clasesusuario.txt");
    while(ban){
        cout<<"Ingrese el codigo de la materia que desea tomar: ";
        cin>>array;
        bool existe=existemateria(array,&he,&hp,datos);
        if (existe){
            cout<<"Materia encontrada"<<endl;
            acumhoras+=he;
            acumhoras+=hp;
            if(acumhoras<83){
                arch<<datos;
                arch<<'\n';
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
            else{
                cout<<"El horario ingresado es muy pesado, cancele materias e intente de nuevo"<<endl;
                ban=false;
                mov=false;
            }

        }

    }
    arch.close();
    return mov;
}
bool existemateria(char a[254], int *p,int *h,char d[254])
{
    int cont=0,contin=0;
    char numeros[5];
    ifstream arch;
    bool existe=true;
    arch.open("basedatosuno.txt");
    while(a[contin]!='\0'){
        contin+=1;
    }
    while(arch.good()){
        arch.getline(d,254);
        while(d[cont]!=':'){
            cont+=1;
        }
        if (contin==cont){
            for(int i=0;i<cont;i++){
                if(a[i]!=d[i]){
                    break;
                }
                else if(i==cont-1){
                    existe=true;
                    while(d[cont]!=','){
                        cont+=1;
                    }
                    cont+=1;
                    contin=0;
                    while(d[cont]!=','){
                        numeros[contin]=d[cont];
                        cont+=1;
                        contin+=1;
                    }
                    *p=charaint(numeros);
                    numeros[1]='\0';
                    cont+=1;
                    contin=0;
                    while(d[cont]!=','){
                        numeros[contin]=d[cont];
                        cont+=1;
                        contin+=1;
                    }
                    *h=charaint(numeros);
                    arch.close();
                    return existe;
                }
            }
        }
    }
    arch.close();
    existe=false;
    return existe;

}

void horariosdeclase()
{
    ifstream arch;
    arch.open("clasesusuario.txt");
    char array[254],numero[5];
    char dia='\0';
    int cont=0,contaux=0;
    int horas=0, acumh=0, HI=0,HF=0;
    cout<<"Para ingresar dias cuando se solicite ingrese la inicial para miercoles sera w"<<endl;
    cout<<"Los horas estan en formato de 24 horas"<<endl;
    while(arch.good()){
        char *nombre=new char[100];
        acumh=0;
        cont=0;
        arch.getline(array,254);
        if(array[cont]!='\0'){
            while(array[cont]!=':'){
                cont+=1;
            }
            contaux=0;
            cont+=1;
            while(array[cont]!=','){
                nombre[contaux]=array[cont];
                cont+=1;
                contaux+=1;
            }
            nombre[contaux]='\0';
            cont+=1;
            contaux=0;
            while(array[cont]!=','){
                numero[contaux]=array[cont];
                cont+=1;
                contaux+=1;
            }
            horas=charaint(numero);
            imprimirnombre(nombre);
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
                while(HF<7 || HF>20){
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
                        arch<<nombre;
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
            cout<<"Todos los horarios de las materias han sido guardados exitosamente"<<endl;
        }
        delete[] nombre;
    }
}

void imprimirnombre(char array[100])
{
    cout<<"Vas a ingresar los horarios de ";
    for(int i=0;array[i]!='\0';i++){
       cout<<array[i];
    }
    cout<<endl;
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

void generarmatriz(char ***matriz)
{
    ifstream arch;
    char array[200];
    int cont=0, dia=0, contaux=0, HI=0,HF=0;
    char d='\0';
    char numeros[5];
    arch.open("basedatosdos.txt");
    while(arch.good()){
        char codi[20];
        arch.getline(array,200);
        cont=0;
        while(array[cont]!='='){
            codi[cont]=array[cont];
            cont+=1;
        }
        codi[cont]='\0';
        cont+=1;
        d=array[cont];
        dia=valordia(d);
        cont+=2;
        contaux=0;
        numeros[1]='\0';
        while(array[cont]!='-' && array[cont]!='_'){
            numeros[contaux]=array[cont];
            cont+=1;
            contaux+=1;
        }
        HI=charaint(numeros);
        contaux=0;
        while(array[cont]!='_'){
            cont+=1;
        }
        numeros[1]='\0';
        cont+=1;
        while(array[cont]!='\0'){
            numeros[contaux]=array[cont];
            cont+=1;
            contaux+=1;
        }
        HF=charaint(numeros);
        HF-=7;
        HI-=6;
        while(HI<=HF){
            for(int i=0;codi[i]!='\0';i++){
                matriz[dia][HI][i]=codi[i];
            }
            HI+=1;
        }



    }
    arch.close();
}

int valordia(char d)
{
    if(d=='L'){
        return 0;
    }
    else if(d=='M'){
        return 1;
    }
    else if(d=='W'){
        return 2;
    }
    else if(d=='J'){
        return 3;
    }
    else if(d=='V'){
        return 4;
    }
}
