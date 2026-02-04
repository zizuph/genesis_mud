/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){

object door;

set_short("Shed");
set_long(
"This old wooden shed smells of fine earth, wild flowers and " +
"the rich scent of herbs. A long bench and table fill this place, " +
"allowing many to work here on horticulture. The walls are pegged " +
"and studded to allow tools and supplies to be hung up. " +
"There is a small well here.\n"
);

add_item("shed", "You stand within this wooden building.\n");
add_item("bench", "it is plain wood and lines up with the table.\n");
add_item("table", "It is a simple long wood table, stained and soiled " +
"with dirt, it looks stable and well used.\n");
add_item("pegs", "They cover the walls.\n");
add_item("studs", "They cover the walls.\n");
add_item("well", "It is a small well, used to water shrubs and " +
"plants stored here. The water looks clean.\n");
door=clone_object(PATH + "sd2");
door->move(this_object());


add_exit(PATH + "rg", "northeast", 0);
  add_exit(PATH + "hive", "northwest", 0);

}


