inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Street");
set_long(
"Fog rolls over the cobblestone of this northern street, hiding most\n"
+ "everything, except the edges of buildings and sparkling rooftops. " +
"A small dark building stands north from here, a large wood building to the southwest, a large gray stone building is northwest.\n"
);

add_item("building", "It is a small dark building, looking almost like a mausoleum.\n");
add_item("cobblestone", "It covers the streets.\n");
add_item("fog", "Like a warding mantle, it holds this place in its presence.\n");
add_exit(PATH + "street4", "south", 0);
add_exit(PATH + "chapel", "north", 0);
add_exit(PATH + "monastery", "northwest", 0);
add_exit(PATH + "street13", "northeast", 0);
add_exit(PATH + "dist", "southwest", 0);


}

