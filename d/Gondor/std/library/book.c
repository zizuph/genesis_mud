/*
 * /d/Gondor/std/library/book.c
 *
 * A standard book used in the library of Solamnian Knights
 * Made by Nick
 * Updated for the new std/library by Aridor 12/96
 * 
 * Modification log:
 * Gwyneth 1/29/01: Updated from /d/Krynn/std/library/book.c for
 *                  Gondorian use.
 */
inherit "/std/scroll";

#include <cmdparse.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include "lib.h"

string gBname;
string gLibr;

public void
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
public void
read_it(string str)
{
    seteuid(getuid(this_object()));
    say(QCTNAME(this_player()) + " reads the " + short() + ".\n");

    /* To fix a bug in /obj/more.c we do this nasty trick: */
    this_player()->add_prop(PLAYER_I_MORE_LEN, 
        this_player()->query_option(OPT_MORE_LEN));

    if (!scroll_file)
        write("There was nothing to read in that book.\n");
    else if (str == "read" && file_size(scroll_file) < 4000)
        cat(scroll_file);
    else
        clone_object(MOREOBJ)->more(scroll_file, 1);
}

public void
set_bookname(string str, string str2)
{
    gBname = str;
    gLibr = str2;
}

string
query_bookname()
{
    return gBname;
}

string
remove_object()
{
    if (gLibr)
        gLibr->returned_book(gBname);
    ::remove_object();
}

