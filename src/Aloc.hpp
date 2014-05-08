#ifndef ALOC_H
#define ALOC_H

using namespace std;
class Aloc{
	short Available;
	short[] Allocation;
	public void SetAloc(short index,short nextindex);
	public short GetAloc(short index);
	public void SearchAvailable();
};
#endif

