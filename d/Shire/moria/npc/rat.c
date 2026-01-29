/*
 *  Rat-thing for Mines of Moria
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BITE     0
#define ATT_CLAWS    1

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LEGS     3
#define HIT_NOSE     4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

/* Some random values */
#define RNAME	({ "mouse", "rat", "rat", "rat" })
#define RADJ	({ ({"big","beige"}), "white", "brown", "black" })
#define RLONG   ({ \
         "The big red mouse has big claws with which he can scratch " \
       + "your eyes out if you want to fight.\n", \
         "The rat picks every now and then a bit of gore from its teeth.\n", \
         "The rat picks every now and then a bit of gore from its teeth.\n", \
         "The rat wobbles clumsily around.\n", })
#define RCON	({ 8+random(5), 6+random(5), 6+random(5), 6+random(5) }) 
#define RGENDER	({ G_MALE, G_FEMALE,  G_FEMALE,  G_FEMALE })

create_creature()
{
   int ran;
   ran = random(4);

   if (!IS_CLONE)
      return;
   set_name(RNAME[ran]);
   set_race_name(RNAME[ran]); 
   set_adj(RADJ[ran]);
   set_gender(RGENDER[ran]);
   set_long(break_string(RLONG[ran],70));
   set_alignment(-100 + random(50));

   add_prop(CONT_I_WEIGHT, 3000);   /* 3.0 Kg  */
   add_prop(CONT_I_VOLUME, 2500);   /* 2.5 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);  /* You'll never know it */

   /* So much for the rat, now we want some combat! */
            /* str dex   con      int wis dis */
   set_stats(({  8,  8, RCON[ran],  1,  1,  8 }));
   set_hp(10000); /* Heal fully */

   set_skill(SS_DEFENCE, 5);

   set_attack_unarmed(ATT_BITE ,  24, 25,W_IMPALE, 70, "bite");
   set_attack_unarmed(ATT_CLAWS,  20, 22, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 20, "body");
   set_hitloc_unarmed(HIT_LEGS,  ({ 8, 8, 8, 8 }), 25, "legs");
   set_hitloc_unarmed(HIT_NOSE, ( { 8, 8, 8, 8 }), 25, "nose");
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

 if (CAN_SEE_IN_ROOM(this_player()))
 {
   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " pecks some carnage from the floor.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " steps around you.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " eyes you carefully.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " cleans " + query_possessive() + " teeth.\n");
 }
   return "";
}

make_cnoise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " attempts to run away.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " cackles loudly!\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " tries to bite your leg.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " crawls up your leg.\n");
   return "";
}

