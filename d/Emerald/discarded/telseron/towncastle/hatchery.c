inherit "/std/room";
 
#include "default.h"

object baby;

void
reset_room()
{
    int i;
    
    if (baby)
	return;
    for (i=0 ; i<4 ; i++) {
	baby = clone_object(TCASTLE_DIR + "npc/babyalligator");
	baby->move_living("into a room", this_object());
    }
}
 
void
create_room()
{
    object gate, door;
 
    set_short("Hatchery");
    set_long( "This looks like a hatchery. However, it doesn't look "+
    "like it is birds that get hatched in here, but larger creatures "+
    "you probably wouldn't want to meet.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    gate = clone_object(TCASTLE_DIR + "doors/gate_a");
    gate->move(this_object());
 
    door = clone_object(TCASTLE_DIR + "doors/hdoor_a");
    door->move(this_object());
 
    set_alarm(1.0, 0.0, reset_room);
}
