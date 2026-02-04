/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pocket_protector.c
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
    set_name("sceptre");
    set_short("King RoTooles sceptre");
    set_long("This is the Sceptre that signified the fear of " +
	     "King RoTooles way back in the darker ages.  The " +
	     "sceptre was a replica of the RoTooles kingdom " +
	     "symbol, which is a globe with a handle underneath, " +
	     "with swords protruding from the globe.  He scared " +
	     "a great many subjects with this sceptre.\n");

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  20);
}
