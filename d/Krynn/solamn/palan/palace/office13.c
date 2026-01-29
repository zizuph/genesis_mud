/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Treasury");
    set_long(BS("This is the treasury. Actually this room contains "
          +  "a simple desk and a chair. You can't see anyone here, "
          +  "the only thing conspicious is the door here.", SL));

    add_exit(PALACE + "hall8","east",0,0);
    clone_object(OBJ + "door13")->move(TO);

    add_item(({"chair","desk"}),BS("You get the feeling that neither chair "
           +  "nor desk are used very much. It seems the door is still in "
           +  "use though, probably things are handled by the tax collector "
          +  "and his computing department now?",SL));
}

 
