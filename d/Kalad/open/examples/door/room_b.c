inherit "/std/room";
#include "/d/Kalad/defs.h"

create_room()
{
    object door;

    set_short("room b");
    set_long("This is room b. Try 'bash gate'.\n");
    
    door = clone_object(OPEN(examples/door/door_b));
    door->move(TO);
    door->set_key(765234);   /*for lock to work properly*/

}
