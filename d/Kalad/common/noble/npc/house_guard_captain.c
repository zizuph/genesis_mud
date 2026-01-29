/* 
 * /d/Kalad/common/noble/npc/house_guard_captain.c
 * Purpose    : Captain of the houseguard of nobles 
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *              Fysix, Feb 1998, Recoded
 *              Zignur, June 2017 changed stats,skills, modifier.
 *              Zignur 20171017 bugfix he did not wield his weapon
 *              Zignur 20171026 bugfix use clone_unique
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";
/* Zignur 20171026 bugfix use clone_unique for magic weapons */
inherit "/lib/unique";

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

void
create_kalad_monster()
{
   
    string *str = ran_adj();
    object weapon;

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
    /* New stats changed by Zignur 2017-06-29 */
    set_stats(({120,130,120,120,120,120}));
    
    /* Zignur 20171026 bugfix otherwise he wont wield properly */
    refresh_living();
    /* New skills changed by Zignur 2016-06-29*/
    set_skill(SS_WEP_CLUB,70);
    set_skill(SS_DEFENSE,70);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_PARRY,70);
    set_skill(SS_BLIND_COMBAT,50);

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

    /* Zignur 20171026 bugfix use clone_unique */
    weapon = clone_unique(NOBLE + "wep/magic_mace", 20,
                      NOBLE +"wep/morning_star");
    weapon -> move(TO);
    
    equip(({
        weapon,
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

    /* XP Adjustment, Zignur 2017-06-29 */
    set_exp_factor(120);    
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

