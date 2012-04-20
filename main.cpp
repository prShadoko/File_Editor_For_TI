#include <QApplication>
#include <cstdlib>
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
    file.readHeader();

    cout        << "Calc model:     " << file.calc_model()                 << endl
         << hex << "Signature:      " << file.signature1()          << 'h' << endl
                << "Default folder: " << file.default_folder_name()        << endl
                << "Comment:        " << file.comment()                    << endl
         << dec << "Entries number: " << file.entries_number()             << endl
                << "File size:      " << file.file_size()                  << endl
         << hex << "Signature:      " << file.signature2()          << 'h' << endl
                                                                           << endl;

    file.readVariables();
    QList<TiVarEntry*> var_table = file.entries();
    for(QList<TiVarEntry*>::iterator it=var_table.begin(); it!=var_table.end(); it++)
    {
        if((*it)->isFolder())
        {
            cout << "Folder name:    " << (*it)->name()       << endl
                 << "Variable count: " << (*it)->var_number() << endl
                                                              << endl;
        }
        else
        {
            cout << hex << "Offset:          " << (*it)->offset()            << 'h' << endl
                        << "Variable name:   " << (*it)->name()              << endl
                        << "Type ID:         " << (qint16)(*it)->type_id()   << 'h' << endl
                        << "Attribute:       " << (qint16)(*it)->attribute() << 'h' << endl;
            cout << "<--" << endl;

            switch((*it)->type_id())
            {
                case TiVarEntry::String:{
                    TiStringVar *var = (TiStringVar*)(*it)->variable();

                    var->parse();
                    cout << dec << "Variable size:   " << var->size()                      << endl
                         << hex << "Signature:       " << (qint16)var->signature1() << 'h' << endl
                                << "Data:            " << var->data()                      << endl
                                << "Signature:       " << (qint16)var->signature2() << 'h' << endl
                                << "Checksum:        " << var->checksum()           << "h -- "
                                                       << var->calc_checksum()      << 'h' << endl;
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
