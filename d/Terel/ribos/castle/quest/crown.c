/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * crown.c
 *
 * a golden crown
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
    set_name("crown");
    set_adj("golden");
    set_short("golden crown");
    set_long("This is the fabulous crown of the late King Farl.  He " +
	     "was the first leader of a people that managed to get " +
	     "its forces into Ribos for attack.  The invaders were " +
	     "defeated.  King Farl was foolish enough to come along " +
	     "with his forces.  He died in the castles dungeon.\n");

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,  10);
}
