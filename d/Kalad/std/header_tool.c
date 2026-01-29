/*
 * /d/Kalad/std/header_tool.c
 * Purpose    : To easily add info headers to files.
 * Located    : <see above>
 * Created By : Sarr 27.Feb.97
 * Modified By: Rico 27.Feb.97
 */

inherit "/std/object";

#include "/d/Kalad/defs.h"

#define THIS_FILE   "/d/Kalad/std/header_tool.c"

void
create_object()
{
    set_name("header_tool");
    add_name("header");
    set_long("\nThis tool is to enable you to quickly put a dreaded "+
      "info header into a given file.  Obviously, you will need "+
      "to have write access to said file.  You will also need to "+
      "have the affected file's dir as your current working dir.\n"+
      "Syntax of the Tool:\n"+
      "\thead <filename>|<purpose>|<located>|<creator>|<date>"+
      "\nHere's an example:\n"+
      "\thead test.c|A test file.|/d/Kalad/|Sarr|27.Feb.97|\n\n"+
      "NOTE: You may leave a field blank by not putting an entry "+
      "between the\n      related pipes.\n\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL, "It isn't an item the merchant finds "+
      "any value in.\n");
    add_prop(OBJ_M_NO_DROP, "It isn't a good idea to drop a wiz "+
      "tool.\nIf you don't want it, destruct it.\n");

    seteuid(getuid());
}

/* Name   : query_auto_load
 * Purpose: Give a wizard the convenience of not
 *          having to clone it repeatedly.
 */
string
query_auto_load()
{
    return THIS_FILE;
}

void
init()
{
    ::init();

    add_action("do_header", "head");
}

/* Name   : do_header
 * Purpose: A wiz tool to quickly add a header to a file.
 */
int
do_header(string str)
{
    string file,
    file_name,
    purpose,
    located,
    createdby,
    date,
    header;

    notify_fail("\nError! Correct syntax is:\n"+
      "\thead <file>|<purpose>|<located>|<creator>|<date>\n\n"); 

    if(sscanf(str, "%s|%s|%s|%s|%s|", file_name,
	purpose, located, createdby, date) != 5)
	return 0;

    /* Get the working dir of the user. */
    file_name = TP->query_path() + "/" + file_name;
    notify_fail("\nError! File not found.\n"+
      "Make sure it is in your working directory.\n\n");

    file = read_file(file_name);
    if(!file)
	return 0;

    rm(file_name);

    header =  "/* \n"+
    " * " + file_name + "\n"+
    " * Purpose    : " + purpose + "\n"+ 
    " * Located    : " + located + "\n"+
    " * Created By : " + createdby + " " + date + "\n"+
    " * Modified By: \n"+
    " */ \n\n";

    write_file(file_name, header);
    write_file(file_name, file);
    write("\nFile headed: " + file_name + "\n\n");

    return 1;
}

