/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * meat.c
 *
 * Janus 920701
 * modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDFOOD;

#include "/d/Terel/include/recover.h"

/*
 * Function name: create_food
 * Description:   Create the food.
 */
public void
create_food()
{
    set_name("meat");
    set_adj("bloody");
    set_long("This is bloody hunks of meat from an animal.  Looks OK to " +
	     "eat, but better prepare it first.\n");
    set_amount(100); /* 500 grams of food. */
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, random(200));
}

