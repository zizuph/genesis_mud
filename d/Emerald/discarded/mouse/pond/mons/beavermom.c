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
     set_living_name("mouse:beavermom");
     set_race_name("beaver");
     set_adj(({"light","brown"}));
     set_short("light brown beaver");
     set_long("A mammoth rodent with thick, soft, light brown fur. "+
          "She has large, sharp incisors with which she fells trees "+
          "and feasts on tasty leaves and bark. Her powerful tail is "+
          "large, flat and scaly. She has strong, webbed hind feet and "+    
          "tiny eyes. She has a keen sense of hearing and even "+           
          "keener sense of smell.\n");
     set_gender(G_FEMALE);
     set_alignment(ALIGN_SWEET);
     set_stats(({20,15,10,10,20,15}));
     set_skill(SS_DEFENCE,15);
     set_skill(SS_UNARM_COMBAT,15);
     add_prop(NPC_I_NO_RUN_AWAY, 1);
     add_prop(LIVE_I_NEVERKNOWN, 1);
     add_prop(NPC_I_NO_LOOKS, 1); 
     
     set_act_time(10);
     add_act("emote anxiously watches her young.");
     add_act("emote grooms her fur thoroughly with her front paws.");
     add_act("emote grunts softly.");

     set_cact_time(10);
     add_cact("emote slaps at you with her tail.");


   set_attack_unarmed(A_TEETH,12,10, W_IMPALE, 80, "sharp incisors");

   set_attack_unarmed(A_TAIL,10,12, W_BLUDGEON, 20, "powerful tail");


   set_hitloc_unarmed(H_HEAD, 8, 30, "head");
   set_hitloc_unarmed(H_BODY, 8, 50, "body");
   set_hitloc_unarmed(H_TAIL, 3, 10, "tail");
   set_hitloc_unarmed(H_LEGS, 3, 10, "legs");

     add_prop(CONT_I_WEIGHT, 45000);
     add_prop(CONT_I_HEIGHT, 120);
     add_prop(CONT_I_VOLUME, 4500);
     add_prop(CONT_I_MAX_WEIGHT, 65000);
     add_prop(CONT_I_MAX_VOLUME, 5500);


}

attacked_by(object ob)
{
   int i,num;
   write(TO->query_The_name(ob)+ " slaps her tail in alarm.\n");
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
