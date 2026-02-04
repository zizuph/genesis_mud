/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/"

init(){
add_action("pray", "pray");
::init();
}

pray(){
write("You kneel down and pray.\n");
say(QCTNAME(this_player()) + " kneels down and prays.\n");
return 1;
}

reset_room(arg){
}

create_room(){

object door;

set_short("Holy Chapel of Life");
set_long(
"Vaulted in silver, this small chamber stands in ancient solemnity\n"
+"and solmen grace. Its walls of ancient stone are of pure white marble,\n"
+"the floor of dark silver gray stone. From the ceiling are suspended\n"
+"hundreds of bright candles, set in silver lamps. A small white altar\n"
+"stands in the center of the chamber.\n"
);

add_item("candles", "They are hung from the ceiling in silver lamps.\n");
add_item(({"silver lamps", "lamps"}), "They are simple lamps of silver,\n"
+ "housing bright candles.\n");
add_item("floor", "It is dark gray stone.\n");
add_item(({"ceiling", "vault", "dome"}), "It is made of silver, this vaulted\n"
+ "ceiling, inscribed with many runes.\n");
add_cmd_item(({"ceiling", "runes"}), "read",
 "WHEN TRUTH BECOMES LIFE, THEN LIFE BECOMES TRUTH\n");
add_item("altar", "It is a simple block of pure white marble.\n");
door=clone_object(PATH + "ldoor1");
door->move(this_object());
add_exit(PATH + "lh", "east", 0);

reset_room();
}

