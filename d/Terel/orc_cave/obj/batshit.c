/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * batshit.c
 *
 * Used in the batshit quest.
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
    set_name("batguano");
    add_name("bat droppings");
    set_adj("lumpy");
    set_long("A small ovoid of almost dried bat droppings. "+
	     "A more educated person than you would call them "+
	     "batguano, on the other that educated person would "+
	     "never try picking them up either.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE,  1);
    add_prop(OBJ_M_NO_DROP, 0);
}


