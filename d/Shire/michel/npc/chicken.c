/*
 *  Chicken for in the barn
 */

/* Copied from the one in /d/Genesis/start/hobbit/farm, */
/* Dunstable, July 1994 */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BEAK     0
#define ATT_CLAWS    1

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LWING    3
#define HIT_RWING    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

/* Some random values */
#define RNAME	({ "rooster", "chicken", "chicken", "chicken" })
#define RADJ	({ ({"big","red"}), "white", "brown", "black" })
#define RLONG   ({ \
         "The big red rooster has big claws with which he can scratch " \
       + "your eyes out if you want to fight it.\n", \
         "The chicken picks every now and then a corn from the ground.\n", \
         "The chicken picks every now and then a corn from the ground.\n", \
         "The chicken moves clumsily around.\n", })
#define RCON	({ 8+random(5), 6+random(5), 6+random(5), 6+random(5) }) 
#define RGENDER	({ G_MALE, G_FEMALE,  G_FEMALE,  G_FEMALE })

create_creature()
{
   int ran;
   ran = random(4);

   if (!IS_CLONE)
      return;
   set_name(RNAME[ran]);
   add_name("_barn_chicken_");
   set_race_name(RNAME[ran]); 
   set_adj(RADJ[ran]);
   set_gender(RGENDER[ran]);
   set_long(break_string(RLONG[ran],70));

   add_prop(CONT_I_WEIGHT, 3000);   /* 3.0 Kg  */
   add_prop(CONT_I_VOLUME, 2500);   /* 2.5 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);  /* You'll never know it */

   /* So much for the chicken, now we want some combat! */
            /* str dex   con      int wis dis */
   set_stats(({  8,  8, RCON[ran],  1,  1,  8 }));
   set_hp(10000); /* Heal fully */

   set_skill(SS_DEFENCE, 5);

   set_attack_unarmed(ATT_BEAK ,  8, 8,W_IMPALE, 70, "beak");
   set_attack_unarmed(ATT_CLAWS,  8, 8, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 20, "body");
   set_hitloc_unarmed(HIT_LWING, ({ 8, 8, 8, 8 }), 25, "left wing");
   set_hitloc_unarmed(HIT_RWING, ({ 8, 8, 8, 8 }), 25, "right wing");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }),  5, "left paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }),  5, "right paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   /* And now make it move every now and then... */
   set_act_time(7 + random(17));
   add_act("@@make_noise");

   set_cact_time(5 + random(5));
   add_cact("@@make_cnoise");
}

make_noise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " pecks some corns from the floor.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " steps around you.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " sees another corn to pick.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " flaps " + query_possessive() + " wings.\n");
   return "";
}

make_cnoise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " attempts to fly away.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " cackles loudly!\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " tries to run away.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " pecks at your legs.\n");
   return "";
}

