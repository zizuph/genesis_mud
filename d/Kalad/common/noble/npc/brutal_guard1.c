/* 
 * /d/Kalad/common/noble/npc/brutal_guard1.c
 * Purpose    : The brutal guard of the house of Alexander, guards prisoner
 * Located    : /d/Kalad/common/noble/alexander/
 * Created By : Sarr ??.??.95
 * Modified By: Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

// Variables
string house_name;
string color_name;

string
*ran_adj()
{
    return ({
        ({"muscular","beady-eyed"}),
        ({"mean","stone-faced"}),
        ({"fierce","black-skinned"}),
        ({"nasty","shifty-eyed"}),
        ({"proud","big-nosed"}),
        })[random(5)];
}

void
create_kalad_monster()
{
    string *str = ran_adj();
    object ob;

    set_name("guard");
    set_adj("brutal");
    set_race_name("human");
    set_short("brutal guard of the house of @@query_house_name@@");
    set_long("This guard's job is to protect the house of his Lord. He "+
        "seems quite capable of doing that, as he is very well paid and "+
        "very well trained.\n");

    set_alignment(400);
    set_knight_prestige(-100);

    add_speak("Don't cause trouble.\n");

    set_stats(({110,110,100,60,60,100}));

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,100);

    set_act_time(5);
    add_act("beat bloodied goblin");
    add_act("slap bloodied goblin");
    add_act("growl");
    add_act("spit goblin");
    add_act("say Get out of here!");
    set_cact_time(3);
    add_cact("shout Fool! You will die now!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_equipment(({
        NOBLE + "wep/" + ({"spiked_mace", "morning_star",
            "steel_broadsword"})[random(3)],
        NOBLE + "obj/door_key",
        NOBLE + "arm/os_helm",
        NOBLE + "arm/os_breastplate",
        NOBLE + "arm/os_bracers",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        // house name and color name needs to be set for the cloak
        NOBLE + "arm/house_cloak",
        }));

    MONEY_MAKE_SC(random(35))->move(TO);
}

void
set_house_name(string str)
{
object ob;

    ob = present("cloak");
    ob->set_house_name(str);
    house_name = str;
}

void
set_color_name(string str)
{
object ob;

    ob = present("cloak");
    ob->set_color_name(str);
    color_name = str;
}

string
query_house_name()
{
    return house_name;
}

string
query_color_name()
{
    return color_name;
}

