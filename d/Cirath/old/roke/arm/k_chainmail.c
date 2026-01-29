/*
 * k_chainmail.c
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

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("chainmail");
    add_name("coat");
    set_adj("polished");
    set_short("coat of polished chainmail");
    set_pshort("coats of polished chainmail");
    set_long("A well made coat of steel chainmail.\n");

    set_ac(27);
    set_am(({-1, 1, 0}));
    set_at(A_TORSO | A_ARMS);

    set_af(TO);

    add_prop(OBJ_I_VOLUME, 3750);
}

int
wear(object ob)
{
    write("You wear the " + ob->short() + " on your arms and " +
          "shoulders.\n");
    say(QCTNAME(TP) + " wears the " + ob->short() + ".\n");
    return 1;
}
