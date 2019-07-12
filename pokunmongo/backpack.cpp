#include "backpack.h"
Backpack::Backpack(){
	items=NULL;
	itemCount=0;
}
Backpack::~Backpack(){
	delete []items;
	items=NULL;
	itemCount=0;

}
Item** Backpack::getItems() const{
	return items;
}
Item* Backpack::getItem(string name) const{
	for(int i=0;i<itemCount;i++){
		if(items[i]->getName()==name){
			return items[i];
		}

	}
	return NULL;
}
bool Backpack::hasItem(const Item*item) const{
	for(int i=0;i<itemCount;i++){
		if(items[i]==item){
			return true;
		}
	}return false;
}

void Backpack::addItem(Item* item){
		if(!this->hasItem(item)){
			Item** intermediate=new Item*[itemCount+1];
			for(int i=0;i<itemCount;i++){
				intermediate[i]=items[i];
			}

			intermediate[itemCount]=item;
			delete[]items;
			items=NULL;
			items=intermediate;
			itemCount+=1;
		}

	}

void Backpack::removeItem(Item* item){
	if(this->hasItem(item)){
		if(itemCount==1){
			itemCount=0;
			delete[]items;
			items=NULL;
		}
		else{
			Item** intermediate=new Item*[itemCount-1];
			for(int i=0;i<itemCount;i++){
				intermediate[i]=items[i];
				if(items[i]->getName()==item->getName()){
					continue;
				}
			}
			delete[]items;
			items=NULL;
			items=intermediate;
			itemCount-=1;
		}}
	else{
		return;
	}
}

int Backpack::getItemCount() const{
	return itemCount;
}
