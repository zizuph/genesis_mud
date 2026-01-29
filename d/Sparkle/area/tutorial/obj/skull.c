/*
 *  /d/Sparkle/area/tutorial/obj/skull.c
 *
 *  This leftover can be cut from the animals which inhabit the
 *  Sterling Woods, and elsewhere in Silverdell.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth) 
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/leftover";

#include <macros.h>

/* Prototypes */
public void        create_leftover();


/*
 * Function name:        create_leftover
 * Description  :        set up the leftover
 */
public void
create_leftover()
{
    set_name("skull");
    add_name( ({ "leftover" }) );
    set_adj( ({ "animal" }) );
    set_short("animal skull");
    set_long("This is the scavenged skull of an animal.\n");
 
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
