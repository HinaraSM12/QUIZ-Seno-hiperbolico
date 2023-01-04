#include <iostream>
using namespace std;

int main()
{
    //DEFINICIÓN DE VARIABLES
    int n2 = 2, n = 0, m;
    float x, r3, r2;
    double cont, r, r4, result = 0, resultado, n1 = 1;

    cout << "CALCULO DEL SENO HIPERBOLICO MEDIANTE LA SERIE DE TAYLOR\n";
    cout << "\nREALIZADO POR: HINARA SANCHEZ, JUAN OSPINA, LUZARAIT CANAS Y SEBASTIAN AGUINAGA\n";
    cout << "\nIngrese el valor de x: ";
    cin >> x;
    cout << "\nIngrese el valor de m: ";
    cin >> m;

    _asm {
        finit                                   //Iniciar el coprocesador
        inc n                                   //Incrementar el valor de n

        //SUMATORIA
        inc m                                   //Incrementar el valor de m
        mov ecx, m                              //mover el valor de m al registro ecx
        sum :                                    //Inicia el ciclo sum
            //CALCULO 2N+1 CON PILAS
        fild n2                             //Carga a n2 en la pila
            fild n                              //Carga a n en la pila
            fmul                                //Multiplica a n2 con n
            fstp cont //cont es 2n              //Guarda el resultado en la variable cont
            fld cont                            //Coloca la variable cont en la pila
            fadd n1                             //Le suma n1 a la variable cont
            fstp r //r es 2n+1                  //Guarda el resultado en la variable r

            //CALCULO 2N CON REGISTROS
            mov ebx, n                          //Mueve el valor de n al registro ebx
            mov eax, 2                          //Mueve el valor de 2 al registro eax
            mul ebx                             //Multiplica lo que hay en el registro ebx con lo que hay en el registro eax
            mov ecx, eax //En ecx está 2n       //Mueve el valor de eax y lo pasa al registro ecx

            //POTENCIA
            mov ecx, eax                        //Mueve el valor de eax y lo pasa al registro ecx
            fld x                               //Coloca la variable x en la pila
            potencia :                           //Comienza el ciclo potencia
        fmul x                          //Multiplica la variable x por si misma
            loop potencia                       //Decrementa ecx y termina cuando esta llegue a cero
            fstp r2                             //Guarda el resultado en la variable r2
            finit                               //Vacía la pila para no perjudicar próximos cálculos

            //FACTORIAL
            mov ecx, eax                        //Mueve lo que hay en eax al registro ecx
            fld r                               //Coloca a r en la pila
            fact :                               //Comienza el ciclo fact
        fmul cont                       //Multiplica a cont con r
            fld cont                        //Coloca cont en la pila
            fsub n1                         //Le resta a cont el valor de n1
            fstp cont                       //Guarda el resultado en cont
            loop fact                           //Decrementa ecx y termina cuando esta llegue a cero
            fstp r3                             //Guarda el resultado final del loop en r3
            finit                               //Vacía la pila para no perjudicar próximos cálculos

            //DIVISION
            fld r2                     		    //Coloca a r2 en la pila
            fdiv r3                    		    //Divide r2 con r3
            fstp r4                    		    //Guarda el resultado en r4

            //DECREMENTANDO M Y AUMENTANDO N
            inc n                               //Incrementa a n
            dec m                               //Decrementa a m
            mov ecx, m                          //Mueve el valor de m en el registro ecx

            //GUARDADO DEL RESULTADO
            fld result                          //Coloca la variable result en la pila
            fadd r4                             //Le suma r4 a la variable result
            fstp result                         //Guarda el resultado en result
            finit                               //Vacía la pila para no perjudicar próximos cálculos
            loop sum                       		//Decrementa ecx y termina cuando esta llegue a cero
            fld result                     		    //Coloca la variable result en la pila
            fadd x                        		    //Le suma x a la variable result
            fstp resultado                 		    //Guarda el resultado en la variable resultado
            fwait                          		    //Sincroniza el procesador y el coprocesador
    }
    cout << "\nEl valor de senh(x) es: " << resultado << "\n";
    getchar();
    return 0;
}