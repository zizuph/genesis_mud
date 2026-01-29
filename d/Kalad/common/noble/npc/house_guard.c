/* 
 * /d/Kalad/common/noble/npc/house_guard.c
 * Purpose    : The houseguard of nobles 
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *              Fysix, Feb 1998, Recoded
                Zignur June 2017 modified stats and skills
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

    set_name("guard");
    set_adj("noble");
    set_race_name("human");
    set_short("noble guard of the house of @@query_house_name@@");
    set_long("This guard's job is to protect the house of his Lord. He "+
        "seems quite capable of doing that, as he is very well paid and "+
        "very well trained.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    add_speak("Don't cause trouble.\n");
    /* New stats changed by Zignur 2016-06-29 */  
    set_stats(({110,110,110,110,110,110}));
    
    /* New skills changed by Zignur 2017-06-28 */
    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_WEP_CLUB,70);
    set_skill(SS_DEFENSE,70);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,70);
    set_skill(SS_BLIND_COMBAT,50);

    set_act_time(5);
    add_act("scratch chin");
    add_act("emote fidgets.");
    add_act("say Are you a new servant?");
    add_act(({"sweat","emote mumbles something about the hot sun."}));

    set_cact_time(3);
    add_cact("say I shall protect my Lord!");
    add_cact("shout Fool! You will die now!");

    add_prop(LIVE_I_NEVERKNOWN,1);
    /* Use the function equip instead */
    equip(({
        NOBLE + "wep/" + ({"spiked_mace", "morning_star",
        "steel_broadsword"})[random(3)],
        NOBLE + "arm/os_helm",
        NOBLE + "arm/os_breastplate",
        NOBLE + "arm/os_bracers",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        NOBLE + "arm/house_cloak",
        }));

    MONEY_MAKE_SC(random(35))->move(TO);

    // Configure our special attack
    set_default_special(25, W_BLUDGEON, 85, 250, A_BODY);

   /* XP Adjustment, Zignur 2017-06-29 */
   /* Very well armoured and a special */
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

// Execute a special attack only if we have a weapon
int special_attack(object enemy)
{
   // This special requires having a weapon
   if (!sizeof(query_weapon(-1)))
      return 0;

   return ::special_attack(enemy);
}

// Aim for head or body randomly, body with 66% chance
int
query_special_hitloc_id()
{
   return ({A_BODY, A_HEAD})[random(3) ? 0 : 1];
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
   int damage_type, int damage)
{
string how;

   if (phurt <= 0)
      how = " with hardly any effect";
   else
      switch(phurt)
      {
        case 1..10:
         how = "";
         break;
        case 11..20:
         how = " with a thud";
         break;
        case 21..40:
         how = " with a loud thud";
         break;
        case 41..70:
         how = " with a loud crack";
         break;
        default:
         how = " with a bone crushing sound";
      }

   if (hitloc_id == A_BODY)
   {
      enemy->catch_msg(QCTNAME(TO) + " parries your blow with his "+
         query_weapon(-1)[0]->short() +
         ", then slams his shoulder into your " +
         "side" + how + ".\n"); 
      tell_watcher(QCTNAME(TO) + " parries " + QTNAME(enemy) +
         "'s blow " + "with his " + query_weapon(-1)[0]->short() +
         ", then slams his shoulder " +
         "into " + HIS(enemy) + " side" + how + ".\n", enemy);
   }
   else
   {
      enemy->catch_msg(QCTNAME(TO) + " dodges your swing, then brings " +
         "up the hilt of his " + query_weapon(-1)[0]->short() +
         " across your face" + how + ".\n");
      tell_watcher(QCTNAME(TO) + " dodges " + QTNAME(enemy) +
         "'s swing, " + "then brings up the hilt of his " +
         query_weapon(-1)[0]->short() + " across " +
         HIS(enemy) + " face" + how + ".\n", enemy);
   }
}

