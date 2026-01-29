/* grep command
 *
 *    -- based on Centove's old code but heavily updated and added onto.
 *
 *    --= Lucius
 */

#pragma no_clone
#pragma strict_types

#include <filepath.h>

static int flag = 0;
static string where = "";
static string *file_text = ({ });

static void grep_file(string pattern, string file);
static void scan_file(string pattern, string file, int i);

void create()
{
    seteuid( getuid( this_interactive() ) );
}

 /*
  * grep information in files
  */
static void
grep_file(string pattern, string file)
{
    int i, size;

    if ((size = file_size(file)) < 1)
        return;

    file_text += ({"Scanning "+ file +" for <"+ pattern +">, "+
        size + " bytes\n" });

    if (size > 2000)
        size = size / 2000;
    else
        size = 1;

    for( i = 0; i < size + 1; i++ )
        scan_file(pattern, file, i);

    return;
}


static void
scan_file(string pattern, string file, int i)
{
    int j, sz;
    string s, *read;

    if (!strlen(s = read_file(file, i*100, 100)))
        return;

    read = explode(s, "\n");
    for( j=0, sz=sizeof(read); j < sz; j++ )
    {
        if( !sscanf(read[j], "%s"+ pattern +"%s", s, s) )
            continue;

        if( flag )
            file_text += ({ "Line "+ (i * 100 + j) +": "+ read[j] +"\n" });
        else
            file_text += ({ "Found pattern in line "+ (i * 100 + j) +
                ", File:"+ file +"\n" });
    }
}

public int
main(string str)
{
    int      i, sz;
    string   temp, path, pattern, file, *split, *array;

    notify_fail("Please do grep [-l] <pattern> <file> [> <filename>]\n");
    if (!str)  return 0;

    file_text = ({ });
    where = "";
    flag = 0;

    if( sscanf(str, "%s > %s", temp, where ) )
    {
        str = temp;
        if( sizeof( array = explode(where + "/", "/") ) < 2 )
            where = this_player()->query_path() +"/"+ where;

        where = FTPATH(this_player()->query_path(), where);
    }

    if( str[0..1] == "-l" )
    {
        flag = 1;
        str = str[3..];
    }
    array = explode(str, " ");

    if ((sz = sizeof(array)) < 2)
        return 0;

    file    = array[sz-1];
    array  -= ({ file });
    pattern = implode(array, " ");

    if (!strlen(file))
        return 0;

    file = TPATH(this_player()->query_real_name(), file);

    if (file[0] != '/')
        file = this_player()->query_path()+"/"+file;

    if (file[strlen(file)-1] == '*')
    {
        array = get_dir(file);
        split = explode(file, "/");
        file  = implode(split[0..sizeof(split)-2],"/") + "/";
        if (file[0] != '/')
            file = "/" + file;
    }
    else
    {
        if (file_size(file) < 1)
        {
            notify_fail("No such file.\n");
            return 0;
        }
        array = ({ file });
        file = "";
    }

    if (!(sz = sizeof(array)))
    {
        notify_fail("No files found.\n");
        return 0;
    }

    for( i = 0, sz =sizeof(array); i < sz; i++)
        grep_file(pattern, file + array[i]);

    if( strlen(where) && write_file( where, implode( file_text, "" ) ) )
        write("Operation complete, results printed out to: "+ where +"\n");
    else
        this_player()->more( implode( file_text, "" ) );

    file_text = ({ });
    where = "";
    flag = 0;
    return 1;
}
