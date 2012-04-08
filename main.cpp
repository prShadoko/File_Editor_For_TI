#include <QApplication>
#include <iostream>
#include "tifile.h"
#include "tivar.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cerr << argv[0] << " expects one argument." << endl;
        return EXIT_FAILURE;
    }

    TiFile file(argv[1]);

    cout        << file.calc_model()                 << endl
         << hex << file.signature1()          << 'h' << endl
                << file.default_folder_name()        << endl
                << file.comment()                    << endl
         << dec << file.entries_number()             << endl
                << file.file_size()                  << endl
         << hex << file.signature2()          << 'h' << endl
                                                     << endl;

    QList<TiVarEntry*> var_table = file.entries();
    for(QList<TiVarEntry*>::iterator it=var_table.begin(); it!=var_table.end(); it++)
    {
        if((*it)->isFolder())
        {
            cout << (*it)->name()       << endl
                 << (*it)->var_number() << endl
                                        << endl;
        }
        else
        {
            cout << hex << (*it)->offset()            << 'h' << endl
                        << (*it)->name()              << endl
                        << (qint16)(*it)->type_id()   << 'h' << endl
                        << (qint16)(*it)->attribute() << 'h' << endl;
            TiVar *var = (*it)->variable();
            var->parse();
            cout << "<--" << endl;
            switch((*it)->type_id())
            {
                case TiVarEntry::String:{
                    cout << dec << ((TiStringVar*)var)->size()                      << endl
//                         << hex << (qint16)((TiStringVar*)var)->signature1() << 'h' << endl
                                << ((TiStringVar*)var)->data()                      << endl
                         << hex << (qint16)((TiStringVar*)var)->signature2() << 'h' << endl;
                    break;
                }

                default:{
                    cout << "Type de variable non pris en charge." << endl;
                    break;
                }
            }
            cout << "-->" << endl
                          << endl;
        }
    }

    return EXIT_SUCCESS;
}
