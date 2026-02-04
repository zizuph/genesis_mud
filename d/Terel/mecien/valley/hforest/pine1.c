inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/hforest/"

create_room(){
set_short("Dark Pine Forest");
set_long(
"All about great dark pines rise up, like shadowy enemies prepared to\n"
+"do battle with any who oppose them. They sway in the winds, frosted\n"
+"with a glaze of snow and ice.\n"
);

add_item("trees", "They are dark pines, frosted with snow and ice.\n");
add_item("pines", "They are great dark trees, conifers of many ages.\n");

add_exit(PATH + "edge", "northwest", 0);
add_exit(PATH + "forest4", "southeast", 0);

add_exit(PATH + "river1", "southwest", 0);
}

