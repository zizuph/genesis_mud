/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * book.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
#include <cmdparse.h>

#define MORE_OBJ    "/std/board/board_more"

inherit STDOBJECT;

public int do_read(string str);

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("kingdom_index");
    add_name("book");
    add_name("ribos_book");
    set_short("blue leathery book");
    set_adj("blue");
    set_adj("leathery");
    set_long("This book has not been in existence very long, " +
	     "and judging by the version information on the front " +
	     "cover, you think it might be updated every year.  " +
	     "The book is covered in fine, blue leather and the " +
	     "title is Royal Histories of the World. \n");

    add_prop(OBJ_I_VOLUME, random(6000)+500);
    add_prop(OBJ_I_WEIGHT, TO->query_prop(OBJ_I_VOLUME)/2);
    add_prop(OBJ_I_VALUE,  0);
	
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
	::init();
	add_action(do_read,"read");
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */
public int
do_read(string str)
{
    FIX_EUID;
    if (str == "book" || str == "blue book" || str == "leather book") {
	say(QCTNAME(TP)+" reads from the blue book.\n");;
	clone_object(MORE_OBJ)->more(CASTLE_DIR + "obj/history.book", 3);
	return 1;
    }
    else {
	NF("Read what?\n");
	return 0;
    }
}

