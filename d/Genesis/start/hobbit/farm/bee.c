/*
 *  Small bee for in the pasture 
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
#define ATT_STING    0

#define HIT_BODY     0

create_creature()
{
   if (!IS_CLONE)
      return;
   set_name("bee");
   set_living_name("bee");
   set_race_name("bee"); 
   set_long("The bee buzzes happily while it flies from flower to flower.\n");
   set_gender(G_FEMALE);
   set_alignment(-2);

   set_stats(({ 2, 2, 2, 15, 15, 5 }));

   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_STING,  8, 8,W_IMPALE, 100, "sting");

   set_hitloc_unarmed(HIT_BODY, ({ 8, 8, 8, 8 }), 100, "body");

   add_prop(CONT_I_WEIGHT, 50);   /* 0.050 Kg  */
   add_prop(CONT_I_VOLUME, 50);   /* 0.050 Ltr */
   add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
}