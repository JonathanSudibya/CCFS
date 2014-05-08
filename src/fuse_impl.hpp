#ifndef FUSE_IMPL_HPP
#define FUSE_IMPL_HPP

/** Header implementasi fungsi-fungsi fuse */

// pakai versi 26
#define FUSE_USE_VERSION 26

#include <fuse.h>
#include "ccfs.hpp"

/* get attribute */
int ccfs_getattr(const char* path, struct stat* stbuf);

/* open file */
int ccfs_open(const char* path, struct fuse_file_info* fi);

/* mknod, untuk membuat file */
int ccfs_mknod(const char *path, mode_t mode, dev_t dev);

/* membaca direktori */
int ccfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);

/* untuk mengubah panjang suatu file, biasa digunakan saat penulisan pertama */
int ccfs_truncate(const char* path, off_t size);

/* membaca file */
int ccfs_read(const char* path, char *buf, size_t size, off_t offset, struct fuse_file_info* fi);

/* menulis file */
int ccfs_write(const char* path, const char *buf, size_t size, off_t offset, struct fuse_file_info* fi);

/* rename/cut file */
int ccfs_rename(const char* from, const char* to);

/* hapus file */
int ccfs_unlink(const char* path);

#endif
