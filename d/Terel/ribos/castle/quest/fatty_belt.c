/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fatty_belt.c
 *
 * Fatty's belt
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
    set_name("belt");
    set_adj("fatty's");
    set_short("Fatty's belt");
    set_long("This is an extremely long piece of thick, roughened leather " +
	     "with holes in it that look a bit strained.  It is none " +
	     "other than Fatty's Belt, which held up his pants for " +
	     "about three weeks.  King Bor-El aquired it after it " +
	     "snapped one morning after breakfast, and shot across " +
	     "the sky and wrapped itself around a tree, totally obscurring " +
	     "the tree and all of its leaves from the sun.  It took him " +
	     "three days to unravel it from around that tree.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 300);
}
