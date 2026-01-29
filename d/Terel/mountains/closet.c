

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object fur;
if(present("fur")) return;
fur=clone_object("/d/Terel/mountains/obj/fur");
fur->move(this_object());

}

create_room(){
set_short("Closet");
set_long(
"This is a large storage room of the house. Its walls are lined with\n"
+"racks and shelves. Large pegs are on the walls on which cloaks and\n"
+"robes are to hang.\n");
add_prop(ROOM_I_INSIDE, 1);
add_exit("/d/Terel/mountains/house1","west", 0);
reset_room();
}

