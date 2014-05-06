#ifndef CCFS_HPP
#define CCFS_HPP

//deklarasi lib standar
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>

using std::string;
using std::fstream;

/** deklarasi konstanta ccfs **/

#define HEADER_SIZE 8
#define DATA_START HEADER_SIZE
#define SLOT_SIZE 128
#define SLOT_NUM 255

/**
*	Slot
*	Kelas yang memodelkan data slot pada CCFS
*/

class Slot
{
public:
	string name; 		// nama file	
	int size;			// ukuran file
	char content[100];	// isi file

	/** konstruktor */
	Slot();

	/** copy buffer ke content pada posisi ke-offset,sebanyak length */
	void setContent(const char* buffer,int length,int offset);

	/** copy content ke buffer, mulai dari posisi ke-offset, sebanyak length */
	void getContent(char* buffer, int length, int offset);

	/* tulis data slot ke file ccfs */
	void writeToFile(fstream& handle);
	
	/* tulis baca data slot ke file ccfs */
	void readFromFile(fstream& handle);
	
	/* cek apakah slot kosong */
	bool isEmpty();
};

/**
*	ccfs
*	Kelas untuk model file CCFS
*/
class CCFS
{
private:
	fstream handle;			// file simple.fs
	
public:
	Slot files[SLOT_NUM]; 	// data seluruh slot file yang ada
	
	int available;			// jumlah slot yang masih kosong
	int firstEmpty;			// slot pertama yang masih kosong
	time_t mount_time;		// waktu mounting, diisi di konstruktor
	
	/* konstruktor & destruktor */
	SimpleFS();
	~SimpleFS();
	
	/* buat file simple.fs baru */
	void create(string filename);
	
	/* baca file simple.fs */
	void load(string filename);

	/* tulis header filesystem ke file simple.fs */
	void writeHeader();
	
	/* tulis data slot ke-index pada file simple.fs di posisi yang sesuai */
	void writeFile(int index);
	
	
};

#endif