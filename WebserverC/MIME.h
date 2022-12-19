//
//  File.h
//  WebserverC
//
//
//

#ifndef File_h
#define File_h

struct file_data{
    int size;
    void *data;
};

extern struct file_data* loadFile(char *filename);
extern void file_free(struct file_data*);


#endif /* File_h */
