inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/mountains/"

reset_room(arg){
object corpse, axe, ice;

if (!present("ice"))
{
    ice = clone_object("/d/Terel/cedric/thane/ice");
    ice->move(this_object());
}
corpse = present("corpse");
if (corpse) corpse->remove_object();
if(!present("corpse"))
{
    corpse = clone_object("/d/Terel/cedric/thane/ice_corpse");
    corpse->move(this_object());
}
}

create_room(){
set_short("Chasm Bottom");
set_long(
"Howling in the winds, this icy pit is the bottom of an immense\n"
+ "chasm. The edges of the chasm are high above, strung with\n"
+ "myriads of icicles. Some of the icicles are so long that they\n"
+ "hang to the bottom of the chasm, transforming this place, as if\n"
+ "they are pillars of some majestic hall. All the ice sparkles\n"
+ "and glitters in the light.\n"
);

add_exit(PATH + "chasm1", "south", 0);
add_exit(PATH + "chasm3", "northeast", 0);

add_item("icicles", "These icicles hang from high above, around the\n"
 +"edge of the chasm, some descend all the way down here.\n"
);
add_item("chasm", "It is immense, icy and forsaken.\n");
add_item("hole", "It is a strange ascending tunnel.\n");
add_cmd_item("hole", "enter", "You cannot go up, its too icy.\n");

reset_room();
}
