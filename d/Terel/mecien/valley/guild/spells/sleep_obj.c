inherit "/std/paralyze";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define EN environment
#define TO this_object()
#define SUBLOC "sleep_subloc"
object gSleeper = 0;

create_paralyze(){
   
   set_name("_sleep_");
   set_stop_verb("awaken");
   set_stop_message("You wake yourself from the powerful sleep.\n");
   set_fail_message("You are in a state of sleep, you will need to awaken before you can do anything.\n");
   set_stop_fun("awake");
    set_stop_object(TO);
   set_remove_time(600);
   
   
}

show_subloc(string subloc, object car, object for_obj){
   string str;
   if(car->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if(for_obj == car)
      str = "You are asleep.\n";
   else
      str = capitalize(car->query_pronoun()) + " is asleep.\n";
   return str;
}

enter_env(object inv, object to){
   ::enter_env(inv, to);
   if(living(inv)){
      inv->catch_msg("You fall into a deep sleep.\n");
   tell_room(EN(inv), QCTNAME(inv) + " falls into a deep sleep.\n", inv);
      inv->add_subloc(SUBLOC, TO);
      inv->add_prop(LIVE_S_EXTRA_SHORT, " is sleeping");
    gSleeper = inv;
   }
}

leave_env(object inv, object to){
   ::leave_env(inv, to);
   if(living(inv)){
      inv->remove_prop(LIVE_S_EXTRA_SHORT);
      inv->remove_subloc(SUBLOC, TO);
   }
}


awake(){
   object EP;
    EP = gSleeper;
  if(!MEMBER(EP)){
   if(EP->query_stat(SS_DIS) + random(100) < 150){
      EP->catch_msg("You cannot seem to awaken.\n");
      tell_room(EN(EP), QCTNAME(EP) + " seems restless in sleep.\n", EP);
      return 1;
   }
   }
   
   tell_room(EN(EP), QCTNAME(TP) + " awakens from sleeping.\n", EP);
  return 0;
}


