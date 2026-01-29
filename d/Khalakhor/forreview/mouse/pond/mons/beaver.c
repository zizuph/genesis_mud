/* npc coded by Elizabeth Cook/Mouse, September 1996 */

inherit "/std/npc";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <const.h>
#include <alignment.h>
#include "../../mouse.h"

#define A_TEETH  0
#define A_TAIL   1

#define H_HEAD   0
#define H_BODY   1
#define H_TAIL   2
#define H_LEGS   3

   void create_npc() {
     set_name("beaver");
     set_living_name("mouse:beaver");
     set_race_name("beaver");
     set_adj("chestnut-brown");
     set_short("chestnut-brown beaver");
     set_long("A mammoth rodent with thick, soft fur of a deep, "+
          "rich brown hue. He has large, sharp incisors with which "+
          "he fells trees and feasts on tasty leaves and bark. "+
          "His powerful tail is large, flat and scaly. He has strong, "+
          "webbed hind feet and tiny eyes. He has a keen sense of "+
          "hearing and even keener sense of smell.\n");
     set_gender(G_MALE);
     set_alignment(ALIGN_SWEET);
     set_stats(({25,20,10,10,20,15}));
     set_skill(SS_DEFENCE,20);
     set_skill(SS_UNARM_COMBAT,20);
     add_prop(NPC_I_NO_RUN_AWAY, 1);
     add_prop(LIVE_I_NEVERKNOWN, 1);
     add_prop(NPC_I_NO_LOOKS, 1);     
     
     set_act_time(10);
     add_act("emote nibbles the bark from a twig.");
     add_act("emote grooms his fur thoroughly with his front paws.");
     add_act("emote grunts softly.");

     set_cact_time(10);
     add_cact("emote slaps at you with his tail.");


   set_attack_unarmed(A_TEETH, 15,10, W_IMPALE, 80, "sharp incisors");

   set_attack_unarmed(A_TAIL, 10,15, W_BLUDGEON, 20, "powerful tail");


   set_hitloc_unarmed(H_HEAD,10, 30, "head");
   set_hitloc_unarmed(H_BODY,10, 50, "body");
   set_hitloc_unarmed(H_TAIL,5, 10, "tail");
   set_hitloc_unarmed(H_LEGS,5, 10, "legs");

     add_prop(CONT_I_WEIGHT, 55000);
     add_prop(CONT_I_HEIGHT, 150);
     add_prop(CONT_I_VOLUME, 5000);
     add_prop(CONT_I_MAX_WEIGHT, 75000);
     add_prop(CONT_I_MAX_VOLUME, 6000);


}

