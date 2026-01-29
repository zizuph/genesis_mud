/*
 *  Small snake for the farmyard
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
#define ATT_BITE     0
#define ATT_SLASH    1 

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2

create_creature()
{
   if (!IS_CLONE)
      return;
   set_name("snake");
   set_race_name("snake"); 
   set_adj(({"small","green"}));
   set_long(break_string(
      "The small green snake is not venomous, but it can bite you. It "
    + "hisses in your direction.\n",70));

   set_alignment(-20);
   set_stats(({ 1, 1, 1, 15, 15, 5 }));

   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_BITE ,  8, 8,W_IMPALE, 40, "teeth");
   set_attack_unarmed(ATT_SLASH,  8, 8, W_SLASH, 60, "tail");

   set_hitloc_unarmed(HIT_HEAD, ({ 2, 2, 2, 2  }), 20, "head");
   set_hitloc_unarmed(HIT_BODY, ({ 8, 8, 8, 8 }), 60, "body");
   set_hitloc_unarmed(HIT_TAIL, ({ 8, 8, 8, 8 }), 20, "tail");

   add_prop(CONT_I_WEIGHT, 3000);   /* 3.0 Kg  */
   add_prop(CONT_I_VOLUME, 2500);   /* 2.5 Ltr */
   add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
}