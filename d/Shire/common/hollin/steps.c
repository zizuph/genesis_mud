#include "outroom.h"

create_outroom() {
    set_short("Steps");
    set_long("You are on a path climbing steeply upwards to the east. There "+
	     "are some steps carved from rock here to make it easier to "+
	     "walk. They are almost completely worn out after being used "+
	     "for a long time. A bit further south a small brook is trickling. "+
	     "It winds between some stone blocks, and down in a large "+
	     "dried out river. The brook runs in parallel with the path. To the west "+
	     "the path slopes more gently.");
    add_item(({"steps","rock","path"}),
	     "The path is really some steps carved from the rock here.\n");
    add_item("brook",
	     "It runs from the east down to the west. Wonder where it "+
	     "starts?\n");
    add_item(({"stone blocks","blocks"}),
	     "They are big and grey. Between them, a small brook is "+
	     "trickling.\n");
    add_item("river",
	     "The river looks emptied though. The water must disappear "+
	     "somewhere.\n");
    add_item("water",
	     "It trickles down, but disappers somehow somewhere.\n");
    EAST("rom1");
    WEST("dwarfroad.15");
}

init()
{
    ::init();
    call_other(STAND_DIR+"trolls_lair", "create_soldier");
}
