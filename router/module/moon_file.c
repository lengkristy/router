#include "moon_file.h"

/**
 * function desc:
 *      Read only open existing file,and invoke moon_close_file function to close it after use.
 * params:
 *      p_moon_file:the pointer of _moon_file struct
 *      file_path_name:file full path name.
 * return:
 *      sucess return true and p_moon_file return the pointer of _moon_file struct,failed return false and p_moon_file is null
 */
bool moon_open_file_for_read(moon_file_ptr p_moon_file,char* p_file_path_name)
{
    if(p_moon_file == NULL)
    {
        return false;
    }
    p_moon_file->file_ptr = fopen(p_file_path_name,"r");
    if(p_moon_file->file_ptr == NULL)
    {
        return false;
    }
    fseek(p_moon_file->file_ptr, 0L, SEEK_END);
    p_moon_file->file_size = ftell(p_moon_file->file_ptr);  
    return true;
}

/**
 * function desc:
 *      Read a row of data from a file.
 * params:
 *      p_moon_file:the pointer of _moon_file struct
 *      out_data:the data for read
 * return:
 *      Returns the length actually read,return -1 if read to the end.
 */
int moon_read_line(moon_file_ptr p_moon_file,_out_ char* out_data)
{
    fgets(out_data,0000,p_moon_file->file_ptr);
    return 0;
}

/**
 * function desc:
 *      close file that has be opened
 * params:
 *      p_moon_file:the pointer of _moon_file struct
 * return:
 *      sucess return true,failed return false
 */
bool moon_close_file(moon_file_ptr p_moon_file)
{
    if(p_moon_file == NULL)
    {
        return true;
    }
    if(fclose(p_moon_file->file_ptr))
        return false;
    return true;
}