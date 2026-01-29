/*
 * copy_file.c
 *
 * A generic routine to copy text files with a size up to 50000 bytes. That is
 * the general gamedriver defined limit for reading and writing chunks of data.
 *
 * Created by Mercade, September 7, 2003.
 *
 * EXAMPLE: copy_file("/d/Domain/dir1/file1", "/d/Domain/dir2/file2")
 *
 * NOTICE : This routine overwrites existing files without warning.
 */

#define FILE_SIZE_LIMIT 50000

/*
 * Function name: copy_file
 * Description  : Will copy a text file with a size up to 50000 bytes. That is
 *                the general gamedriver defined limit for reading and writing
 *                chunks of data.
 *                Note that if the destination path is a directory, nothing is
 *                copied. If the destination file exists, it is overwritten.
 * Arguments    : string source - the full path to the source file.
 *                string dest - the full path to the destination file.
 * Returns      : int 1/0 - success/failure.
 */
int
copy_file(string source, string dest)
{
    int    size;
    string text;

    /* Make sure the source file is a file and has a size. */
    switch(size = file_size(source))
    {
    /* -2 means dir, -1 file doesn't exist. */
    case -2 .. -1:
        return 0;
    /* No length means we don't have to read. */
    case 0:
        text = "";
        break;
    /* If the file exceeds the limit, we don't copy. */
    default:
        if (size >= FILE_SIZE_LIMIT)
        {
            return 0;
        }
        /* Read the source, if we can. */
        catch(text = read_file(source));
        if (!strlen(text))
        {
            return 0;
        }
    }

    /* Make sure the destination doesn't exist. */
    switch(size = file_size(dest))
    {
    /* If it's a dir, we don't try to put the file in there for now. */
    case -2:
        return 0;
    /* This is the way we like it. */        
    case -1:
        break;
    /* There's a file, destroy it first. */
    default:
        catch(rm(dest));
    }

    /* Write the text to the destination file. */
    return write_file(dest, text);
}
