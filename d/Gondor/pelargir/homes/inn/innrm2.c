inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a room at the inn");
    set_long(BSN("You are in an room of the Dragon's claw Inn. "+
       "This room looks like a fine place to stay. The bed is made, "+
       "the chest is pushed neatly into the corner, and there is "+
       "generally no clutter. Perhaps if they fixed the lock on the "+
       "door you might feel safe staying here. Though someone would "+
       "have to dust first."));
    add_prop(ROOM_I_INSIDE,1);
    add_item("dust",BSN("AAACHOOOO!  definitely don't want to do that again."));
    add_item(({"floor","bed"}),BSN("There is so much dust in "+
       "here that little clouds arise when you touch it."));
    add_exit(PELAR_DIR + "homes/inn/innhall3","south",0);
    
    clone_object(PELAR_DIR + "obj/innchest")->move(TO);
}
