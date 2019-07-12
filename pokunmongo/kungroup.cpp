#include "kungroup.h"
KunGroup::KunGroup(){
	kuns=NULL;
	kunCount=0;
}
KunGroup::~KunGroup(){
	delete[]kuns;
	kuns=NULL;
}
Kun** KunGroup::getKuns()const{
	return kuns;
}
Kun* KunGroup::getKun(string name) const{
	for(int i=0;i<kunCount;i++){

		if(kuns[i]->getName()==name){
			return kuns[i];
		}
	}return NULL;
}
bool KunGroup::hasKun(Kun* kun) const{
	if(kunCount==0){
		return false;
	}
	else{
	for(int i=0;i<kunCount;i++){

		if(kuns[i]==kun){
			return true;
		}
	}return false;
}}
void KunGroup::addKun(Kun* kun){
	if(!this->hasKun(kun)){
		Kun** intermediate=new Kun*[this->kunCount+1];
		for(int i=0;i<kunCount;i++){
			intermediate[i]=kuns[i];
		}
		intermediate[kunCount]=kun;
		delete[]kuns;
		kuns=NULL;
		kuns=intermediate;
		kunCount+=1;
	}
}
void KunGroup::removeKun(Kun* kun){
	if(this->hasKun(kun)){
		if(kunCount==1){
			kunCount=0;
			delete[]kuns;
			kuns=NULL;
		}
		else{
		Kun** intermediate=new Kun*[this->kunCount-1];
		for(int i=0;i<kunCount;i++){
			intermediate[i]=kuns[i];
			if(kuns[i]->getName()==kun->getName()){
				continue;
			}
		}
		delete[]kuns;
		kuns=NULL;
		kuns=intermediate;
		kunCount-=1;
	}}
	else{
		return;
	}
}
int KunGroup::getKunCount() const{
	return kunCount;
}
