inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on the bridge");
    set_long(BSN("You are on the stone bridge that spans the river "+
       "running through the middle of Pelargir. The bridge is paved "+
       "with cobblestones and is very sturdy. You would guess this "+
       "bridge has been here for a few hundred years. Below the bridge "+
       "the river runs swift."));
    COBBLE;
    add_item("river",BSN("The river is narrow at this point, and thus "+
       "runs nearly twice as fast here. (definitely not a good place "+
       "to swim!)"));
    add_item("bridge",BSN("This ancient bridge has a nostalgic feeling "+
       "about it. Though it seems worn with the passage of "+
       "many feet. It still feels as solid as the "+
       "stone it is built from."));
    add_exit(PELAR_DIR + "street/ngbcross.c","northeast",0);
    add_exit(PELAR_DIR + "street/groad4","southwest",0);
}
