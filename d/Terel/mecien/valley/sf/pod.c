inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>


#define PATH "/d/Terel/mecien/valley/sf/"
#define ENV environment
#define TO this_object()


create_object(){
   
   int n;
   
   set_name("pod");
   set_adj("black");
   set_short("black shadowy pod");
   set_long("A strange black pod, leathery and silky, like a cocoon. But a\n"
  +"foul aura emanates from it.\n");
   
   
   
  add_prop(OBJ_M_NO_GET, "The dark pod burns your hands with a powerful cold.\n");
   add_prop(OBJ_M_NO_ATTACK, "It seems to be unharmed by attacks.\n");
   
   n = random(20) + 5;
  set_alarm(itof(random(60) + 10), -1.0, "awake");
    set_alarm(itof(random(5) + 5), -1.0, "grow");
   
}

grow(){

   tell_room(ENV(TO), "The shadowy pod pulses and begins to grow.\n");
   
}

awake(){
   object shadow;
   
   seteuid(getuid());
   
   shadow= clone_object(PATH + "dc");
   tell_room(ENV(TO), "The dark pod bursts open and a creature of darkness comes forth!\n");
  shadow->move(ENV(TO));
   remove_object();
   
}


