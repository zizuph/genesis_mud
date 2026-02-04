inherit "/std/creature";
inherit "/std/act/chat";
#include <macros.h>
#include <stdproperties.h>

create_creature(){

set_race_name("demon");
set_name("demon");
set_living_name("feeder");
set_adj("tiny");
add_adj("winged");


set_chat_time(1);
add_chat("Feed us Papa!");

}
