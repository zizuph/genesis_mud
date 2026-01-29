/*
 * campwarrior.c
 *
 * Used in wild/fd.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>
#include <macros.h>

#define ANT_ARMOURS 6

void
create_monster()
{
    int i;

    set_name("warrior");
    set_short("ugly warrior");
    set_long("He's a warrior from the evil island Golbar.\n");
    set_adj("ugly");
    add_name("human");
    set_alignment(-10);
    NEVERKNOWN;

    set_skill(SS_DEFENCE, 35);
    for (i = 0; i < 7; i++)
        set_skill(i, 30);

    default_config_npc(35);
}

int
query_knight_prestige()
{
    return 500;
}

void
equip_me()
{
    object arm, wep;
    int tmp;

    seteuid(getuid(this_object()));

    tmp = (2 + random(6)) / 2;
    wep = clone_object(ROKEDIR + "wep/weapon2");
    wep->set_up(tmp);
    wep->move(this_object());

    tmp = (2 + random(6)) / 2;
    arm = clone_object(ROKEDIR + "arm/armour2");
    arm->set_up(tmp);
    arm->move(this_object());

    command("wear armour");
    command("wield weapon");
}
