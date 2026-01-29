/* an npc coded by Elizabeth Cook/Mouse, September 1996 */

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
     add_name("kit");
     set_living_name("mouse:beaverkit");
     set_race_name("beaver");
     set_short("beaver kit");
     set_long("A beaver young born this season. It likes to play "+
          "with the other kits. It is learning beaver behavior by "+
          "mimicking its parents and the yearlings.\n");
     set_gender(G_NEUTER);
     set_alignment(ALIGN_SWEET);
     set_stats(({10,10,5,5,10,5}));
     set_skill(SS_DEFENCE,10);
     set_skill(SS_UNARM_COMBAT,10);
     add_prop(NPC_I_NO_RUN_AWAY, 1);
     add_prop(LIVE_I_NEVERKNOWN, 1);
     add_prop(NPC_I_NO_LOOKS, 1);
     
     set_act_time(10);
     add_act("emote plays with the other kits.");
     add_act("emote grunts softly.");
     

   set_attack_unarmed(A_TEETH, 8, 6, W_IMPALE, 80, "incisors");

   set_attack_unarmed(A_TAIL, 6, 8, W_BLUDGEON, 20, "tail");


   set_hitloc_unarmed(H_HEAD, 6, 30, "head");
   set_hitloc_unarmed(H_BODY, 6, 50, "body");
   set_hitloc_unarmed(H_TAIL, 3, 10, "tail");
   set_hitloc_unarmed(H_LEGS, 3, 10, "legs");

     add_prop(CONT_I_WEIGHT, 20000);
     add_prop(CONT_I_HEIGHT, 60);
     add_prop(CONT_I_VOLUME, 3000);
     add_prop(CONT_I_MAX_WEIGHT, 25000);
     add_prop(CONT_I_MAX_VOLUME, 3500);


}

attacked_by(object ob)
{
   int i,num;
   write(TO->query_The_name(ob) + " slaps its tail in alarm.\n");
   all_inventory(environment())->help_me(ob,this_object());
   ::attacked_by(ob);
}

help_me(object target,object friend)
{
   if((TO != friend) && (TO->query_attack() != target))
   {
      tell_object(target,TO->query_The_name(target)+" attacks you!\n");
      this_object()->attack_object(target);
   }
}
