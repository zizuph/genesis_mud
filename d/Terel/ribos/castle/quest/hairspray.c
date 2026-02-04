/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hairspray
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
    set_name("hairspray");
    set_short("Jimmy Johnson's Hairspray");
    set_long("This is a small bottle, with an ingenious nozzle on the " +
	     "end that lets its contents spray out.  This particular " +
	     "bottle belongs to Jimmy Johnson.  He uses it to keep his " +
	     "hair in place, patch holes in walls, remove paint from " +
	     "cars, and glue people wearing helmets to structures that " +
	     "are high up.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10);
}
