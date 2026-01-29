/*
 * guard3.c
 *
 * Used in nyreese/cas_c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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

    clone_object(ROKEDIR + "wep/battleaxe3")->move(TO);
    clone_object(ROKEDIR + "arm/doublemail")->move(TO);
    clone_object(ROKEDIR + "arm/chainhelm")->move(TO);

    command("wear all");
    command("wield all");
}

void
create_monster()
{
    default_config_npc(45);

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_AXE, 60);
    set_skill(SS_PARRY, 60);
    set_aggressive(1);
    set_alignment(90);

    set_name("guard");
    set_short("castle guard");
    set_adj("castle");
    set_race_name("dwarf");
    set_long("The guard looks like if he usually kills people disturbing " +
             "him... And then EATS them!!!\n");
}

int
query_knight_prestige()
{
    return 700;
}
