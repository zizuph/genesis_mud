/*
 * h_gloves.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  This pair of gloves belongs to Van Helsing.
    coded by Calonderiel 930906                  */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("gloves");
    add_name("pair of leather gloves");
    set_adj("leather");
    add_adj("fine");
    set_short("pair of leather gloves");
    set_pshort("pairs of leather gloves");
    set_long("A fine pair of leather gloves, protecting the hands from " +
             "the cold night.\n");

    set_default_armour(2, A_HANDS, ({0, 0, 0}), 0);

    add_prop(OBJ_I_VOLUME, 200);
}
