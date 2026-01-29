/*
 * This file is NCAMP_NPC + "orc_spy"
*/

#pragma strict_types

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_NPC + "ncamp_orc.c";

public void
create_ncamp_orc()
{
    set_long("This small and snivelling creature looks like the runt of the "
        + "litter, if there is such a thing among its kind. It cringes and "
        + "whines about its duties, which seem to be limited to sitting high "
        + "up in this tree and keeping an eye out for danger.\n");
    
    default_config_npc( 5 );
    set_base_stat(SS_INT, 5);
    set_base_stat(SS_WIS, 5);
    set_base_stat(SS_DIS, 5);

}
