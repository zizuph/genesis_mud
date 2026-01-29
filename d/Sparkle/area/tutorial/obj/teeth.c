/*
 *  /d/Sparkle/area/tutorial/obj/teeth.c
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
    set_name("tooth");
    add_name( ({ "leftover" }) );
    add_pname( ({ "teeth" }) );
    set_adj( ({ "animal" }) );
    set_short("animal tooth");
    set_pshort("animal teeth"); /* we don't want tooths */
    set_long("These are the scavenged teeth of an animal.\n");
 
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
