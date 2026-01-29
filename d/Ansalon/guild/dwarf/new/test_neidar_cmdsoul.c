/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */
#pragma strict_types
inherit "/cmd/std/command_driver";
inherit "/cmd/std/soul_cmd";
inherit "/d/Genesis/specials/abilities";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

int 
query_cmd_soul() 
{ 
    return 1; 
}

string
get_soul_id()
{
    return "Neidar Test Cmdsoul";
}


int
armour_bonus(string str)
{
    setuid();
    seteuid(getuid());
    object evade_object = clone_object("/d/Ansalon/guild/dwarf/new/special_armour_bonus");
    evade_object->set_effect_caster(this_player());
    evade_object->set_effect_target(this_player());
    evade_object->move(this_player(), 1);
    evade_object->start();

    this_player()->catch_msg("You gain armour bonus.\n");
    return 1;

}

int
shield_master(string str)
{
    object ob = find_player(str);

    if (!ob) {
        notify_fail("Target: *"+str+"* not found\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    object evade_object = clone_object("/d/Ansalon/guild/dwarf/new/special_shieldblock");
    evade_object->set_effect_caster(this_player());
    evade_object->set_effect_target(ob);
    evade_object->move(ob, 1);
    evade_object->start();

    this_player()->set_shield_master_target(ob);

    this_player()->catch_msg("You begin protecting "+QTNAME(ob)+" with your shield.\n");
    ob->catch_msg(QCTNAME(this_player())+" begins protecting you.\n"); 
    return 1;

}

public mapping
query_ability_map() 
{
    return ([
    "chop" : "/d/Ansalon/guild/dwarf/new/special_attack_chop",
     ]);
}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */
        "chop"     :   "do_ability",
         "sm" : "shield_master",
         "ab" : "armour_bonus",
        ]);
}