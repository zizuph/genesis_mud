/*
 * camp-scout-1.c
 * Used in room/path-n-0.c
 *
 * TODO: Create interactions with the other scout
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit ROKEDIR + "lib/monster";
inherit "/std/act/seqaction.c";

#define DEBUG(x) find_player("treacher")->catch_msg(x+"\n")

void
test_seq_func()
{
    object friend = present("camp-scout-2", environment(this_object()));
    if(friend)
    {
        DEBUG("Friend found");
    }
    else
    {
        DEBUG("Friend NOT found");
    }
}

void
create_monster()
{
    set_race_name("human");
    set_name("scout");
    add_name("camp-scout-1");
    set_adj("sneaky");
    set_short("sneaky scout");
    set_long("A scout from the evil island Golbar.\n");
    set_alignment(-50);
    default_config_npc(55);

    NEVERKNOWN;

    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_HIDE, 15);

    //seq_new("test");
    //mixed *command_sequence1 = ({
    //                      "smile", 0, "@@test_seq_func", 0, "jump"
    //                    });
    //seq_addfirst("test", command_sequence1);
}

void
set_me_up()
{
    object arm1, arm2, arm3, wep;
    
    arm1 = clone_object(CAMP_ARM + "armour2");
    arm1->set_up(2);
    arm1->move(this_object());    
    arm2 = clone_object(CAMP_ARM + "armour2");
    arm2->set_up(4);
    arm2->move(this_object());    
    arm3 = clone_object(CAMP_ARM + "armour2");
    arm3->set_up(5);
    arm3->move(this_object());

    clone_object(CAMP_ARM + "leather-bracelet")->move(TO);

    wep = clone_object(CAMP_WEP + "weapon2");
    wep->set_up(1);
    wep->move(this_object());

    command("wear all");
    command("wield all");
}