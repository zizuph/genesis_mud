/*
 * k_helmet.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Calonderiel 94 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helmet");
    set_adj("mycenaen");
    set_short("mycenaen helmet");
    set_pshort("mycenaen helmets");
    set_long("An iron helmet, resembling the great helmet worn by the long " +
             "gone mycenaens.\n");

    set_ac(22);
    set_am(({0, 0, 0}));
    set_at(A_HEAD);

    add_prop(OBJ_I_VOLUME, 870);
}
