/*
Segoy 950206 Shark attack!
paralyze attack from Rhovanion domain.
skin handlrern by Gresse!
*/

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include "../defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>



#define A_BITE  0
#define H_HEAD 0
#define H_BODY 1



void create_creature()
{
   set_name("shark");
   add_adj("vicious");
   add_adj("white");
   set_race_name("shark");
   set_short("vicious white shark");
   set_long("The shark is jumping right out from the water " +
      "aiming his terrible jaw at you! Seems that you "+
      "somehow has offended it. \n");
   set_gender(G_NEUTER);
   
   /*
   str, con, dex, int, wis, dis
   somebody tell me if these are good values
      */
   
  set_stats(({ 210, 200, 210, 40, 31, 300}));
  
  set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
  set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }), 72, "body");
  
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_UNARM_COMBAT, 100);
  set_attack_unarmed(A_BITE, 35, 70, W_IMPALE, 50, "vicious bite");
  set_attack_unarmed(A_BITE, 35, 70, W_SLASH, 50, "sharp teeth");
  
  set_cact_time(5);
  add_cact("emote makes an attack against the boat!");
  add_cact("emote jumps up, out of the water aiming for you!");
  add_cact("emote gnabs at you!");
  
  
  add_prop(LIVE_I_NEVERKNOWN, 1);
  
  set_aggressive(1);
  add_leftover(INMOST_SEA+"obj/shark-skin","skin",1,"",0,1);
}



