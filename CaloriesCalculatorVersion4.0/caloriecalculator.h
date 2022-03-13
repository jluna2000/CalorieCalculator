#ifndef CALORIECALCULATOR_H
#define CALORIECALCULATOR_H

#include <QMainWindow>
#include <map>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class CalorieCalculator; }
QT_END_NAMESPACE

class CalorieCalculator : public QMainWindow
{
    Q_OBJECT

public:
    CalorieCalculator(QWidget *parent = nullptr);
    void initActivityList();
    void initIntensityList();
    float getMET();
    void calculate_opt1();
    void calculate_opt2();
    void calculate_opt3();
    void calculateMET();
    void viewPage(int);
    void formatPageButtons(int);
    void setUpPages();
    ~CalorieCalculator();

private slots:
    void on_nextBtn_clicked();

    void on_pushButton_clicked();

    void on_contBtn_clicked();

    void on_opt1_stateChanged(int arg1);

    void on_opt2_stateChanged(int arg1);

    void on_opt3_stateChanged(int arg1);

    void on_prevBtn_clicked();

    void on_weightUnit_currentTextChanged(const QString &arg1);

    void on_weightUnit_2_currentTextChanged(const QString &arg1);

    void on_weightUnit_3_currentTextChanged(const QString &arg1);

    void reset();

//    void on_resUnit_currentTextChanged(const QString &arg1);

    void on_activity_activated(int index);

private:
    Ui::CalorieCalculator *ui;
    double caloriesBurned;
    static const map<QString,map<QString,float>> ACTIVITY;
};
#endif // CALORIECALCULATOR_H
