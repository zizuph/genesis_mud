inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
 
void
ctower_reset()
{ 
    if (!present("ctower_globe"))
    {
        clone_object(CTOWER_OBJ + "clear_globe")->move(this_object(), 1);
        tell_room(this_object(), "A crystal globe floats into the room.\n");
    }
}

void
create_ctower_room()
{
    set_short("Secret room");
   
    set_long("This room is roughly circular although it is "+
       "hard to judge due to the apparent fractal images "+
       "produced by the crystalline walls.  You shield your "+
       "eyes which seems to help somewhat.\n" );
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
       "milky crystal that is cold to the touch.\n");
   
    add_exit(CTOWER_ROOM + "room6", "west");
   
    add_prop(OBJ_S_WIZINFO,  "You need to touch the globe "+
	     "with something heavy to dispell it. Anything too light "+
	     "will be destroyed.\n" );
  
    ctower_reset();
}

void leave_inv(object ob, object to)
{
    object room;
  
    ::leave_inv(ob, to);
  
    if (!sizeof(filter(all_inventory(), interactive)) &&
	(room = find_object(CTOWER_ROOM + "room6")))
    {
        set_alarm(1.0, 0.0, &room->close_fireplace());
    }
}
