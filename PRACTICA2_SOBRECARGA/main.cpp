#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

//----------------------- CLASE -------------------------------
class Empleado
{
    private:
        int ClaveEmpleado;
        char Nombre[20];
        char Domicilio[20];
        float Sueldo;
        char ReportaA[20];
    protected:
    public:
        //----------------------------- OBJETO ---------------------------------
        Empleado() { ClaveEmpleado = 0; strcpy(Nombre, " "); strcpy(Domicilio, " "); Sueldo = 0.0; strcpy(ReportaA, " "); }
        Empleado(int ce, const char n[], const char d[], float s, const char ra[]) { ClaveEmpleado = ce; strcpy(Nombre, n); strcpy(Domicilio, d); Sueldo = s; strcpy(ReportaA, ra); }

    //------------------- SOBRECARGA DE OPERADORES -----------------------------
    bool operator == (const Empleado& otro) const
    {
        return (ClaveEmpleado == otro.ClaveEmpleado);
    }

    bool operator != (const Empleado& otro) const
    {
        return !(*this == otro);
    }
    bool operator >= (const Empleado& otro) const
    {
        return (ClaveEmpleado >= otro.ClaveEmpleado);
    }

    bool operator <= (const Empleado& otro) const
    {
        return (ClaveEmpleado <= otro.ClaveEmpleado);
    }

    friend ostream& operator << (ostream &o, const Empleado &emp)
    {
        o << "Clave: " << emp.ClaveEmpleado << endl;
        o << "Nombre: " << emp.Nombre << endl;
        o << "Domicilio: " << emp.Domicilio << endl;
        o << "Sueldo: " << emp.Sueldo << endl;
        o << "Reporta a: " << emp.ReportaA << endl;
        return o;
    }
    friend istream& operator >> (istream &i, Empleado &emp)
    {
        cout << "Clave: ";
        i >> emp.ClaveEmpleado;
        cout << "Nombre: ";
        i >> emp.Nombre;
        cout << "Domicilio: ";
        i >> emp.Domicilio;
        cout << "Sueldo: ";
        i >> emp.Sueldo;
        cout << "Reporta a: ";
        i >> emp.ReportaA;
        return i;
    }

    Empleado operator+(const Empleado& otro) const
    {
        Empleado resultado(*this);
        strcat(resultado.Nombre, " y ");
        strcat(resultado.Nombre, otro.Nombre);
        return resultado;
    }

    //--------------------- MÉTODOS ----------------------
    void CambiaDomicilio(const char nuevoDomicilio[20])
    {
        cout << "\t\t\t\t------------------- CAMBIAR DOMICILIO -------------------\n" << endl;
        cout << "Ingresa nuevo domicilio del empleado: ";
        cin.ignore();
        cin.getline(Domicilio, 20);
    }

    void CambiaReportaA(const char nuevoJefe[20])
    {
        cout << "Ingresa el nombre del nuevo jefe: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignora caracteres adicionales en el buffer de entrada
        cin.getline(ReportaA, 20);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Error: Has ingresado más caracteres de los permitidos. El nombre se truncará a 20 caracteres..." << endl;
        }
    }

    void ActualizaSueldo(float nuevoSueldo)
    {
        Sueldo = nuevoSueldo;
    }

    bool buscarPorClave(int clave) const
    {
        return (clave == ClaveEmpleado);
    }

    void Imprime()
    {
        cout << "\t\t\t\t------------------- CONSULTA DE EMPLEADOS -------------------\n" << endl;
        cout << "Clave: " << ClaveEmpleado << endl;
        cout << "Nombre: " << Nombre << endl;
        cout << "Domicilio: " << Domicilio << endl;
        cout << "Sueldo: " << Sueldo << endl;
        cout << "Reporta a: " << ReportaA << endl;
        system("PAUSE");
        system("cls");
    }
};

//----------------- OPCIONES ENUMERADAS DEL MENÚ PRINCIPAL ------------------------
enum OPTIONS
{
    OPT_SALIR,     //0
    OPT_CONSULTA,  //1
    OPT_MODIFICAR  //2
};

//--------------- OPCIONES ENUMERADAS DEL MENÚ DE MODIFICACIÓN ------------------------
enum OPTIONSMOD
{
    OPT_MODSALIR,       //0
    OPT_CAMBIARDOM,     //1
    OPT_CAMBIARJEFE,    //2
    OPT_CAMBIARSUELDO   //3
};

int main()
{
    setlocale(LC_ALL, "spanish");

    int opt;

    //----------------- INSTANCIAS -------------------------------
    Empleado JefePlanta(123, "Dr. Pepe Pecas", "TodoVerde 443", 75000.99, "Ricardo Kaka");
    cin>>JefePlanta;
    Empleado JefePersonal(234, "Mtro. Paco Cabeza", "Cerro Divino 666", 47999.49, "Dr. Pepe Pecas");
    cin>>JefePersonal;

    do
    {
        cout << "\t     --------------------------------------- DUNDLER MIFFLIN ---------------------------------------\n\n" << endl;
        cout << "(1) Consultar registro de empleados.\n" << endl;
        cout << "(2) Modificar datos de empleado.\n" << endl;
        cout << "(0) Salir.\n" << endl;
        cout << "Seleccione una opción: ";
        cin >> opt;

        system("cls");

        switch (opt)
        {
        case OPT_CONSULTA:
            int clave;

            cout << "\t\t\t\t------------------- CONSULTA DE EMPLEADOS -------------------\n" << endl;
            cout << "\nIngresa la clave del empleado que buscas: "<< endl;
            cin >> clave;

            system("cls");

            if (JefePersonal.buscarPorClave(clave))
            {
                JefePersonal.Imprime();
            }
            else if (JefePlanta.buscarPorClave(clave))
            {
                JefePlanta.Imprime();
            }
            else
            {
                cout << "\n\nLa clave que ingresaste no corresponde a ningún empleado registrado." << endl;
                system("PAUSE");
                system("cls");
            }
            break;

        case OPT_MODIFICAR:
            int optMod;
            do
            {
                cout << "\t\t\t------------------ MODIFICAR DATOS DE EMPLEADO ------------------\n" << endl;
                cout << "(1) Cambiar domicilio.\n" << endl;
                cout << "(2) Cambiar al jefe al que reporta.\n" << endl;
                cout << "(3) Cambiar el salario que percibe el empleado.\n" << endl;
                cout << "(0) Salir.\n" << endl;
                cout << "Seleccione una opción: ";
                cin >> optMod;

                system("cls");

                switch (optMod)
                {
                    case OPT_CAMBIARDOM:
                        cout << "\t\t\t\t------------------- CAMBIAR DOMICILIO -------------------\n" << endl;
                        cout << "\nIngresa la clave del empleado que buscas: ";
                        cin >> clave;

                        system("cls");

                        if (JefePersonal.buscarPorClave(clave))
                        {
                            JefePersonal.CambiaDomicilio("Nuevo Domicilio");
                            system("cls");
                        }
                        else if (JefePlanta.buscarPorClave(clave))
                        {
                            JefePlanta.CambiaDomicilio("Nuevo Domicilio");
                            system("cls");
                        }
                        else
                        {
                            cout << "\n\nLa clave que ingresaste no corresponde a ningún empleado registrado." << endl;
                            system("PAUSE");
                            system("cls");
                        }

                        break;
                    case OPT_CAMBIARJEFE:
                        cout << "\t\t\t\t------------------- CAMBIAR JEFE -------------------\n" << endl;
                        cout << "\nIngresa la clave del empleado que buscas: ";
                        cin >> clave;

                        system("cls");

                        if (JefePersonal.buscarPorClave(clave))
                        {
                            JefePersonal.CambiaReportaA("Nuevo Jefe");
                            system("PAUSE");
                            system("cls");
                        }
                        else if (JefePlanta.buscarPorClave(clave))
                        {
                            JefePlanta.CambiaReportaA("Nuevo Jefe");
                            system("PAUSE");
                            system("cls");
                        }
                        else
                        {
                            cout << "\n\nLa clave que ingresaste no corresponde a ningún empleado registrado." << endl;
                            system("cls");
                        }
                        break;
                    case OPT_CAMBIARSUELDO:
                        cout << "\t\t\t\t------------------- CAMBIAR SUELDO -------------------\n" << endl;
                        cout << "\nIngresa la clave del empleado que buscas: ";
                        cin >> clave;

                        system("cls");

                        if (JefePersonal.buscarPorClave(clave))
                        {
                            float nuevoSueldo;
                            cout << "\t\t\t\t------------------- CAMBIAR SUELDO -------------------\n" << endl;
                            cout << "Ingresa el nuevo sueldo: ";
                            cin >> nuevoSueldo;
                            JefePersonal.ActualizaSueldo(nuevoSueldo);
                            system("cls");
                        }
                        else if (JefePlanta.buscarPorClave(clave))
                        {
                            float nuevoSueldo;
                            cout << "\t\t\t\t------------------- CAMBIAR SUELDO -------------------\n" << endl;
                            cout << "Ingresa el nuevo sueldo: ";
                            cin >> nuevoSueldo;
                            JefePlanta.ActualizaSueldo(nuevoSueldo);
                            system("cls");
                        }
                        else
                        {
                            cout << "\n\nLa clave que ingresaste no corresponde a ningún empleado registrado." << endl;
                            system("cls");
                        }
                        break;
                    case OPT_MODSALIR:
                        {
                            cout << "\n\n\n\n\n\n\t\t\t\t\t\tVolviendo al menú principal...\n\n\n\n" << endl;
                            system("cls");
                        }
                        break;
                    default:
                        cout << "Opción inválida..." << endl;
                        system("PAUSE");
                        system("cls");
                        break;
                    }
            } while(optMod != OPT_MODSALIR);
            break;

        case OPT_SALIR:
            cout << "\n\n\n\n\n\n\t\t\t\t\t\t\tSaliendo...\n\n\n\n" << endl;
            break;

        default:
            cout << "Opción inválida..." << endl;
            system("PAUSE");
            system("cls");
            break;
        }
    }while(opt != OPT_SALIR);

    return 0;
}
