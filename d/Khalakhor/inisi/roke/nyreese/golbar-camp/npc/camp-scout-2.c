/*
 * camp-scout-2.c
 * Used in room/path-n-0.c
 *
 * TODO: Create interactions with the other scout
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit ROKEDIR + "lib/monster";

void
create_monster()
{
    set_race_name("human");
    set_name("scout");
    add_name("camp-scout-2");
    set_adj("weary");
    set_short("weary scout");
    set_long("A scout from the evil island Golbar.\n");
    set_alignment(-50);
    default_config_npc(45);

    NEVERKNOWN;

    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_PARRY, 45);
	set_skill(SS_AWARENESS, 50);
}

void
set_me_up()
{
    object arm1, arm2, arm3, wep;
    
    arm1 = clone_object(ROKEDIR + "arm/armour2");
    arm1->set_up(2);
    arm1->move(this_object());    
    arm2 = clone_object(ROKEDIR + "arm/armour2");
    arm2->set_up(4);
    arm2->move(this_object());    
    arm3 = clone_object(ROKEDIR + "arm/armour2");
    arm3->set_up(5);
    arm3->move(this_object());

    clone_object(CAMP_ARM + "leather-bracelet")->move(TO);

    wep = clone_object(CAMP_WEP + "weapon2");
    wep->set_up(1);
    wep->move(this_object());


    command("wear all");
    command("wield all");
}