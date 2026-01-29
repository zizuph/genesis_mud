inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a room at the inn");
    set_long(BSN("You are in an upstairs room of the Dragon's claw. "+
       "The room seems fairly average as far as inn rooms go, a simple bed, "+
       "a nice chest for personal belongings in the corner, and "+
       "generally free of dust. Evidently no one is using this "+
       "room, since the door was left unlocked."));
    add_prop(ROOM_I_INSIDE,1);
    add_item("bed",BSN("The bed is made, and the pillows are fluffed, "+
       "it would be a pity to mess it up."));
    add_exit(PELAR_DIR + "homes/inn/innhall2","south",0);
    
    clone_object(PELAR_DIR + "obj/innchest")->move(TO);
}
