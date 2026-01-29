// Room that knows how to talk to mapper object

#pragma save_binary

inherit "/std/room";

#define MAPPER "/d/Avenir/common/map/mapper"

mapping exits;

void
create_room()
{

  ::create_room();
  exits = MAPPER->query_room_exits (this_object());
  if (!exits || m_sizeof (exits) == 0 )
    return;
  
  map (m_indexes (exits), "add_exits", this_object());
}
    
void
add_exits ( string room )
{
  add_exit (room, exits[room], 0);
}