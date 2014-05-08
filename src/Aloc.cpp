#include "Aloc.hpp"

void Aloc::SetAloc(short index, short nextindex){
	Allocation[index] = nextindex;
}

short Aloc::GetAloc(short index){
	return Allocation[index];
}

void Aloc::SearchAvailable(){
	int i=0;
	while((i<SLOT_SIZE)&&(Allocation[i] != 0)){
		i++;
	}
	Available = i;
}