/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Decker's briefcase
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
    set_name("briefcase");
    set_short("Decker's briefcase");
    set_long("This is an odd looking case with a handle on top.  " +
	     "It is crafted of fine, top grain leather, and smells " +
	     "of a blend of leather, chicken, and beef.  There " +
	     "are also several ketchup stains.  On top, you see the " +
	     "name 'Decker'.  Could this be the briefcase of " +
	     "the great wizard Decker?  How did the King acquire it?  " +
	     "Oh No!  What will Decker do now?\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10);
}
