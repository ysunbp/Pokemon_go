#include "trainer.h"
Trainer::Trainer(string name):name(name),backpack(),kunGroup(){}
string Trainer::getName() const{
	return name;
}
Backpack& Trainer::getBackpack(){
	return backpack;
}
KunGroup& Trainer::getKunGroup(){
	return kunGroup;
}
void Trainer::feedItemToKun(Item* item, Kun* kun){
	if(this->getBackpack().hasItem(item)&&this->getKunGroup().hasKun(kun)){
		kun->eatItem(item);
		this->getBackpack().removeItem(item);
		delete item;
		item=NULL;
	}
}
void Trainer::receiveNewbornKunFromProf(){
	Kun* new_kun=new Kun();
	this->getKunGroup().addKun(new_kun);
}
void Trainer::trainKunInTheWild(Kun* kun, int times){


	kun->gainExperience(100*times);
}
