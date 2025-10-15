#include "Store.h"
#include <iostream>

using namespace std;

//Consturctor
Store::Store(){
    level = 1;
    rating = 0;
    revenue = 0.0;
}

//Control plater rating
void Store::updateRating(int newRating){
    rating = newRating;
}

//Control player level
void Store::updateLevel(int newLevel){
    level = newLevel;
}

//Control player revenue
void Store::updateRevenue(double newRevenue){
    revenue += newRevenue;
}

//Check if elligible for upgrade
bool checkUpdgrade(int rating, double revenue){
    //Set condtions for upgrade
    int RatingLimit = 4;
    double moneyLimit = 15.0;
    
    if (rating < RatingLimit && revenue < moneyLimit){
        return 1;
    }
}

//Control store
void Store::upgradeStore(bool val){
    if (val = 1){
        level++;
        //Add new customers from customer class
        
        cout << "Store upgraded to Level " << level << endl;

        //Reset rating 
        rating  = 0;

    }
    else{
        cout << "Upgrade conditions not met yet! Keep trying!" << endl;
    }
}

//Get
int Store::getRating(){
    return rating;
}
int Store::getLevel(){
    return level;
}
double Store::getRevenue(){
    return revenue;
}
