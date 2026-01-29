/*
 * steelmail.c
 *
 * Used in npc/towerg2.c npc/towerg4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("platemail");
    add_name(({"mail", "plate"}));
    set_adj("steel");
    set_short("steel platemail");
    set_long("It's a steel platemail, made by the best blacksmiths of Nyreese.\n");
    set_ac(30);
    set_at(A_BODY);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4000);
}
