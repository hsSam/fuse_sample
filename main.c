#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

static int do_getattr(const char *path, struct stat *st) {
    printf("[getattr] Called\n");
    printf("\tAttributes of %s requested\n", path);

    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time(NULL);
    st->st_mtime = time(NULL);

    if(strcmp(path, "/") == 0)
    {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    }
    else
    {
        st->st_mode = S_IFREG | 0644;
        st->st_nlink = 1;
        st->st_size = 1024;
    }

    return 0;
}

static int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    printf("--> Getting the list of files of %s\n", path);
    filler(buffer, ".", NULL, 0);
    filler(buffer, "..", NULL,  0);

    if(strcmp(path, "/") == 0)
    {
        filler(buffer, "file54", NULL, 0);
        filler(buffer, "file349", NULL, 0);
    }

    return 0;
}

static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("--> trying to read %s, %u, %u\n", path, offset, size);
    char file54Text[] = "hello 54\n1234\n5678";
    char file349Text[] = "hello 349\n1234\n5678";
    char *selectedText = NULL;

    if(strcmp(path, "/file54") == 0)
    {
        selectedText = file54Text;
    }
    else if(strcmp(path, "/file349") == 0)
    {
        selectedText = file349Text;
    }else
    {
        return -1;
    }

    memcpy(buffer, selectedText + offset, size);
    return strlen(selectedText) - offset;
}

static struct fuse_operations operations = {
        .getattr = do_getattr,
        .readdir = do_readdir,
        .read = do_read,
};

int main(int argc, char *argv[])
{
    printf("hello world!\n");
    printf("time: %d\n", time(NULL));

    return fuse_main(argc, argv, &operations, NULL);
}