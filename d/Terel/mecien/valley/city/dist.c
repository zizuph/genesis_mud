inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/city/"
#define EN environment

create_room(){
set_short("Distillery");
set_long(
"This large building looks to be a distillery. Huge casks and barrels rest " +
"in racks and upon shelving units. Intricate glass and metal equipment is " +
"set up for grain distillation.\n"
);
add_item("casks", "They are large wooden casks, made of oak.\n");
add_item("barrels", "They are small wooden barrels, made of oak.\n");
add_item("shelves", "they are wooden shelves made to hold small barrels.\n");
add_item("glass", "It is part of the equipment for distillation.\n");
add_item("metal", "Parts of a the distillery apparatus.\n");
add_item("racks", "They hold the casks in place, made of iron.\n");
add_item("equipment", "It is distillery equipment, made of glass and metal. A very intricate apparatus. A liquid drips from a spot where it may be sampled.\n");

add_cmd_item("liquid", "sample", "Yum! Yum! A wonderful cherry liquor!\n");

add_item("liquid", "It is red in colour.\n");

add_exit(PATH + "street6", "northeast", 0);
}

