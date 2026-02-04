inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/lake/"

create_room(){
set_short("Isle");
set_long(
"A cool breeze is cast from the sparkling lake and shivers its\n"
+"way through the grand trees of this beautiful isle. A sharp reddish\n"
+"coloured rock juts out of the ground here next to the lake. All about\n"
+ "the waterfront are rocks.\n");

add_item("rocks", "They are all about the waterfront. Some of them\n"
+"are sharp and craggy mountainous rocks.\n");
add_item("lake", "It is sparkling and beautiful.\n");
add_item("trees", "They are tall and grand. Maples, pine, oak, birch,\n"
  + "beech and hickory line the waterfrontand spread out over the isle.\n");
add_item("rock", "It is a large piece of rock set in the earth next\n"
+ "to the water. A strange inscription is upon it.\n");
add_cmd_item("rock", "read", "Glory to the Ancients.\n");
add_cmd_item("inscription", "read", "Glory to the Ancients.\n");

add_exit(PATH + "isle1", "west", 0);


}
