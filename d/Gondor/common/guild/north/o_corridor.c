#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/north/northern_hq.h"

create_room()
{
    set_short("A corridor in the northern headquarters");
    set_long(BS("You're in a corridor. The walls are made of stone "+
    "blocks, smooth to the touch, so skillfully set that the seams are "+
    "hard to detect. Burning torches are set in torch brackets at regular "+
    "intervals. To the south a stairway leads up, to the north the "+
    "corridor ends in an arched opening.\n"));

    add_item("opening","The opening leads into the great hall.\n");
    TORCHES;
    SCONCES;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"great_hall","north",0);
    add_exit(RANGER_NORTH_DIR+"stairs","up",0);
}