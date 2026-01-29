/*
 * child.c
 *
 * Used in nyreese/cas_a5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* gresolle -92 */

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
    clone_object(ROKEDIR + "wep/stick")->move(TO);

    command("wield all");
}

void
create_monster()
{
    default_config_npc(10);

    set_skill(SS_DEFENCE, 5);
    set_skill(SS_WEP_SWORD, 5);
    set_skill(SS_PARRY, 5);

    set_alignment(-5);

    set_name("child");
    set_short("evil child");
    set_adj("evil");

    set_long("The child is torturing an innocent white mouse.\n" +
             "He was left behind when the evil wizard was hunted " +
             "out of the castle.\n");
    add_leftover(ROKEDIR + "obj/fat.c", "slice of fat", 1, "", 1, 1);
}

int
query_knight_prestige()
{
    return 50;
}
