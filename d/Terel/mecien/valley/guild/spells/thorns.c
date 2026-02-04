inherit "/std/object";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define EN environment
#define TO this_object()
#define TP this_player()
#define QP query_possessive()

if_living(object who){
   if(living(who)){
      if(who->query_prop("blessed")) return 0;
      set_alarm(3.0, -1.0, "start_attack", who);
   }
}

start_attack(object who){
   
   who->catch_msg("The shadowy black thorns seem to shift about, pricking you with its barbed tendrils.\n");
   tell_room(EN(TO), "The shadowy black thorns seem to shift about, in the process pricking " + QTNAME(who) + " with its barbed tendrils.\n", who);
   who->add_mana(-1);
   who->reduce_hit_point(3);
   set_alarm(5.0, -1.0, "continue_attack", who);
}

continue_attack(object who){
   int n;
   if(present(who, EN(TO))){
  if(who->query_prop("blessed") < 1){
         n = random(4);
         if(n == 0){
            who->catch_msg("The shadowy black thorns pierce your flesh!\n");
            tell_room(EN(TO), "The shadowy black thorns pierce the flesh of " + QTNAME(who) + "!\n", who);
            who->reduce_hit_point(3);
            who->add_mana(-1);
         }
         if(n == 1){
            who->catch_msg("A sudden movement of the thorns knocks you deep into its midst, pricking you with many of its spines!\n");
            who->reduce_hit_point(12);
            who->add_mana(-1);
            tell_room(EN(who), "A sudden movement of the thorns causes " + QTNAME(who) + 
               " to fall back deep into its midst, upon many of the sharp spines!\n", who);
         }
         if(n == 2){
            who->catch_msg("The shadowy black thorns prick at your body.\n");
            who->reduce_hit_point(3);
            who->add_mana(-1);
            tell_room(EN(who), "The shadowy black thorns prick at " + QTNAME(who) + ".\n", who);
         }
         if(n == 3){
            tell_room(EN(who), "The deeply thorns wrap around " + QTNAME(who) + 
               ", impaling " + who->query_objective() + ".\n", who);
            who->catch_msg("The deadly thorns wrap around you, impaling your body.\n");
            who->reduce_hit_point(6);
            who->add_mana(-1);
         }
         
   who->add_panic(1);
         set_alarm(5.0, -1.0, "continue_attack", who);
         
      }
   }
}








init(){
   map(all_inventory(EN(TO)), if_living);
}

create_object(){
   
   set_name("thorns");
   add_name("mass");
   set_adj(({"mass of", "shadowy", "black" }));
   add_name("mass of thorns");
   add_name("mystic_thorns");
   add_name("nether_thorns");
   
   set_short("mass of shadowy black thorns");
   
   set_long(
      "A gigantic mass of twisting thorns, ominous and dark, as if they are " +
      "not altogether of living substance. Consisting of long black vines, " +
      "covered with long, extremely sharp needle-like thorns." +
      "\n");
   
  add_prop(OBJ_M_NO_GET, "You prick your hand in the attempt!\n");
   add_prop(OBJ_I_WEIGHT, 999999);
add_prop(OBJ_I_VOLUME, 999999);
add_item("thorn", "An extremely sharpy black thorn growing of the tendrils of the great mass of shadowy black thorns.\n");
  add_item("tendrils", "Vines that seem almost like shadowy arms, stretching forth to the reaches of light.\n");
   
}




