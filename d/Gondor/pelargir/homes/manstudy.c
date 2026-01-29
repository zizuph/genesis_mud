inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  lord;

void
reset_room()
{
    if (objectp(lord))
        return;

    lord = clone_object(PELAR_DIR + "npc/manlord");
    lord->arm_me();
    lord->move_living("down", TO);
}

void
create_room()
{
    set_short("in the study of the mansion");

    set_long(BSN("This is the study and library of the mansion. There "
      + "are not many books here, however. A desk, a mostly empty "
      + "bookshelf, and the table are the only furnishings here, and "
      + "all are covered in dust."));

    add_prop(ROOM_I_INSIDE,1);
    add_item("dust",BSN("The dust is pretty thick, "+
       "coating just about everything in the room."));
    add_item(({"desk","table"}),BSN("Covered in dust... definitely "+
       "not much in use."));
    add_item(({"bookshelf","books"}),BSN(
       "The bookshelf is bare at the moment, though there is a "+
       "spot here that is not covered by dust. Someone must have taken "+
       "the books. Perhaps they will return them soon."));

    add_exit(PELAR_DIR + "homes/mangrhall","south",0);
    
    reset_room();
}

