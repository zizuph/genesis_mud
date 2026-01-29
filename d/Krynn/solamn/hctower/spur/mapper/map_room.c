// Room that knows how to talk to mapper object
// borrowed (with permissions) from Boriska of Avenir.
// grace march 1995

#include "../local.h"

inherit SPURRM;

#define MAPPER "/d/Krynn/solamn/hctower/spur/mapper/mapper"

mapping exits;

void
create_spur_room()
{

  /*::create_room(); not needed!!!*/
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
