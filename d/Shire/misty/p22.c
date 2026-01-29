/* highpass */

#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("by the river");
    set_long("This is the end of the grassy path. It can't go any further "+
      "east because it is blocked by swift currents of River Anduin. "+
      "It seems that all your hopes to escape this way were wrong. "+
      "You must turn back and seek some other way.\n");

    add_item("path", "It comes from the west direction but here it stops. "+
      "Maybe it is used only by goblins when they want to "+
      "have fish for lunch.\n");
    add_item(({"river","water"}), "The water is icy cold and runs swiftly to "+
      "the south.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p21", "west",    0,    4);

}

init()
{
    ::init();
    add_action("enter_river", "enter");
}

int
enter_river(string river) {
    if(river != "river")
    {
	NF("Enter what?\n");
	return 0;
    }
    TP->catch_msg("You notice the that water is far to fast moving "+
      "and cold for you to go for a swim.\n");
    return 1;
}
