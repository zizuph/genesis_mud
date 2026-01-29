/*
 * coward.c
 *
 * Used in nyreese/cas_c12.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

/* an automatically attacking small coward leaping to attack anyone
   who rests in c12
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

void
create_monster()
{
    default_config_npc(15);
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 20);
    set_aggressive(1);
    set_alignment(-5);

    set_name("coward");
    set_short("greedy coward");
    set_adj("greedy");

    set_long("The greedy coward attacks anyone who might carry money.\n");

    NEVERKNOWN;
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/coward_knife")->move(TO);
    clone_object(ROKEDIR + "arm/coward_shirt")->move(TO);

    command("wear all");
    command("wield all");
}

int
query_knight_prestige()
{
    return 250;
}
