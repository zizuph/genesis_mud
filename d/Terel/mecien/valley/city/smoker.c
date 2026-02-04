inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

create_monster(){

set_race_name("human");
set_name("jenorin");
set_adj("tall");
add_adj("friendly");
set_long(
"A rather sly looking man, he stands tall and has a rather devilish\n"
+"look in his face. Somehow he still manages to keep a friendly\n"
+"presence about himself. He is strong, with long black hair\n"
+"and his eyes are bright green and keen as an eagles.\n"
);

set_alignment(134);
set_stats(random(15) + 11);


set_chat_time(15);
add_chat("Do you ever take a smoke?");
add_chat("In Elnoven we have a lot of liesures");
add_chat("Beware the mystics up on the mountains");

set_act_time(3);
add_act("@@smoke");
add_act("@@ring");

}

smoke(){

tell_room(environment(this_object()),
   QCTNAME(this_object()) + " smokes from his pipe.\n");
return 1;
}

ring(){

tell_room(environment(this_object()),
  QCTNAME(this_object()) + " blows a ring of smoke from his pipe.\n");
return 1;
}


