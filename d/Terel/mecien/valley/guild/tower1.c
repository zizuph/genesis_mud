/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Tower");
set_long("This circular room is the ground floor of what seems to be\n"
   +"a large tower. The walls are made from small rounded grey\n"
   +"stones, the floor from a deeper grey slate. A spiral staircase\n"
  +"leads up and down.\n");

add_item(({"stairs", "staircase"}), 
  "The steps are dark slate, but strong. Up the staircase it\n"
 +"looks to get lighter, while it gets darker downwards.\n");

add_item("walls", "They are made from small round grey stones.\n");

add_exit(PATH + "tower2", "up", 0);
add_exit(PATH + "tower_cellar", "down", 0);
add_exit(PATH + "e_hall", "west", 0);

}


