inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/lake/"

init(){
add_action("swim", "swim");
::init();
}

swim(){
write("It is far too cold.\n");
return 1;
}

create_room(){
object ship;

set_short("Dock");
set_long(
"Stretching out into the crystal clear waters of the lake, this long\n"
+"dock stands sturdy, made of some beautiful silver-white wood. Water\n"
+"from the lake laps slowly up against the dock, blown by the wind.\n"
+"The lake is deep and its waters reach out across the valley, seemingly\n"
+"forming its center. Tall trees grow up to the edge of the lake here.\n"
);

add_item("dock", "It is well made, of silver-white wood.\n");
add_item("lake", "A crystal clear mountain lake.\n");
add_item("trees", "They grow along the shore of the lake.\n");
add_item("water", "It is clear and pue.\n");

add_cmd_item("water", "touch", "It is very cold.\n");

add_exit("/d/Terel/mecien/valley/lv", "south", 0);

ship=clone_object(PATH + "m_ship");
ship->move(this_object());

call_out("start_now", 5, ship);
}

start_now(object ship){

if(ship && present(ship, this_object())){
   ship->start_ship();
   }
}


