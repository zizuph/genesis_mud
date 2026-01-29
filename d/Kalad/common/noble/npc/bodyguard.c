/* 
 * /d/Kalad/common/noble/npc/bodyguard.c
 * Purpose    : The bodyguard of nobles who wander the noble district
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *              Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("bodyguard");
    set_adj("strong");
    add_adj("stern");
    set_race_name("human");
    set_short("strong stern bodyguard");
    set_long("This man regards you with careful eyes. His job is to "+
        "protect the nobles who hire him. He seems like he can do his "+
        "job quite well.\n");

    set_alignment(200);
    set_knight_prestige(-60);

    add_speak("Don't cause trouble.\n");

    set_stats(({125,120,130,60,60,100}));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENSE, 100);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_act_time(3);
    add_act("scratch chin");
    add_act("glare all");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/os_helm",
        NOBLE + "arm/os_breastplate",
        NOBLE + "arm/os_bracers",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        NOBLE + "wep/bastard_sword"
        }));

    MONEY_MAKE_SC(random(12))->move(TO);

    // Configure our special attack
    set_default_special(25, W_BLUDGEON, 85, 300, A_BODY);
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

// Special has random weapon penetration
int
query_special_wcpen()
{
    return 300 + random(300);
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
      tell_room(ENV(enemy), QCTNAME(TO) + " parries " + QTNAME(enemy) +
         "'s blow " + "with his " + query_weapon(-1)[0]->short() +
         ", then slams his shoulder " +
         "into " + HIS(enemy) + " side" + how + ".\n", enemy);
   }
   else
   {
      enemy->catch_msg(QCTNAME(TO) + " dodges your swing, then brings " +
         "up the hilt of his " + query_weapon(-1)[0]->short() +
         " across your face" + how + ".\n");
      tell_room(ENV(enemy), QCTNAME(TO) + " dodges " + QTNAME(enemy) +
         "'s swing, " + "then brings up the hilt of his " +
         query_weapon(-1)[0]->short() + " across " +
         HIS(enemy) + " face" + how + ".\n", enemy);
   }
}
