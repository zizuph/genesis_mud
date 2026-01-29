/*
 * warpig.c
 *
 * Used in carisca/f8.c carisca/f10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(40);
    set_short("war pig");
    set_name("pig");
    set_adj("war");
    set_long("This is a pig dressed for war. It looks quite sturdy.\n");
    set_race_name("pig");

    add_act("emote oinks quite desperately.");
    add_act("emote shakes a leg.");
    set_act_time(7);

    set_attack_unarmed(0, 14, 14, W_IMPALE, 60, "jaws");
    set_hitloc_unarmed(A_HEAD, ({10}), 10, "head");
    set_hitloc_unarmed(A_BODY, ({30}), 80, "body");

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 15);
    NEVERKNOWN;

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);
}

void
equip_me()
{
    object armour;
    armour = clone_object(ROKEDIR + "arm/pigskin");
    armour->move(TO);
}
