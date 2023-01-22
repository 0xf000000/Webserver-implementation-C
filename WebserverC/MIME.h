//
//  File.h
//  WebserverC
//
//
//

#ifndef MIME_H
#define MIME_H


extern char*  getMIMEtype(char *filename);
extern struct file_data* loadFile(char *filename);
extern void file_free(struct file_data*);


#endif /* File_h */
