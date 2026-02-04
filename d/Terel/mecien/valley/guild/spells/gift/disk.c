inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define EN environment

int t;
init(){
   add_action("do_disk", "rub");
   ::init();
}

stop_fire(object who){
   tell_room(EN(who), "The fire about " + QCTNAME(who) + " dies out.\n", who);
   who->catch_msg("The ancient fire returns home.\n");
   who->remove_prop(OBJ_M_NO_ATTACK);
  who->remove_prop(LIVE_S_EXTRA_SHORT);
   TO->remove_object();
}

do_disk(string str){
  object who;
   if(!str) return 0;
   if(str == "disk"){
      tell_room(EN(TP), QCTNAME(TP) + " is suddenly transfigured in a cloud of fire!\n", TP);
   TP->catch_msg("You are transfigured in the glorious fires of mystery!\n");
      who = TP;
      set_alarm(3.0, 3.0, "fiery", who);
      who->add_prop(OBJ_M_NO_ATTACK, "You would be consumed by the fire!\n");
  who->add_prop(LIVE_S_EXTRA_SHORT, " is surrounded by a blaze of fire");
      set_alarm(33.0, -1.0, "stop_fire", who);
      return 1;
   }
   
}

fiery(object who){
   int n;
   n = random(3);
   if(n > 1){
      tell_room(EN(who), QCTNAME(TP) + " is transfigured in a cloud of fire!\n", TP);
      who->catch_msg("You continue to burn in the flames of glory.\n");
      return 1;
   }
   if(n < 1){
      tell_room(EN(who), QCTNAME(TP) + " is engulfed in the churning fiery cloud!\n", TP);
      who->catch_msg("You revel in the fires of mystery.\n");
      return 1;
   }
   tell_room(EN(who), QCTNAME(TP) + " is swallowed up in the blaze of fire!\n", who);
   who->catch_msg("You feel power from the fire.\n");
   return 1;
}
create_object(){
   set_name("disk");
   add_name("ancient_gift");
   set_adj("fiery");
   set_long("A beautiful gold disk, set with fiery letters.\n");
   add_item("letters", "They seem to almost be made of fire.\n");
   add_cmd_item("letters", "read", "They burn your mind!\n");
}
