inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){
set_short("Street");
set_long(
"Dark and foggy, this part of the street winds through the " +
"northern parts of town. It is cobble stone, worn smooth. " +
"A large building stands to the east, a small one to the north." +
"A bright cherry-wood building is to the northwest." +
"\n");

add_item("street", "It is dark, paved with cobblestones worn smooth.\n");
add_item(({"building", "east building"}),
  "It is a fairly large building with a high roof.\n");
add_item(({"small building", "north building"}), "It is rather small and made of rounded stones.\n");
add_item(({ "bright building", "bright cherry-wood building", 
   "cherry-wood building" }), "It is a medium size building made from a bright and cheerful cherry-wood.\n");

add_exit(PATH + "street6", "southwest", 0);
add_exit(PATH + "adv_guild", "east", 0);
add_exit(PATH + "library", "north", 0);
add_exit(PATH + "merc", "northwest", 0);

}

