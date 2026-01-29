/*
 * blademaster_kilt.c
 * 
 * Black kilt for Blademasters to wear.
 *
 * Khail - Mar 4/97
 */
#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit "/d/Khalakhor/std/arm/kilt_base";

public int
is_blademaster_equipment()
{
    return 1;
}

public string
can_identify_sett()
{
    if (!TP->is_khalakhor_clan_member())
        return "You are unable to identify the pattern, however.\n";

    else
        return "You easily recognize the dark sett as that worn " +
            "by the Blademasters of Khalakhor.\n";
}

public void
create_unique_kilt()
{
    set_name("kilt");
    set_adj("heavy");
    add_adj("black");
    set_short("heavy black kilt");
    set_long("The heavy kilt is made wool, and largely black. " +
        "The pattern of the tartan is almost entirely composed " +
        "of the main black colour, but a thin cross-hatching of " +
        "deep blue is present. " + VBFC_ME("can_identify_sett"));

   add_prop(OBJ_I_BLADEMASTER_ARM, 1);
}
