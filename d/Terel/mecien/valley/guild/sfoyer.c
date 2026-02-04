inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/guild/"
#define EN environment
#define TP this_player()


create_room(){
set_short("Holy Chamber");
set_long(
"Amid the whispering shadows does this chamber rise up, carved into the" +
" deep places of the world, of some strange aquamarine stone. It is altogether cold "
+"and lifeless, still and unmoving. A large obelisk with gold letters stands in the " +
"center of this place. There is an archway leading to the north.\n"
);

add_item("archway", "It is made of the same aquamarine stone. Plain and smooth.\n");
add_item("obelisk", "It is made of marble set with gold lettering.\n");
add_cmd_item("obelisk", "read", "WE WHO ARE FAITHFUL SHALL ENDURE FOREVER\n");
add_item("stone", "It is a strange aquamrine stone, soft and smooth.\n");

  add_exit(PATH + "seal_chamber", "north", 0);
  add_exit(PATH + "ss3", "west", 0);
}

