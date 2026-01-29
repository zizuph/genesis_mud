// inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include <wa_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
 
inherit "/d/Genesis/steed/steed.c";

create_steed()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;

   set_name("bill");
   set_adj(({"calm","demure"}));
    set_alignment(200 + random(50));
   set_race_name("pony"); 
   set_long("This pony looks lost and forlorn.\n"
	    + "He looks rather malnourished.\n");

   add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

   set_stats(({ 14, 15, 12, 18, 12, 40}));
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_SNEAK, 100);
   set_skill(SS_HIDE, 100);
/* Bill must have known these to get back from Moria uneaten */

   set_attack_unarmed( 0, 10, 20, W_IMPALE, 50, "teeth");
   set_attack_unarmed( 1, 20, 10, W_BLUDGEON, 25, "left hoof");
   set_attack_unarmed( 2, 20, 10, W_BLUDGEON, 25, "right hoof");

   set_hitloc_unarmed( 0, ({ 30, 25, 25, 5 }), 20, "head");
   set_hitloc_unarmed( 1, ({ 15, 23, 20, 5 }), 50, "body");
   set_hitloc_unarmed( 2, ({ 40, 12, 10, 5 }), 30, "legs");

/*
   set_pick_up(0);

   set_aggressive(0);
   set_attack_chance(0);
*/

   set_hp(500); /* Heal fully */

   /* Actions */
   set_act_time(5);
   add_act("emote walks around you in a circle, eyeing you curiously.");
   add_act("emote whinnies pitifully.");
   add_act("emote shifts his weight from one side to the other.");
   add_act("nudge all");
   add_act("emote paws the ground repeatedly.");

   /* Combat actions */
   set_cact_time(1);
   add_cact("west");
   add_cact("north");
   add_cact("south");
   add_cact("east");
   add_cact("sneak north");
   add_cact("sneak south");
   add_act("sneak east");
   add_cact("sneak west");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */


}



/* For the solamnic Knights */

query_knight_prestige() { return(-25); }
