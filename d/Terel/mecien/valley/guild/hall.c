/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Great Hall");
set_long("High above is the arched stone ceiling of this great and\n"
  + "ancient hall. It is dark and somewhat peaceful in the lonliness\n"
  + "of this barren stone hall. The antiquity reaches out and almost\n"
  + "speaks words from the depths of the stones.\n"
);

add_exit(PATH + "n_hall1", "north", 0);
add_exit(PATH + "s_hall1", "south", 0);
add_exit(PATH + "temple", "east", 0);
add_exit(PATH + "guild", "west", 0);


}


