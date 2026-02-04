inherit "/std/room";

create_room(){
set_short("Forest Edge");
set_long(
"Massive pines rise here, all about. Some leaning out over the swift icy\n"
+ "river that flows from north to south. A huge covered bridge spans the river\n"
+"to the east, its old form somewhat decaying and half covered with\n"
+"ice. The forest seems to be colder on this side of the river.\n"
);

add_item("bridge", "It is a huge covered wooden bridge that spans the icy river. It seems\n"
+"to be in stable condition, but a bit decayed and worn.\n");
add_item("pines", "They are massive pines, old and grand.\n");
add_item("river", "It is a swift running icy river.\n");

add_exit("/d/Terel/mecien/valley/fall/bridge", "west", 0);
add_exit("/d/Terel/mecien/valley/hforest/pine1", "southeast", 0);
add_exit("/d/Terel/mecien/valley/hforest/df1", "north", 0);
}
