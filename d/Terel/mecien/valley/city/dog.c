/*
/doc/examples/mobiles/tiger2.c

JnA 920111

A sample creature 

This creature uses no tools for fighting. 
It inherits the routines for unarmed combat.

This is a rather tough beast. You need on average 30 or more in your
stats to handle it. You also need wc30 weapon with skills to match.

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1


create_creature()
{
   set_name("dog"); 
   set_race_name("dog");
   set_adj("large");
   add_adj("sheep");
   set_long("It is a friendly looking animal, white and gray fur.\n");
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 23, 21, 31, 5, 5, 21}));
   set_hp(2000);
   
   set_skill(SS_DEFENCE, 20);
   set_random_move(10);
   
   
   enable_commands();
   
   set_act_time(1);
   add_act("@@bark");
   add_act("@@roll");
   set_follow("mecien");
   
   set_attack_unarmed(A_BITE,  32, 28, W_IMPALE, 100, "teeth");
   
   set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15, 5 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 15, 5 }), 80, "body");
}


init_living(){
   add_action("pet", "pet");
   ::init_living();
}

pet(string str){
   int align;
   
   if(!str) return 0;
  if(str == "dog"){
  write("You pet the dog.\n");
  say(QCTNAME(this_player()) + " pets the dog.\n");
      align= this_player()->query_alignment();
      if(align > 50){
         wag();
         return 1;
      }
      if(align < -10){
         this_object()->command("growl");
         this_object()->command("kill " + this_player()->query_real_name());
         return 1;
      }
      bark();
      return 1;
   }
}

   
   bark(){
      tell_room(environment(this_object()), QCTNAME(this_object()) + " barks loudly!\n");
      return 1;
   }
   
   wag(){
      tell_room(environment(this_object()), QCTNAME(this_object()) + " wags its tail contently!\n");
      return 1;
   }
   
