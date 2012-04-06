#include <QApplication>
#include <iostream>
#include "tifile.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cerr << argv[0] << " expects one argument." << endl;
        return EXIT_FAILURE;
    }

    try {
        TiFile file(argv[1]);
    } catch(exception const& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    };

    cout        << file.calc_model()          << endl
         << hex << file.signature1()          << endl
                << file.default_folder_name() << endl
                << file.comment()             << endl
         << hex << file.entries_number()      << endl
         << hex << file.file_size()           << endl
         << hex << file.signature2()          << endl;

    return EXIT_SUCCESS;
//    QApplication app(argc, argv);

//    return app.exec();
}
