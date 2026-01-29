/*
 *  /d/Sparkle/area/tutorial/obj/krolock_heart.c
 *
 *  This leftover is actually the heart of Baron von Krolock.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated July 22, 2016 by Gronkas: override command_eat function
 *  to prevent this quest item from being accidently eaten
 *
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
    add_name( ({ "leftover", "_krolock_heart", "_tutorial_item" }) );
    set_adj( ({ "old", "withered" }) );
    set_short("old withered heart");
    set_long("This is the beating heart of Baron von Krolock. What"
      + " vile sorcery must be present to keep such a thing beating"
      + " outside his body, you cannot fathom. The mayor of Greenhollow"
      + " would very much like you to bring this to him immediately.\n");

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

/* override standard food function to prevent eating quest item */

public mixed
command_eat()
{
	return "You attempt to force yourself to eat the old withered heart"+
        " but fail. Yuck!\n";
}
