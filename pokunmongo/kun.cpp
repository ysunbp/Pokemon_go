#include "kun.h"
Kun::Kun():MAX_LEVEL(100){
	name="KUN";
	hp=10;
	attack=1;
	defense=1;
	level=1;
	experience=0;
	moveList=NULL;
	moveCount=0;

}
Kun::Kun(string name):MAX_LEVEL(100){
	this->name=name;
	hp=10;
	attack=1;
	defense=1;
	level=1;
	experience=0;
	moveList=NULL;
	moveCount=0;

}
Kun::Kun(const Kun& another):MAX_LEVEL(another.MAX_LEVEL){
	this->name=another.name;
	this->hp=another.hp;
	this->attack=another.attack;
	this->defense=another.defense;
	this->level=another.level;
	this->experience=another.experience;
	this->moveCount=another.moveCount;
	moveList=new Move[moveCount];
	for(int i=0;i<moveCount;i++){
		this->moveList[i]=another.moveList[i];
	}
}
Kun::~Kun(){
	delete[]moveList;
	moveList=NULL;
}
string Kun::getName() const{
	return name;
}
void Kun::setName(string name){
	this->name=name;
}
double Kun::getHP()const{
	return hp;
}
void Kun::setHP(double HP){
	hp=HP;
}
bool Kun::isAlive()const{
	if(hp>0){
		return true;
	}
	else{
		return false;
	}
}
void Kun::heal(){
	hp=level*10;
}
double Kun::getAttack()const{
	return attack;
}
void Kun::setAttack(double attack){
	this->attack=attack;
}
double Kun::getDefense()const{
	return defense;
}
void Kun::setDefense(double defense){
	this->defense=defense;
}
int Kun::getLevel()const{
	return level;
}
bool Kun::increaseLevelTo(int level){
	if (level>MAX_LEVEL){
		return false;
	}
	else if(level<=this->level){
		return false;
	}
	else{
		int increment=level-this->level;
		for(int i=0;i<increment;i++){
		hp+=10;
		attack+=2;
		defense+=2;
		}
		experience=0;
		this->level=level;
		return true;
	}
}
double Kun::getExperience()const{
	return experience;
}
bool Kun::gainExperience(double experience){
	double total_experience=((level-1.0)*level/2)*100.0+experience+this->experience;
	/*cout<<"total experience is "<<total_experience<<endl;*/
	if(this->level>=MAX_LEVEL){return false;}
	else if(total_experience<100){
		this->experience=total_experience;
		return true;
	}
	else{
	for(int i=1;i<MAX_LEVEL;i++){
		double sum1=((1.0+i)*i/2.0)*100.0;
		double sum2=((2.0+i)*(i+1.0)/2.0)*100.0;
		int increment;
		if(sum1<=total_experience&&sum2>total_experience){
			increment=i+1-level;
			hp+=10*increment;
			attack+=2*increment;
			defense+=2*increment;
			level=i+1;
			this->experience=total_experience-sum1;
			break;
		}
	}
	/*cout<<"divide is "<<divide<<endl;*/

	/*experience=total_experience-divide*100.0;*/
	return true;
	}
}
Move* Kun::getMoveList(){
	return moveList;
}
void Kun::addMove(Move move){
	Move* intermediate=new Move[moveCount+1];
	for(int i=0;i<moveCount;i++){
		intermediate[i]=this->moveList[i];
	}
	intermediate[moveCount]=move;
	delete[]moveList;
	moveList=NULL;
	this->moveList=intermediate;
	moveCount+=1;
}
void Kun::removeAllMoves(){
	delete[]moveList;
	moveCount=0;
	moveList=NULL;
}
int Kun::getMoveCount()const{
	return moveCount;
}
void Kun::eatItem(const Item* item){
	this->attack+=item->getAttack();
	this->defense+=item->getDefense();
	this->hp+=item->getHP();
}
void Kun::eatKun(const Kun* kun){
	this->hp+=0.1*kun->hp;
	this->attack+=0.1*kun->attack;
	this->defense+=0.1*kun->defense;
	this->gainExperience(kun->level*30);
}
