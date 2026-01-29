/*
 * A standard book used in the library of Solamnian Knights
 * Made by Nick
 * Updated for the new std/library by Aridor 12/96
 */

inherit "/std/scroll";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <options.h>
#include "lib.h"

string file;
string bname;
string libr;

void
create_scroll()
{
    set_name("book");
    add_name("lib_book");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
}

/*
 * Function name: read_it
 * Description:   Perform the actual read
 */
void
read_it(string str)
{
    seteuid(getuid(this_object()));
    say(QCTNAME(this_player()) + " reads the " + QSHORT(this_object()) + ".\n");

    /* To fix a bug in /obj/more.c we do this nasty trick: */
    TP->add_prop(PLAYER_I_MORE_LEN,TP->query_option(OPT_MORE_LEN));

    if (!scroll_file)
        write("There was nothing to read in that book.\n");
    else if (str == "read" && file_size(scroll_file) < 4000)
        cat(scroll_file);
    else
        clone_object(MOREOBJ)->more(scroll_file, 1);
}

void
set_bookname(string str, string str2)
{
    bname = str;
    libr = str2;
}

string
query_bookname()
{
    return bname;
}

string
remove_object()
{
    if (libr)
      libr->returned_book(bname);
    ::remove_object();
}

