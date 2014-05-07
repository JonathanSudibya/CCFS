#include <stdexcept>

#include "ccfs.hpp"

using std::runtime_error;

/******* kelas Slot *******/

/* kostruktor */
Slot::Slot() : name(""), size(0){
	memset(content,0,480);
}

/* copy buffer ke content pada posisi ke-offset, sebanyak length */ 
void Slot::setContent(const char* buffer, int length, int offset){
	memcpy(content + offset, buffer, (size_t) length);
}

/* copy content ke buffer, mulai dari posisi ke-offset, sebanyak length */
void Slot::getContent(char* buffer, int length, int offset){
	memcpy(buffer, content + offset, (size_t) length);
}

/* tulis data slot ke file ccfs */
void Slot::writeToFile(fstream& handle){

	// maksimum panjang nama file 21 karakter
	int fname_len = name.length() < 21 ? name.length() : 21;
	
	// inisialisasi buffer untuk penulisan slot
	char data[SLOT_SIZE];
	memset(data, 0, SLOT_SIZE);
	
	// set nama file
	memcpy(data, name.c_str(), fname_len);
	
	// set atribut file
	data[22] = atribut;

	// set tgl_buat file
	data[23] = (unsigned char) tgl_buat;
	data[24] = (unsigned char) tgl_buat >> 8;

	// set tgl_modif file
	data[25] = (unsigned char) tgl_modif;
	data[26] = (unsigned char) tgl_modif >> 8;

	// set index pertama data pool
	data[28] = (unsigned char) indexDP >> 8;
	data[27] = (unsigned char) indexDP ;
	// set ukuran file
	data[29] = (unsigned char) size;
	data[30] = (unsigned char) size >> 8;
	data[31] = (unsigned char) size >> 16;
	data[32] = (unsigned char) size >> 24;
	
	// set isi file
	memcpy(data+33, content, 480);
	
	// tulis slot ke simple.fs
	handle.write(data, SLOT_SIZE);
	handle.flush();
}

void Slot::readFromFile(fstream& handle){
	char buffer[SLOT_SIZE],strbuf[22];

	// baca 512 byte dari data ke buffer
	handle.read(buffer, SLOT_SIZE);

	// ambil string dari nama file dari buffer
	memcpy(strbuf,buffer,22);
	name = string(strbuf);

	//ambil atribut
	atribut = (unsigned char) buffer[22];

	// set tgl_buat
	tgl_buat = (unsigned char) buffer[24];
	tgl_buat = tgl_buat << 8;
	tgl_buat = tgl_buat + (unsigned char) buffer[23];

	//set tgl_modif
	tgl_modif = (unsigned char) buffer[26];
	tgl_modif = tgl_modif << 8;
	tgl_modif = tgl_modif + (unsigned char) buffer[25];

	// ambil indeks pertama data pool
	indexDP = (unsigned char) buffer[28];
	indexDP = indexDP << 8;
	indexDP = indexDP + (unsigned char) buffer[27];

	// ambil size dari buffer
	size = (unsigned char) buffer[32];
	size = size << 8;
	size = size + (unsigned char) buffer[31];
	size = size << 8;
	size = size + (unsigned char) buffer[30];
	size = size << 8;
	size = size + (unsigned char) buffer[29];

	// ambil isi file dari buffer
	setContent(buffer+33,490,0);
}

/* cek apakah slot kosong */
bool Slot::isEmpty()
{
	return name.length() == 0;
}

/****** kelas CCFS ******/

/* konstruktor */
CCFS::CCFS(){
	time(&mount_time);
}

/* destruktor */
CCFS::~CCFS(){
	handle.close();
}

/* buat file ccfs baru */
void CCFS::create(string filename){
	/* buka file dengan mode input-output,binary and truncate (untuk membuat file baru) */
	handle.open(filename.c_str(), fstream::in | fstream::out | fstream::binary | fstream::trunc);

	/* inisialisasi header */
	available = SLOT_NUM;
	firstEmpty = 0;
	writeHeader();

	/* inisialisasi allocation table */


	/* inisialisasi slot dengan data kosong */
	char buffer[SLOT_SIZE];
	memset(buffer, 0, SLOT_SIZE);
	for (int i = 0; i < SLOT_NUM; i++){
		handle.write(buffer, SLOT_SIZE);
	}
	
	handle.flush();

}

/* baca file ccfs */
void CCFS::load(string filename){

	/* buka file dengan mode input-output, dan binary */
	handle.open(filename.c_str(), fstream::in | fstream::out | fstream::binary);
	
	/* cek apakah file ada */
	if (!handle.is_open()){
		handle.close();
		throw runtime_error("File not found: " + filename);
	}

	char header[HEADER_SIZE];

	/* baca buffer header */
	handle.read(header,HEADER_SIZE);

	/* cek magic string */
	if (string(header,4) != "CCFS"){
		handle.close();
		throw runtime_error("File not valid");
	}
}