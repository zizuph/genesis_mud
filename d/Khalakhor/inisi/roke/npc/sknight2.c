/*
 * sknight2.c
 *
 * Used in nyreese/cas_b3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

void
equip_me()
{
    clone_object(ROKEDIR + "wep/battleaxe")->move(TO);
    clone_object(ROKEDIR + "arm/doublemail")->move(TO);
    clone_object(ROKEDIR + "arm/doublehelmet")->move(TO);

    command("wear all");
    command("wield all");
}

void
create_monster()
{
    set_name("knight");
    add_name("guard");
    set_adj("experienced");
    set_race_name("dwarf");
    set_short("experienced knight");
    set_long("The knight guards the stairs and stops anyone that " +
             "wants to go to the next floor.\n");

    set_alignment(-45);
    default_config_npc(60);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);

    NEVERKNOWN;
}
