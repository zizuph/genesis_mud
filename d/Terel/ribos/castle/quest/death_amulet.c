/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * death_amulet.c
 *
 * A black amulet
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
    set_name("amulet");
    set_adj("black");
    set_short("large black amulet");
    set_long("This amulet is black.  Dark black.  On the back, " +
	     "in a silver imprint is the image of a scythe.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE,  10);
}
