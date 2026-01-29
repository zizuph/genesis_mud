
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "sulphur.h"
 
void
create_room()
{
    set_short("Sulphur chamber");
    set_long("You have entered a beautifully decorated chamber "+
        "carved out of this cavern.  The walls are very smooth "+
        "and painted with an off-white paint.  Along the north wall "+
        "you see a gigantic yellow stone block.  There is a door leading back "+
        "to the south.\n");
    add_item(({"gigantic yellow block","yellow block","block","gigantic block"}),
        "After closer inspection you see that it is a gigantic block of "+
        "sulphur, too heavy for anyone to have placed here.  Lord Pyros "+
        "himself must have put it here for some reason.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
 
    add_exit(CAVE+"startroom","south",0,1);

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
