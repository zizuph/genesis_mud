inherit "/std/room";
 
#include "default.h"
#include <filter_funs.h>
#include <macros.h>

object leader;

void reset_room();

public void
create_moat()
{
}
 
public void
reset_moat()
{
    object obj, *inv;
    int    i;
 
    inv = all_inventory();
    if (leader)
        return;
    if (random(5) < 3) {
	switch (random(3)) {
	    case 0:
		leader = clone_object(TCASTLE_DIR + "npc/alligator");
		break;
	    case 1:
		leader = clone_object(TCASTLE_DIR + "npc/tortoise");
		break;
	    case 2:
		leader=clone_object(TCASTLE_DIR + "npc/piranhaboss");
		leader->move_living("into a room", this_object());
		obj=clone_object(TCASTLE_DIR + "npc/piranha");
		obj->move_living("into a room", this_object());
		leader->team_join(obj);
		obj=clone_object(TCASTLE_DIR + "npc/piranha");
		obj->move_living("into a room", this_object());
		leader->team_join(obj);
		obj=clone_object(TCASTLE_DIR + "npc/piranha");
		leader->team_join(obj);
		break;
	}
	obj->move_living("into a room", this_object());
    }
}
 
nomask void
create_room()
{
    set_short("In moat");
    set_long( "You are wading in a deep moat. The water reaches "+
	     "to your waist, and is rather foul smelling.\n" );
 
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
 
    create_moat();
 
    set_alarm( 1.0, 0.0, reset_room);
}
 
nomask void
reset_room()
{
    if (MASTER == TCASTLE_DIR + "moat")
	return;
    reset_moat();
}
