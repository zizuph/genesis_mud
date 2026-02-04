/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_object(){

set_name("obelisk");
set_adj("ancient");
add_adj("stone");

set_long(
"An ancient monolith, carved of deep gray stone, smooth and\n"
+ "polished. It glimmers in the light, casting off strange prisms\n"
+ "of silvery light. It is covered with runes of silver, in the center\n"
+ "of which is a circle and star.\n");

add_prop(OBJ_I_NO_GET, "It is unmovable.\n");

add_item("runes", "They are ancient letters in silver settings.\n");
add_cmd_item("runes", "read", "@@read_runes");

}

read_runes(){

if(this_player()->query_skill(SS_LANGUAGE)<15){
write("You cannot understand them.\n");
return 1;
}
write("LET THE DEAD LAY IN PEACE\n");
return 1;

}
