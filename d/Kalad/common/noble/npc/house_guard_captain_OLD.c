/* 
 * /d/Kalad/common/noble/npc/house_guard_captain.c
 * Purpose    : Captain of the houseguard of nobles 
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *              Fysix, Feb 1998, Recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";

#include "default.h"
#include <money.h>

string house_name;
string color_name;

string
*ran_adj()
{
    return ({
        ({"ferocious","stern"}),
        ({"gigantic","black-eyed"}),
        ({"cruel","barrel-chested"}),
        ({"mighty","blonde-bearded"}),
        ({"menacing","giant"}),
        })[random(5)];
}

object
unique_item(string name, string alter, int num)
{
    if(objectp(find_object(name)))
        if(num < sizeof(object_clones(find_object(name))))
            return clone_object(alter);
        else
            return clone_object(name);
    else
        return clone_object(name);
}

void
create_kalad_monster()
{
    string *str = ran_adj();
    object ob;

    set_name("guard");
    add_name("captain");
    set_adj("noble");
    set_race_name("human");
    set_short("noble guard captain of the house of @@query_house_name@@");
    set_long("This guard's job is to protect the house of his Lord. He "+
        "seems quite capable of doing that, as he is very well paid and "+
        "very well trained. This one seems to be the leader.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    add_speak("Don't cause trouble.\n");
    set_stats(({110,130,110,70,60,100}));

    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT,100);

    set_act_time(5);
    add_act("scratch chin");
    add_act("say I serve my Lord well.");
    add_act("say Don't even think about messing with me.");
    add_act("growl all");
    add_act("glare all");

    set_cact_time(3);
    add_cact("say I shall protect my Lord!");
    add_cact("shout Fool! You will die now!");

    add_prop(LIVE_I_NEVERKNOWN,1);

    ob = unique_item(NOBLE + "wep/magic_mace",
        NOBLE + "wep/morning_star", 5);
    ob->move(TO, 1);

    add_equipment(({
        NOBLE + "arm/os_helm",
        NOBLE + "arm/os_breastplate",
        NOBLE + "arm/os_bracers",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        NOBLE + "arm/house_cloak",
        NOBLE + "arm/os_shield",
        }));

    MONEY_MAKE_GC(random(5))->move(TO);

    // Configure our special attack with random hitlocation
    set_default_special(12, W_BLUDGEON, 90, 300, -1);
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

// Special has random weapon penetration
int
query_special_wcpen()
{
    return 400 + random(200);
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
   int damage_type, int damage)
{
string msg;

    enemy->catch_tell(TO->query_The_name(enemy) +
        " rams you with his head!\n");

    switch(phurt)
    {
        case -100..-1:
            msg = "misses";
            break;
        case 0..25:
            msg = "lightly grazes";
            break;
        case 26..50:
            msg = "slams into";
            break;
        case 51..75:
            msg = "brutally slams into";
            break;
        default:
            msg = "devastates";
    }       

    enemy->catch_tell(TO->query_The_name(enemy) + " " + msg
        + " you with his head.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " " + msg + " " +
        QTNAME(enemy) + " with " + "his head.\n", enemy);
}

