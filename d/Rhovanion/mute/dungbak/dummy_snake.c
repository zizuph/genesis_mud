inherit "/std/monster";
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
void
create_monster() {
   set_name("snake");
   add_name("dummy_snake");
   set_living_name("dummy_snake");
   set_race_name("snake");
   set_long("Coiled snake\n");
   set_skill(SS_HIDE, 101);
   add_prop(OBJ_I_HIDE, 100);
   trig_new("%s 'throws' 'a' 'javelin' 'at' 'you' 'and' 'hits' %s",
      "react_destruct");
   set_alarm(0.0,0.0,"snake_hide");
}
public int
snake_hide() {
   command("hide,1");
   return 1;
}
public void
react_destruct(object thrower, string dummy) {
   set_alarm(0.0,0.0,"react_destruct2");
}
public void
react_destruct2() {
   command("emote falls off the lever and splooshes into the water.");
   remove_object();
}
