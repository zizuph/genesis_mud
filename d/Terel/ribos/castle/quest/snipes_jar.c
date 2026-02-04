/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * snipes_jar.c
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
    set_name("snipes");
    set_short("jar of snipes");
    set_long("When King Bor-El was young, a town commoner played " +
	     "a little joke on him.  He informed the young lad as " +
	     "to the fun of hunting Snipes.  The King, at that time, " +
	     "was an impressionable young lad, and went off on his " +
	     "futile quest.  Vader, feeling sorry for the young lad, " +
	     "created some Snipes for the King to catch.  What you see " +
	     "in this jar is one of a kind.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 300);
}
