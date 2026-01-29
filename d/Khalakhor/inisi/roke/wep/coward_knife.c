/*
 * coward_knife.c
 *
 * Used in npc/coward.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 
  Modified by Motorhead to suit his purposes
*/

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_short("coward knife");
    set_adj("coward");
    set_name("knife");
    set_long("This is a big knife, much in use among cowards.\n");

    set_hit(10);
    set_pen(10);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
}
