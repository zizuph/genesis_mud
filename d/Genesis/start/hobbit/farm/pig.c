/*
 * The standard cow for in the barn
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
#define ATT_CRUSH    1 

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LFPAW    3
#define HIT_RFPAW    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

#define RNAME   ({ "boar", "sow", "piglet" })
#define RADJ    ({ ({"brushy","big"}), ({"fat","big"}), "small"})
#define RLONG   ({ \
         "The big boar has brushy hairs on his back and looks at you " \
       + "with its flashy, black eyes.\n", \
         "The big fat sow has had many piglets. She must weigh more than " \
       + "one hundred kilograms.\n", \
         "The small piglet stays close to its mother at all times. " \
       + "Every now and then it squeals happily and plays in the mud.\n" })
#define RCON    ({ 13+random(5), 11+random(6), 6+random(2) })
#define RGENDER ({ G_MALE, G_FEMALE, G_MALE })
#define RWEIGHT ({ 200, 150, 30 })

create_creature()
{
   int ran;
   ran = random(3);

   if (!IS_CLONE)
      return;
   set_name(RNAME[ran]);
   add_name("_barn_pig_");
   set_race_name(RNAME[ran]);
   set_adj(RADJ[ran]);
   set_gender(RGENDER[ran]);
   set_long(break_string(RLONG[ran],70));
   set_alignment(9);

   /* So much for the cow, now we want some combat! */
            /* str dex   con      int wis dis */
   set_stats(({ 17,  7, RCON[ran],  2,  2,  2 }));
   set_hp(10000); /* Heal fully */

   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_TEETH,  8, 8,W_IMPALE, 20, "teeth");
   set_attack_unarmed(ATT_CRUSH,  8, 8, W_SLASH, 80, "total body weight");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
   set_hitloc_unarmed(HIT_LFPAW, ({ 8, 8, 8, 8 }), 15, "left front paw");
   set_hitloc_unarmed(HIT_RFPAW, ({ 8, 8, 8, 8 }), 15, "right front paw");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }),  5, "left rear paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }),  5, "right rear paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   add_prop(CONT_I_WEIGHT, RWEIGHT[ran]*1000);   /* Set weight */
   add_prop(CONT_I_VOLUME, RWEIGHT[ran]*1000);   /* Set volume */
   add_prop(LIVE_I_NEVERKNOWN, 1); /* You don't want to know the pig */

   /* And now make it move every now and then... */
   set_act_time(7 + random(17));
   add_act("@@make_noise");

   set_cact_time(5 + random(5));
   add_cact("@@make_cnoise");
   add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
}

make_noise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " oinks.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " rolls around in the mud.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " sniffs on the floor.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " shrugs " + query_possessive() + " back against the wall.\n");
   return " ";
}

make_cnoise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " growls at you.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " blinks " + query_possessive() + " teeth at you.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " tries to squash you against the wall.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " squeals loudly!\n");
   return " ";
}
