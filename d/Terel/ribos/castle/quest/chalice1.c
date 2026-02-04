/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chalice1.c
 *
 *  This is a small miscellaneous treasure with the sole purpose of
 *  lending validity to the Evil in Ribos Quest.  Although it is a
 *  treasure, It will not be worth very much, so as to not ruin the
 *  game balance, because, for quest purposes, there will be 39 other
 *  miscellaneous treasures stored somewhere in the castle
 *
 * Coded by Vader on 05/22/1993
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
    set_name("chalice");
    set_adj("jeweled");
    set_short("jeweled chalice of Rialdi");
    set_long("This sacred chalice once belonged to the Princess " +
	     "of Rialdi.  In those times, it was passed from " +
	     "generation to generation in her family.  After her " +
	     "torid affair with the King, it was passed to " + 
	     "him.  It is lovely and elegant, clustered with " +
	     "precious stones in intricate patterns.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 200);
}
