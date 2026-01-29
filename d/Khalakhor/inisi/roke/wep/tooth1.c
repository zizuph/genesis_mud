/*
 * tooth1.c
 *
 * Used in npc/bore1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_name("tooth");
    set_adj("sharp");
    set_short("sharp tooth");
    set_long("A sharp Boretooth. It is made of some strange alloy. " +
             "It looks like it could be used as a knife\n");
    set_hit(15);
    set_pen(17);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
}
