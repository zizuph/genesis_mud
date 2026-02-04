/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * jorl_anvil.c
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
    set_name("anvil");
    set_short("Jorl's anvil");
    set_long("This is the anvil that Jorl uses to drop on " +
	     "the heads of mortals he wants to play a joke on.  " +
	     "If you give it back to him, he might just use it " +
	     "on you....as a joke, of course.\n");

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  20);
}
