/*
 * The watchdog of the farm
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_TEETH    0
#define ATT_CLAWS    1 

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LFPAW    3
#define HIT_RFPAW    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

create_creature()
{
   if (!IS_CLONE)
      return;
   set_name("dog");
   set_living_name("dog");
   set_race_name("dog"); 
   set_adj(({"vicious","brown","guard"}));
   set_long(break_string(
      "The vicious brown dog growls at you as you examine it. "
    + "It sure looks like he is very capable of doing his job: "
    + "keeping people away from the yard.\n",70));

   set_stats(({ 20, 20, 36, 20, 20,100 }));
   set_hp(10000); /* Heal fully */
   set_alignment(-20);

   set_skill(SS_DEFENCE, 25);
   
   set_attack_unarmed(ATT_TEETH,  8, 8,W_IMPALE, 70, "teeth");
   set_attack_unarmed(ATT_CLAWS,  8, 8, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
   set_hitloc_unarmed(HIT_LFPAW, ({ 8, 8, 8, 8 }), 15, "left front paw");
   set_hitloc_unarmed(HIT_RFPAW, ({ 8, 8, 8, 8 }), 15, "right front paw");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }),  5, "left rear paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }),  5, "right rear paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   add_prop(CONT_I_WEIGHT, 57463);   /* 50 Kg  */
   add_prop(CONT_I_VOLUME, 56453);   /* 50 Ltr */
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
}
