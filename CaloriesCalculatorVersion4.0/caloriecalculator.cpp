#include "caloriecalculator.h"
#include "ui_caloriecalculator.h"

/*You can Activities,levels add MET values
 from here https://golf.procon.org/met-values-for-800-activities/
using this format {"Activity",{"Level",met value}} inside the ACTIVITY
*/

//Activity Initilizer List
const map<QString,map<QString,float>> CalorieCalculator::ACTIVITY = {
    {"Walking",
        {
            {"walking, 1.7mph,slowly",2.3},
            {"walking 2.5mph,moderate",2.9},
            {"walking 3.5mph,speed walk",3.8}
        }
    },
    {"Cycling",
        {
            {"bicycling stationary,very light effort",3.0},
            {"bicycling <10mph, leisure",4.0},
            {"bicycling 10mph-16mph, leisure",10.0},
            {"bicycling, mountain, uphill, vigorous",14.0},
            {"bicycling, mountain, competitive, racing",16.0}
        }
    },
    {"Running",
        {
            {"running, jog/walk combination",6.0},
            {"running, 4 mph (13 min/mile)",6.0},
            {"running, 6 mph (10 min/mile)",9.8},
            {"running, stairs, up",15.0},
            {"running, marathon",13.3}
        }
    },
    {"Rope Skipping",
        {
            {"rope jumping, slow pace, < 100 skips/min",8.8},
            {"rope jumping, slow pace, < 100 skips/min",11.8},
            {"rope jumping, fast pace, 120-160 skips/min",12.3}
        }
    },
    {"Weight Lifting",
        {
            {"general, gym/weight training combined in one visit",4.5},
            {"resistance (weight) training, squats , slow or explosive effort",5.0},
            {"resistance (weight) training, varied resistance",3.5},
            {"weight lifting, free weight, power lifting, vigorous effort",6.0}
        }
    },
    {"Swimming",
        {
            {"swimming laps, freestyle, slow, light or moderate effort",5.0},
            {"swimming, breaststroke, recreational",5.3},
            {"swimming, crawl, medium speed, ~50 yards/minute, vigorous effort",8.3},
            {"swimming laps, freestyle, fast, vigorous effort",9.8}
        }
    }
};

//Constructor
CalorieCalculator::CalorieCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalorieCalculator),caloriesBurned(0)
{
    ui->setupUi(this);//Setup the ui
    initActivityList();//initialize activity list
    initIntensityList();//initialize intensity level list
    setUpPages();//Sets pages to starting point
}
void CalorieCalculator::initActivityList()
{
    ui->activity->clear();
    for(auto const &levels : ACTIVITY)
        ui->activity->addItem(levels.first);

}
void CalorieCalculator::setUpPages()
{
    ui->mainLbl->setText("Welcome to");
    ui->nextBtn->hide();
    ui->prevBtn->hide();
    ui->pg1_btn->hide();
    ui->pg2_btn->hide();
    ui->pg3_btn->hide();
    ui->stackedWidget->setCurrentIndex(0);
}
void CalorieCalculator::initIntensityList()
{//This method shows different intensity levels based on selected activity

    QString activity = ui->activity->currentText();//Get the selected activity
    ui->intensity->clear();//First clear the QComboBox

    for(auto const &levels : ACTIVITY.at(activity))//add intensity levels based on selected activity
        ui->intensity->addItem(levels.first);
}
float CalorieCalculator::getMET()
{
    QString activity = ui->activity->currentText();//get selected activity
    QString level = ui->intensity->currentText();//get selected intensity level
    return ACTIVITY.at(activity).at(level);//get MET value based on the provided info
}
void CalorieCalculator::calculate_opt1()
{//Calculates the total Calories Burned
    float weight = ui->weight->text().toFloat();
    if(ui->weightUnit->currentText()!="kg")
    {
        weight = weight/2.2;
    }
    float duration = ui->hours->value()*60 + ui->minutes->value() + ui->seconds->value()/60;
    this->caloriesBurned = duration*(getMET())*(3.5*weight)/200;
    ui->calBurnt->setText(QString::number(this->caloriesBurned));
    viewPage(5);
}

void CalorieCalculator::calculate_opt2()
{
    int age = ui->age_2->text().toFloat();
    float weight = ui->weight_2->text().toFloat();
    if(ui->weightUnit_2->currentText()=="lbs")
    {
        weight = weight/2.2;
    }
    QString gender = ui->gender_2->currentText();
     float duration = ui->hours_2->value()*60 + ui->minutes_2->value() + ui->seconds_2->value()/60;
    float bpm = ui->rate_2->text().toFloat();
    if(gender == "Male"){
        this->caloriesBurned = ((age*0.2017) + (weight * 0.1988) + (bpm * 0.6309) - 55.0969)* duration/4.184;
    }
    else{
        this->caloriesBurned = ((age*0.074) - (weight * 0.1263) + (bpm * 0.4472) - 20.4022)* duration/4.184;
    }
    ui->calBurnt->setText(QString::number(this->caloriesBurned));
}


void CalorieCalculator::calculate_opt3()
{
    int age = ui->age_3->text().toFloat();
    float weight = ui->weight_3->text().toFloat();
    if(ui->weightUnit_3->currentText()=="lbs")
    {
        weight = weight/2.2;
    }
    QString gender = ui->gender_3->currentText();
     float duration = ui->hours_3->value()*60 + ui->minutes_3->value() + ui->seconds_3->value()/60;
    float bpm = ui->rate_3->text().toFloat();
    float vo2 = ui->vo_3->text().toFloat();
    if(gender == "Male"){
        this->caloriesBurned = ((-95.7735 + (0.634 * bpm) + (0.404 * vo2) + (0.394 * weight) + (0.271* age))/4.184) * duration;
    }
    else{
        this->caloriesBurned = ((-59.3954 + (0.45 * bpm) + (0.380 * vo2) + (0.103 * weight) + (0.274 * age))/4.184) * duration;
    }
    ui->calBurnt->setText(QString::number(this->caloriesBurned));
}

CalorieCalculator::~CalorieCalculator()
{
    delete ui;
}


void CalorieCalculator::on_nextBtn_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    if(index==2)
    {
        if(ui->opt1->isChecked())
            viewPage(1);
        else if(ui->opt2->isChecked())
            viewPage(2);
        else if(ui->opt3->isChecked())
            viewPage(3);
    }
    else{
        if(ui->opt1->isChecked())
            calculate_opt1();
        else if(ui->opt2->isChecked())
            calculate_opt2();
        else if(ui->opt3->isChecked())
            calculate_opt3();
        viewPage(5);
    }
}

void CalorieCalculator::formatPageButtons(int index){
    ui->pg1_btn->setStyleSheet("background-color: white;color: black;border: 2px solid #3498db;");
    ui->pg2_btn->setStyleSheet("background-color: white;color: black;border: 2px solid #3498db;");
    ui->pg3_btn->setStyleSheet("background-color: white;color: black;border: 2px solid #3498db;");
    switch(index){
        case 1:
            ui->pg1_btn->setStyleSheet("background-color: #3498db;color: white;");
            break;
        case 2:
            ui->pg2_btn->setStyleSheet("background-color: #3498db;color: white;");
            break;

        case 3:
            ui->pg3_btn->setStyleSheet("background-color: #3498db;color: white;");
            break;
    }
}
void CalorieCalculator::viewPage(int pgno)
{
    switch(pgno){
        case 1:
            ui->prevBtn->show();
            ui->nextBtn->show();
            ui->stackedWidget->setCurrentIndex(3);
            formatPageButtons(2);
            break;
        case 2:
            ui->prevBtn->show();
            ui->nextBtn->show();
            ui->stackedWidget->setCurrentIndex(4);
            formatPageButtons(2);
            break;
        case 3:
            ui->prevBtn->show();
            ui->nextBtn->show();
            ui->stackedWidget->setCurrentIndex(5);
            formatPageButtons(2);
            break;
        case 4:
            ui->prevBtn->show();
            ui->nextBtn->hide();
            ui->stackedWidget->setCurrentIndex(6);
            formatPageButtons(3);
            break;
        case 5:
            formatPageButtons(3);
            ui->nextBtn->hide();
            ui->stackedWidget->setCurrentIndex(6);
    }

}

void CalorieCalculator::reset()
{
    ui->weight->setText("");
    ui->weight_2->setText("");
    ui->weight_3->setText("");
    ui->age_2->setText("");
    ui->age_3->setText("");
    ui->hours->setValue(0);
    ui->hours_2->setValue(0);
    ui->hours_3->setValue(0);
    ui->minutes->setValue(0);
    ui->minutes_2->setValue(0);
    ui->minutes_3->setValue(0);
    ui->seconds->setValue(0);
    ui->seconds_2->setValue(0);
    ui->seconds_3->setValue(0);
    ui->rate_2->setText("");
    ui->rate_3->setText("");
    ui->vo_3->setText("");
    caloriesBurned = 0;
    ui->calBurnt->setText("0.0");
}

void CalorieCalculator::on_pushButton_clicked()
{
    ui->mainLbl->setText("Calorie Calculator");
    ui->stackedWidget->setCurrentIndex(1);
}

void CalorieCalculator::on_contBtn_clicked()
{
    ui->nextBtn->click();



    ui->pg1_btn->show();
    ui->pg2_btn->show();
    ui->pg3_btn->show();
    ui->prevBtn->show();
    ui->nextBtn->show();
    formatPageButtons(1);
    ui->stackedWidget->setCurrentIndex(2);
}



void CalorieCalculator::on_opt1_stateChanged(int arg1)
{
    if(ui->opt1->isChecked()){
        ui->opt2->setCheckState(Qt::CheckState::Unchecked);
        ui->opt3->setCheckState(Qt::CheckState::Unchecked);
    }
}

void CalorieCalculator::on_opt2_stateChanged(int arg1)
{
    if(ui->opt2->isChecked()){
        ui->opt1->setCheckState(Qt::CheckState::Unchecked);
        ui->opt3->setCheckState(Qt::CheckState::Unchecked);
    }
}

void CalorieCalculator::on_opt3_stateChanged(int arg1)
{
    if(ui->opt3->isChecked()){
        ui->opt1->setCheckState(Qt::CheckState::Unchecked);
        ui->opt2->setCheckState(Qt::CheckState::Unchecked);
    }
}

void CalorieCalculator::on_prevBtn_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    if(index==2)
    {
        ui->pg1_btn->hide();
        ui->pg2_btn->hide();
        ui->pg3_btn->hide();
        ui->prevBtn->hide();
        ui->nextBtn->hide();
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(index == 6){
        if(ui->opt1->isChecked())
            viewPage(1);
        else if(ui->opt2->isChecked())
            viewPage(2);
        else if(ui->opt3->isChecked())
            viewPage(3);
        ui->calBurnt->setText("0.0");
        caloriesBurned = 0;
    }
    else{
        ui->stackedWidget->setCurrentIndex(2);
        formatPageButtons(1);
        reset();
    }
}

void CalorieCalculator::on_weightUnit_2_currentTextChanged(const QString &arg1)
{
    QString weight = ui->weight_2->text();
    double val = weight.toDouble();
    if(val==0)
        return;
    if(ui->weightUnit_2->currentText()=="kg")
    {
        val = val /2.2;
        weight = QString::number(val);
        ui->weight_2->setText(weight);
    }
    else
    {
        val = val*2.2;
        weight = QString::number(val);
        ui->weight_2->setText(weight);
    }
}

void CalorieCalculator::on_weightUnit_3_currentTextChanged(const QString &arg1)
{
    QString weight = ui->weight_3->text();
    double val = weight.toDouble();
    if(val==0)
        return;
    if(ui->weightUnit_3->currentText()=="kg")
    {
        val = val /2.2;
        weight = QString::number(val);
        ui->weight_3->setText(weight);
    }
    else
    {
        val = val*2.2;
        weight = QString::number(val);
        ui->weight->setText(weight);
    }
}

void CalorieCalculator::on_weightUnit_currentTextChanged(const QString &arg1)
{
    QString weight = ui->weight->text();
    double val = weight.toDouble();
    if(val==0)
        return;
    if(ui->weightUnit->currentText()=="kg")
    {
        val = val /2.2;
        weight = QString::number(val);
        ui->weight->setText(weight);
    }
    else
    {
        val = val*2.2;
        weight = QString::number(val);
        ui->weight->setText(weight);
    }
}

//void CalorieCalculator::on_resUnit_currentTextChanged(const QString &arg1)
//{
//    if(ui->resUnit->currentText()=="kcal")
//        ui->calBurnt->setText(QString::number(this->caloriesBurned));
//    if(ui->resUnit->currentText()=="cal")
//        ui->calBurnt->setText(QString::number(this->caloriesBurned*1000));
//    if(ui->resUnit->currentText()=="kJ")
//        ui->calBurnt->setText(QString::number(this->caloriesBurned*4.184));
//    if(ui->resUnit->currentText()=="J")
//        ui->calBurnt->setText(QString::number(this->caloriesBurned*4184));
//}

void CalorieCalculator::on_activity_activated(int index)
{
    QString activity = ui->activity->currentText();//Get the selected activity
    ui->intensity->clear();//First clear the QComboBox

    for(auto const &levels : ACTIVITY.at(activity))//add intensity levels based on selected activity
        ui->intensity->addItem(levels.first);
}
