/*
 * guard2.c
 *
 * Used in nyreese/cas_b11.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

/* an automatically attacking monster intended for use in the
   guard room of the castle 
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <money.h>
#include <ss_types.h>
#include <macros.h>

void
equip_me()
{
    clone_object(ROKEDIR + "wep/battleaxe")->move(TO);
    clone_object(ROKEDIR + "arm/doublemail")->move(TO);
    clone_object(ROKEDIR + "arm/chainhelm")->move(TO);

    command("wear all");
    command("wield all");
}

void
create_monster()
{
    default_config_npc(35);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_PARRY, 50);
    set_aggressive(1);
    set_alignment(75);

    set_name("guard");
    set_short("castle guard");
    set_adj("castle");
    set_race_name("dwarf");
    set_long("The guard is NOT happy about you intruding in his lunch room!\n");

    NEVERKNOWN;
}

int
query_knight_prestige()
{
    return 500;
}
