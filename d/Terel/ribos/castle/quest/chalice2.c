/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chalice2.c
 *
 * a crystal chalice
 *
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
    set_name("chalice");
    set_adj("crystal");
    set_short("small cystal chalice");
    set_long("This is just a small crystal chalice.  You have " +
	     "no idea why the King has chosen to store it here.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 200);
}
