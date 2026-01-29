

#define PATH "/d/Terel/mountains/obj"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

reset_room(arg){

object cook;
if(present("cook")) return;
cook=clone_object("/d/Terel/mountains/obj/cook");
cook->move(this_object());

}

create_room(){
object stove;

set_short("Kitchen");
set_long(
"Smoke and fumes fill the air of this gastly room. It seems to be a\n"
+"kitchen, though whatever is cooked here would hardly seem edible.\n"
+"A large stove and many shelves fill the room.\n");
add_prop(ROOM_I_INSIDE, 1);
add_exit("d/Terel/mountains/house2", "east", 0);

stove = clone_object(PATH + "/stove"); 
stove->move(this_object());

    
add_item(({"shelf","shelves"}),
"The shelves are filled with grotesque ingredients.\n");
reset_room();
}
