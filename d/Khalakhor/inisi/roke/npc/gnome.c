/*
 * gnome.c
 *
 * Used in wild/ran/forroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>

void
create_monster()
{
    set_name("gnome");
    set_race_name("gnome");
    set_short("small gnome");
    set_long("This small gnome looks very helpful.\n");
    set_adj("small");

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_POLEARM, 35);
    set_skill(SS_UNARM_COMBAT, 40);
    default_config_npc(25);
    set_base_stat(SS_STR, 100);
}
