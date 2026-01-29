/*
 *  /d/Sparkle/area/tutorial/obj/heart.c
 *
 *  This leftover can be cut from Farmer Brown's daughter. Doing
 *  so was the most heinous act of evil I could imagine, and therefore
 *  created to allow evil roleplayers to do their thing.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth) 
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/leftover";

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_leftover();


/*
 * Function name:        create_leftover
 * Description  :        set up the leftover
 */
public void
create_leftover()
{
    set_name("heart");
    add_name( ({ "leftover", "_tutorial_heart", "_tutorial_item" }) );
    set_adj( ({ "young", "human" }) );
    set_short("young human heart");
    set_long("This heart is smaller than your fist. It once beat with"
      + " the spirit of joy and innocence.\n");

    add_prop(OBJ_M_NO_DROP, "You decide not to get rid of the heart."
      + " You could probably <show> it to someone, though.\n");
    add_prop(OBJ_M_NO_GIVE, "You decide not to give the heart away."
      + " Perhaps you can just <show> it to someone instead.\n");
 
    set_decay_time(9999); /* lets not have them decay too easily */
    set_amount(1);
} /* create_leftover */

string
query_recover()
{
    return MASTER + ":" + "#ic#" + item_count + "#";
}

void
init_recover(string arg)
{
    int     ic;
    string  foo;

    sscanf(arg, "%s#ic#%d#", foo, ic);
    if (ic > 0)
        set_heap_size(ic);
}


