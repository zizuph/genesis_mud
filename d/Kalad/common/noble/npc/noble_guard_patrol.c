/* 
 * /d/Kalad/common/noble/npc/noble_guard_patrol.c
 * Purpose    : The patrolguard of nobles 
 * Located    : /d/Kalad/common/noble/
 * Created By : Sarr ??.??.96
 * Modified By: Toby 970725,
 *      Fysix, Recoded, March 1998
 */ 
#pragma strict_types

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";

#include "default.h"

void
create_kalad_monster()
{
    set_name("guard");
    set_adj("wary");
    add_adj("noble-district");
    set_race_name("human");
    set_short("wary noble-district guard");
    set_long("This is a high-priced elite guard hired by the various "+
      "nobles of this district to keep the place clean and crime-free. "+
      "The nobles hire only the best, and you can be sure this one "+
      "knows how to do his job and do it well. His hard, shifty eyes, "+
      "cold, grim expression and strong, tall physique make you think "+
      "twice about messing with him.\n");
    set_alignment(300);
    set_knight_prestige(-50);
    add_speak("Things are pretty quiet now in the Noble district.\n");
    set_stats(({120,130,120,90,90,100}));
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_BLIND_COMBAT,100);

    set_random_move(1);
    set_act_time(4);
    add_act("emote adjusts his armour.");
    add_act("emote prods you along.");
    add_act("say Watch yourself, you are in the Noble District now.");
    add_act("spit");
    set_cact_time(4);
    add_cact("shout You will die you fool!");
    add_cact("say I am the best, you cannot defeat me!");
    add_cact("say You are good, but not that good!");
    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "wep/" + ({"steel_broadsword", "steel_halberd",
        "spiked_mace", "steel_longsword"})[random(4)],
        NOBLE + "arm/fs_chainmail",
        NOBLE + "arm/fs_bracers",
        NOBLE + "arm/fs_helm",
        NOBLE + "arm/fs_greaves",
        NOBLE + "arm/fw_cloak",
        }));

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
