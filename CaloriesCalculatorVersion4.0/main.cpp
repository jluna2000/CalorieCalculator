#include "caloriecalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalorieCalculator w;
    w.show();
    return a.exec();
}
