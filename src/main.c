#include <stdio.h>
#include <stdlib.h>
char *readSource(FILE *fp, size_t filesize){
    char *buffer = malloc(filesize+1);
    if(buffer==NULL){
        perror("buffer");
        return NULL;
    }
    size_t bytesRead = fread(buffer,1,filesize,fp);
    if(bytesRead!=filesize){
        fprintf(stderr,"all bytes not read- later make readAll func");
        free(buffer);
        return NULL;
    }
    buffer[filesize]='\0'; //stringify 
    return buffer;
}

int main(int argc, char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"usage: %s <source-file>\n", argv[0]);
        return 1;
    }
    char *filepath = argv[1];
    FILE *fp=  fopen(filepath,"r");
    if(!fp){
        perror("fopen");
        return 1;
    }
    fseek(fp,0,SEEK_END);
    long filesize = ftell(fp); // func signature is long ftell(FILE *stream) so we store its result in long 
    if(filesize<0){
        perror("ftell");
        return 1;
    }
    size_t size =(size_t)filesize; // now we can convert to size_t and use everywhere 
    rewind(fp);
    char *source = readSource(fp,size);
    fclose(fp);
    if(source ==NULL){
        return 1;
    }
    fputs(source,stdout);
    free(source);
    return 0;
}
