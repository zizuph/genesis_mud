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
#define ATT_HORNS    0
#define ATT_CRUSH    1 

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LFPAW    3
#define HIT_RFPAW    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

/* Some random values */
#define RNAME   ({ "bull", "cow", "cow", "calf" })
#define RADJ    ({ "impressive", "black", "brown", "white" })
#define RLONG   ({ \
         "The bull carries two big, white horns. You feel a deep " \
       + "respect for them.\n", \
         "The black cow is almost entirely black, except for a white " \
       + "blemish on the forehead. It is chewing on some straw.\n", \
         "The brown cow is covered with white patches and stares content " \
       + "around.\n", \
         "The white calf looks quite innocent. It is still young and " \
       + "stays close with his mother.\n" })
#define RCON    ({ 22+random(5), 17+random(6), 14+random(8), 9+random(4) })
#define RGENDER ({ G_MALE, G_FEMALE,  G_FEMALE,  G_MALE })
#define RWEIGHT ({ 357, 312, 273, 112 })
create_creature()
{
   int ran;
   ran = random(4);

   if (!IS_CLONE)
      return;
   set_name(RNAME[ran]);
   add_name("_barn_cow_");
   set_race_name(RNAME[ran]);
   set_adj(RADJ[ran]);
   set_gender(RGENDER[ran]);
   set_long(break_string(RLONG[ran],70));

   /* So much for the cow, now we want some combat! */
            /* str dex   con      int wis dis */
   set_stats(({ 17, 11, RCON[ran],  3,  3,  3 }));
   set_hp(10000); /* Heal fully */
   set_alignment(6);

   set_skill(SS_DEFENCE, 6);
   
   set_attack_unarmed(ATT_HORNS,  8, 8,W_IMPALE, 80, "horns");
   set_attack_unarmed(ATT_CRUSH,  8, 8, W_SLASH, 20, "total body weight");

   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
   set_hitloc_unarmed(HIT_LFPAW, ({ 8, 8, 8, 8 }), 15, "left front paw");
   set_hitloc_unarmed(HIT_RFPAW, ({ 8, 8, 8, 8 }), 15, "right front paw");
   set_hitloc_unarmed(HIT_LBPAW, ({ 8, 8, 8, 8 }),  5, "left rear paw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 8, 8, 8, 8 }),  5, "right rear paw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 10, "tail");

   add_prop(CONT_I_WEIGHT, RWEIGHT[ran]*1000);   /* Set weight */
   add_prop(CONT_I_VOLUME, RWEIGHT[ran]*1000);   /* Set volume */
   add_prop(LIVE_I_NEVERKNOWN, 1); /* You don't want to know the cow */

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
              + " moos.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " gazes dreamily at you.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " sniffs at your hand.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " waves " + query_possessive() + " tail.\n");
   return "";
}

make_cnoise() {
   int ran;

   ran = random(4);
   if (ran == 0)
      tell_room(environment(), "The " + query_nonmet_name()
              + " moos aggressively at you.\n");
   if (ran == 1)
      tell_room(environment(), "The " + query_nonmet_name()
              + " threatens you with " + query_possessive() + " horns.\n");
   if (ran == 2)
      tell_room(environment(), "The " + query_nonmet_name()
              + " tries to nail you to the wall.\n");
   if (ran == 3)
      tell_room(environment(), "The " + query_nonmet_name()
              + " bows " + query_possessive() + " head in order to attack.\n");
   return "";
}