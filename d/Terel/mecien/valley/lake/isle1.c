inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/lake/"
create_room(){
set_short("Isle");
set_long(
"A cool breeze is cast from the sparkling lake and shivers its\n"
+"way through the grand trees of this beautiful isle. A tall and\n"
+"elegant wooden dock stretches out into the waters. The waterfront\n"
+"is coated with assortments of rocks, some craggy and sharp.\n"
);

add_item("rocks", "They are all about the waterfront. Some of them\n"
+"are sharp and craggy mountainous rocks.\n");
add_item("lake", "It is sparkling and beautiful.\n");
add_item("dock", "Made of a silver white wood, it is tall and elegant.\n");
add_item("trees", "They are tall and grand. Maples, pine, oak, birch,\n"
  + "beech and hickory line the waterfront and spread out over the isle.\n");


add_exit(PATH + "isle2", "east", 0);
add_exit(PATH + "f1", "north", 0);

}
