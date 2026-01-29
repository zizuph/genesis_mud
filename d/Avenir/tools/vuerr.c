// file name:    ~Avenir/tools/vuerr.c
// creator(s):   Lord Cirion, March 1997
// last update:  
// purpose:      Toolsoul to allow the quick examination of errors
//               in code.
// note:
// bug(s):
// revision:

#pragma strict_types
#pragma save_binary

#include <macros.h>    /* MASTER_OB, etc      */
#include <cmdparse.h>  /* FIND_STR_IN_OBJECT  */
#include <options.h>

#define RELPATH   "/"

// #define LPLOG     RELPATH + "lplog"
#define LPLOG   "/d/" + SECURITY->query_wiz_dom(this_player()->query_name())   \
              + "/log/errors"

inherit "/cmd/std/tracer_tool_base";

string
get_soul_id()
{
    return "Cirion's Error Viewer";
}

int
query_tool_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    return ([
             "vuerr" : "vuerr",
            ]);
}

int
vuerr(string str)
{
    int i, line, last_line, index, start, banner_len;
    string file, error, entry, buggy, newfile, *lines, msg, banner = "";

    notify_fail("Failed.\n");

    // Get the number of lines in the lplog
    while(read_file(LPLOG, i, 1) && ++i)
       ;

    write(LPLOG + ": " + i + " lines.\n");


    notify_fail("Could not find standard error format.\n");
    while(!strlen(error) || !strlen(file) || !line)
    {
        if(!i)
           return 0;

        file = "";
        error = "";
        line = 0;

        entry = read_file(LPLOG, i--, 1);

        if(strlen(entry))
           sscanf(entry, "%s line %d:%s", file, line, error);
    }

    // Now find the first error in that sequence
    newfile = file;
    last_line = line + 1;

    index = i;

    while(newfile == file && last_line >= line && i--)
    {
        if(!i)
           return 0;

        last_line = line;

        entry = read_file(LPLOG, i, 1);
        newfile = "";
        line = 0;
        error = "";

        sscanf(entry, "%s line %d:%s", newfile, line, error);

        write("Found: " + entry + "\n");

        if(strlen(newfile) && strlen(error) && line && line <= last_line)
            index = i;
    }

    index++;
    entry = read_file(LPLOG, index, 1);

    file = "";
    error = "";
    line = 0;

    sscanf(entry, "%s line %d:%s", file, line, error);

    msg = "Error in " + RELPATH + file + " line " + line + ": \""
        + implode(explode(error, "\n"), "") + "\"";

    banner_len = MIN(strlen(msg), (this_player()->query_option(OPT_SCREEN_WIDTH) - 1));

    for(i=0;i<banner_len; i++)
       banner += "-";

    write(banner + "\n");
    write(msg + "\n");
    write(banner + "\n");

    // Now show the part of the file that is buggy
    start = MAX(0, line - 10);
    lines = explode(read_file(RELPATH + file, start, 20), "\n");

    for(i = 0; i < sizeof(lines); i++)
      write((i + start == line ? "*" : " ")
         + (i + start) + " " + lines[i] + "\n");

    write(banner + "\n");

    return 1;
}
