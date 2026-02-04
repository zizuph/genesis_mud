/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * torbas_staff.c
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
    set_name("staff");
    set_short("torbas's staff");
    set_long("This is a fine, wooden staff, with a metal cap in the shape " +
	     "of an eagle.  It belonged to Torbas, but the King stole it " +
	     "as a bit of a prank when he was 17.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
}
