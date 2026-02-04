/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hope_amulet.c
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
    set_name("amulet");
    set_short("small amulet");
    set_long("This is a small amulet.  On the front, are several " +
	     "markings that look like flowers.  On the back, you " +
	     "see the words 'Geeb Arok Tarkin'.  It is a fine, " +
	     "beautiful piece of jewelry.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE,  10);
}
