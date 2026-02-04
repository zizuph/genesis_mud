inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/lake/"

create_room(){

set_short("Isle Forest");
set_long(
"Mysterious and beautiful, these ancient trees grow up from the\n"
+"depths of the rich earth of this isle. The ground is heavily covered\n"
+"with moss and small shrubs.\n"
+"The lake dock can be seen through the trees to the south.\n"
);

add_item("trees", "They are ancient pines, maples, holly, oak, birch,\n"
  + "elder, hawthorn and beech.\n");
add_item("moss", "It covers the isle like a rich emerald carpet.\n");
add_item("shrubs", "There are multitudes.\n");

add_exit(PATH + "isle1", "south", 0);
add_exit(PATH + "f2", "north", 0);
add_exit(PATH + "f3", "east", 0);
add_exit(PATH + "f4", "west", 0);

}
