#include "../../ctower.h" 

inherit MAZESTD;
 
void
ctower_reset()
{
    object talis;
   
    if (present("phase_quest_talis"))
    {
        return;
    }
  
    if (talis = clone_object(CTOWER_OBJ + "talis"))
    {
        talis->move(this_object(), 1);
    }
}
 
void
create_maze()
{
    set_long("All surfaces of this room are mirrored, "+
	"making reflections stretching away to infinity in all "+
	"directions. There is a soft glow eminating from the very "+
	"walls themselves, giving you plenty of light.\n");
   
    remove_exit("west");
    add_exit(CTOWER_ROOM_MAZE + "maze13", "west", "@@mirror_open@@");

    ctower_reset();
}

int mirror_open()
{
    object room;
  
    if (!(room = find_object(CTOWER_ROOM_MAZE + "maze13")) || 
	!room->query_exit_open() || !room->wand_in_hole())
    {
        return bump();
    }
  
    return sure();
}
