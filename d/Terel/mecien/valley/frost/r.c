inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/frost/local.h"

create_room(){

set_short("Ice Fortress");

add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");

INSIDE;


}



