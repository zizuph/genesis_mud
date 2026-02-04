/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Cedric's discus
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
    set_name("discus");
    set_short("Cedric's discus");
    set_long("This is the discus that Cedric throws around whenever he " +
	     "is bored.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,  10);
}
