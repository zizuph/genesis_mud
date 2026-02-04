/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * norm_tab.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("book");
    set_short("huge book");
    set_long("This is a huge book.  The owner of the Ribos Pub, " +
	     "Mr. Samnibus Maloney, gave this, the bar tab of one " +
	     "Norm, to the King.  iIf Norm is ever found, the King " +
	     "stands to fill his treasury quite a bit.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 300);
}
