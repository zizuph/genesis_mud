/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fatty_chin.c
 *
 * Fatty's missing chin
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
    set_name("chin");
    set_adj("missing");
    set_short("Fatty's missing chin");
    set_long("This is the chin Fatty has been looking for.  " +
	     "Somewhere along the line, this one got crowded in " +
	     "between numbers 8 and 9.  It couldn't breathe, so he " +
	     "removed it, and set it aside for a while, where he soon " +
	     "misplaced it under a pile of donut crumbs.\n");

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE,  0);
}

