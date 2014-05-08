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

#define HEADER_SIZE 512
#define DATA_START (257 * 512)
#define ALLOCATION_START HEADER_SIZE
#define ALLOCATION_NUM 256
#define SLOT_SIZE 512
#define SLOT_NUM 65536 

union ShortByteUnion{
	unsigned short asShort;
	unsigned char asByte[2];
}

/**
*	Slot
*	Kelas yang memodelkan data slot pada CCFS
*/

class Slot
{
public:
	string name; 		// nama file2
	char atribut;		// atribut file
	short tgl_buat;		// tgl file dibuat
	short tgl_modif;	// tgl file dimodifikasi terakhir
	short indexDP;		// index pertama Data Pool
	int size;			// ukuran file
	char content[480];	// isi file

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
	ShortByteUnion Allocation[SLOT_NUM]; // allocation table ke seluruh data pool.

	string filename;		// nama filesystem
	int kapasitas;			// kapasitas filesystem
	int available;			// jumlah slot yang masih kosong
	int firstempty;			// slot pertama yang masih kosong
	time_t mount_time;		// waktu mounting, diisi di konstruktor
	
	/* konstruktor & destruktor */
	CCFS();
	~CCFS();
	
	/* buat file simple.fs baru */
	void create(string filename);
	
	/* baca file simple.fs */
	void load(string filename);

	/* tulis header filesystem ke file simple.fs */
	void writeHeader();
	
	/* tulis data slot ke-index pada file simple.fs di posisi yang sesuai */
	void writeFile(int index);
	
	/* tulis allocation table ke file ccfs */
	void writeAllocation();	
};


#endif