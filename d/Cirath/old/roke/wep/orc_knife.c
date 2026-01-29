/*
 * orc_knife.c
 *
 * Used in obj/charity.c npc/kobold2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 
  Modified by Motorhead to suit his purposes
  Nahh i want it like this :-) / geddy

*/

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_short("orc knife");
    set_adj("orc");
    set_name("knife");
    set_long("This is a small knife, much in use among baby orcs.\n");

    set_hit(10); 
    set_pen(7); 

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
