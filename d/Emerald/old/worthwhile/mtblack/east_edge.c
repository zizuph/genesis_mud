inherit "/std/room";

#include "/d/Emerald/defs.h";

void create_room()
{
    set_short("Eastern Edge");
    set_long("You step up to the edge of the eastern "+
       "side of Mount Black and look around. Down is some "+
        "sort of shelf that seems covered with rubble and "+
        "a crude trail leading down to it. Back to the west is the "+
       "summit of the mountain.\n");

    add_exit(MBLACK_DIR + "east_shelf", "down", 0);
    add_exit(MBLACK_DIR + "top", "west", 0);

    add_item(({"Mount Black", "mountain", "summit"}), ("The "+
       "mountain is quite impressive as you survey it from "+
       "atop the east side.\n"));
    add_item(({"trail", "crude trail"}), ("The crude trail "+
       "leads down and seems to weave its way back and forth "+
     "across the side of the mountain.\n"));
     add_item(({"shelf", "rubble"}), ("The shelf, a fair ways "+
        "below you, is covered in some rocky rubble and looks "+
        "fairly dangerous to climb down to.\n"));
}
