/*
 * skeleton.c
 *
 * Used in carisca/x1.c carisca/x2.c carisca/x4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>

void
create_monster()
{
    set_name("ghoul");
    set_long("The ghoul eats corpses.\n");
    set_race_name("ghoul");

    set_aggressive(1);
    set_alignment(-75);

    default_config_npc(35);

    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_DEFENCE, 15);

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);
}

void
equip_me()
{
    seteuid(getuid(TO));

    clone_object(ROKEDIR + "arm/pigskin")->move(TO);

    command("wear all");
}
