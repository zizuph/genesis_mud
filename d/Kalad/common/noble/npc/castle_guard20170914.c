/*
   castle_guard.c
   
   Sarr,
   
   recoded by Fysix, Jan 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";
inherit "/d/Kalad/lib/assist";

#include "default.h"

void
create_kalad_monster()
{
    set_name("guard");
    set_adj("elite");
    set_race_name("human");
    set_short("elite guard of the High-Lord");
    set_long("This is one of the High-Lord's elite home guard. "+
        "He is very well trained and paid. He is in charge of keeping "+
        "the High-Lord's castle safe, so he must be very good. His "+
        "eyes look sharp, his weapons deadly, and his muscles strong.\n");

    set_alignment(500);
    set_knight_prestige(-300);

    add_speak("Don't cause trouble.\n");

    set_stats(({120,120,120,70,70,100}));

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,100);

    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,2);
    add_prop(LIVE_I_NEVERKNOWN,1);
    // I am a Kabal citizen
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    // I will assist Kabal citizens in combat
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    set_act_time(3);
    add_act("scratch chin");
    add_act("emote stares straight ahead.");
    add_act("say Watch yourself, stranger...");
    add_act("say This is the High-Lord's castle.");
    add_act("emote checks on his weapons.");
    add_act("emote checks on his armours.");
    set_cact_time(5);
    add_cact("say I shall protect my High-Lord!");
    add_cact("shout Fool! You will die now!");
    
    add_equipment(({
      NOBLE + "wep/two-handed_longsword",
      NOBLE + "arm/os_helm",
      NOBLE + "arm/os_breastplate",
      NOBLE + "arm/os_bracers",
      NOBLE + "arm/os_greaves",
      NOBLE + "arm/sl_boots",
      }));

    set_default_special(25, W_BLUDGEON, 100, 300, A_BODY);

    set_watch_friends(1);

    /* XP Adjustment, Cotillion 2014-12-02 */
    set_exp_factor(180);

}

// Watch for friends as soon as we move to a new room
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    watch_friends();
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
