#include "widget.h"
#include <QApplication>


// void *operator new(size_t size){
//     void *ptr = malloc(size);
//     if(ptr == nullptr){
//         throw std::bad_alloc();
//     }
//     // printf("new: ptr = %p,size = %zd\n",ptr,size);
//     qDebug()<<"new: ptr "<<ptr<<"size = "<<size;
//     return ptr;
// }

// void operator delete(void *ptr) noexcept{
//     // printf("delete :ptr = %p\n",ptr);
//     qDebug()<<"delete : ptr = "<<ptr;
//     free(ptr);
// }
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
