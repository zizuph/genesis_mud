inherit "std/monster";
#include "defs.h";
#include <macros.h>
#include <stdproperties.h>

#define TO  this_object()
create_monster(){
   set_race_name("sylph");
   set_name("iwilista");
   set_short("sylph");
   set_long(
   );
   
   set_alignment(343);
    set_gender(1);
   
   set_chat_time(2);
   add_chat("The forest is so beautiful!");
   add_chat("If you seek the Order, find the keeper in the waters of the shrine");
    add_chat("Pray in honour of the Ancient Ones");
    add_chat("Happy are we who live in the shadow of the mystic ways");
    add_chat("Be joyful and sing");
   
     set_act_time(5);
     add_act("smile");
   add_act("@@singo");
   add_act("@@dances");
   add_prop(OBJ_I_NO_ATTACK, "@@bye");
   
}
dances(){
 tell_room(environment(TO), QCTNAME(TO) + " joyously dances about.\n");
  return 1;
}
singo(){
tell_room(environment(TO), QCTNAME(TO) + " sings out in a heavenly voice:\n" +
    "  Within the ways of weeping worlds,\n" +
    "  abides a peace that calms the soul.\n" +
     " Pray in the name of the Ancient Ones,\n" +
   "  by their hands shall all things be done.\n"
   );
  return 1;
}

bye(){
   TO->command("say How very evil of you!");
   tell_room(environment(TO), QCTNAME(TO) + " flies away in a sparkling light.\n");
   remove_object();
}

