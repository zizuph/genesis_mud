inherit "/std/room";
#include "/d/Kalad/defs.h"

create_room()
{
    object door;

    set_short("room a");
    set_long("This is room a. Try 'bash gate'.\n");
    
    door = clone_object(OPEN(examples/door/door_a));
    door->move(TO);
    door->set_key(765234);   /*for lock to work properly*/

}
