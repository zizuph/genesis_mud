inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/obj/"
#define TP this_player()
#define TO this_object()

#define EN environment

init(){
   add_action("smell", "smell");
   ::init();
}

undead(object who){
   if(who->query_prop(LIVE_I_UNDEAD)){
      who->add_panic(5);
      who->add_mana(-10);
      tell_room(EN(who), QCTNAME(who) + " thrashes about and snarls.\n", who);
      who->catch_msg("The incense seems to weaken you.\n");
   }
}

create_object(){
   
   set_name("_incense_cloud_");
   add_prop(OBJ_M_NO_GET, 1);
   set_no_show(1);
   
}

do_time(){
  set_alarm(240.0, -1.0, "remove_cloud");
}

remove_cloud(){
   TO->remove_object();
}

smell(){
   TP->catch_msg("You smell incense, made of sandalwood and myrrh.\n");
   return 1;
}

enter_env(object inv, object from){
   ::enter_env(inv, from);
   set_alarm(2.0, 15.0, "mesg");
}

leave_env(object inv, object to){
  ::enter_env(inv, to);
   tell_room(inv, "The smell of incense fades from this place.\n");
}


mesg(){
   int n;
   n = random(10);
   switch(n){
      case 0: tell_room(EN(TO), "A haze of incense passes over you.\n");
      break;
      case 1: tell_room(EN(TO), "You see lingering clouds of incense rolling about.\n");
      break;
      case 2: tell_room(EN(TO), "You inhale a portion of incense, smelling of sandalwood and myrrh.\n");
      break;
      case 3: tell_room(EN(TO), "Incense floats upwards, like a spirit destined for the heavens.\n");
      break;
      case 4: tell_room(EN(TO), "A cloud of incense floats about.\n");
      break;
      case 5: tell_room(EN(TO), "Your vision becomes hazy, as a cloud of incense passes by you.\n");
      break;
      case 6: tell_room(EN(TO), "Drifting incense lingers throughout this place.\n");
      break;
      case 7: tell_room(EN(TO), "As if beckoned by some great power, a cloud of incense rises upward.\n");
      break;
      case 8: tell_room(EN(TO), "A powerful smell of incense fills your nose, being sandalwood and myrrh.\n");
      break;
      case 9: tell_room(EN(TO), "A wisp of incense seems to linger about you.\n");
      break;
   }
   
   map(all_inventory(EN(TO)), undead);
}

