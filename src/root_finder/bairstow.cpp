#include<iostream>
#include<cmath>

using namespace std;

void Bairstow(float r, float s, float array[], int grado){
	float b[grado+1];
    float c[grado+1];
    b[0]= array[0];
    b[1] = array[1]+(b[0]*r);
    b[2] = array[2]+(b[1]*r)+(b[0]*s);
    for (int i = 3; i < grado+1; ++i)
    {
        b[i] = array[i] + (b[i-1]*r) + (b[i-2]*s);
    }

    cout << "-----b-----" << endl;
    for (int i = 0; i < grado+1; ++i)
    {
        cout << b[i] <<endl;
    }
    cout << "----------" << endl;

    c[0]= b[0];
    c[1] = b[1]+(c[0]*r);
    c[2] = b[2]+(c[1]*r)+(c[0]*s);
    for (int i = 3; i < grado+1; ++i)
    {
        c[i] = b[i] + (c[i-1]*r) + (c[i-2]*s);
    }

    cout << "-----c-----" << endl;
    for (int i = 0; i < grado+1; ++i)
    {
        cout << c[i] <<endl;
    }
    cout << "----------" << endl;

    //Método de Cramer para obtener deltaR y deltaS
    float A = c[grado-2];
    float B = c[grado-3];
    float C = -b[grado-1];
    float P = c[grado-1];
    float Q = c[grado-2];
    float R = -b[grado];

    float deltaR = ((C*Q)-(B*R))/((A*Q)-(P*B));
    float deltaS = ((A*R)-(C*P))/((A*Q)-(P*B));
    cout << "deltaR" << deltaR << endl;
    cout << "deltaS" << deltaS << endl;

    r += deltaR;
    s += deltaS;
    cout << "nueva r: " << r <<endl;
    cout << "nueva s: " << s <<endl;

    float errorR = abs(deltaR/r)*100;
    float errorS = abs(deltaS/s)*100;

    cout << "ErrorR: " << errorR << endl;
    cout << "ErrorS: " << errorS << endl;

    int counter = 0;

    while (errorR >= .01 || errorS >= .01){
        b[0]= array[0];
        b[1] = array[1]+(b[0]*r);
        b[2] = array[2]+(b[1]*r)+(b[0]*s);
        for (int i = 3; i < grado+1; ++i)
        {
            b[i] = array[i] + (b[i-1]*r) + (b[i-2]*s);
        }

        cout << "-----b-----" << endl;
        for (int i = 0; i < grado+1; ++i)
        {
            cout << b[i] <<endl;
        }
        cout << "----------" << endl;

        c[0]= b[0];
        c[1] = b[1]+(c[0]*r);
        c[2] = b[2]+(c[1]*r)+(c[0]*s);
        for (int i = 3; i < grado+1; ++i)
        {
            c[i] = b[i] + (c[i-1]*r) + (c[i-2]*s);
        }

        cout << "-----c-----" << endl;
        for (int i = 0; i < grado+1; ++i)
        {
            cout << c[i] <<endl;
        }
        cout << "----------" << endl;

        //Método de Cramer para obtener deltaR y deltaS
        A = c[grado-2];
        B = c[grado-3];
        C = -b[grado-1];
        P = c[grado-1];
        Q = c[grado-2];
        R = -b[grado];

        deltaR = ((C*Q)-(B*R))/((A*Q)-(P*B));
        deltaS = ((A*R)-(C*P))/((A*Q)-(P*B));
        cout << "deltaR" << deltaR << endl;
        cout << "deltaS" << deltaS << endl;

        r += deltaR;
        s += deltaS;
        cout << "nueva r: " << r <<endl;
        cout << "nueva s: " << s <<endl;

        errorR = abs(deltaR/r);
        errorS = abs(deltaS/s);

        cout << "ErrorR: " << errorR << endl;
        cout << "ErrorS: " << errorS << endl;

        counter++;
    }

    float x1 = (r+sqrt(pow(r,2)+(4*s)))/2;
    float x2 = (r-sqrt(pow(r,2)+(4*s)))/2;
    cout << "----RAICES-----" << endl;
    cout << "x1: " << x1 << endl;
    cout << "x2: " << x2 << endl;

    cout << "-----FIN-----" << endl;
    for (int i = 0; i < grado-1; ++i)
    {
        cout << b[i] <<endl;
    }
    cout << "----ITERACIONES-----" << endl;
    cout << counter << endl;
}

int main(){
    float arreglo[] = {};
    int size = sizeof(arreglo)/sizeof(arreglo[0]);
    int grado = size-1;
    cout << "Grado = " << grado << endl;
    float r = -3;
    float s = 4;

    Bairstow(r,s,arreglo,grado);
}
