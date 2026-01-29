inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{

    set_short("Gate to the Elven Village");
    set_long("   You find yourself before "+
      "a small iron-wrought gate. Beyond the gate a "+
      "quaint little village spreads out to the north, "+
      "while the sprawling Emerald forest is behind you. There is a sign here, "+
      "set neatly into the ground.\n\n");

    add_item("sign", "There is writing on it.\n");
    add_item("village","The village is just to the north, why not go "+
      "take a look around?\n");
    add_item("forest","The forest is large and thick, the trees are a mixture "+
      "of elms, oaks and other\nlarge deciduous trees.\n");

    add_exit(LROAD_DIR + "leroad10", "south", "@@go_bridge@@");
    add_exit(VILLAGE_DIR + "road2", "north", 0);

}
init()
{
    ::init();
    add_action("read", "read");
    LOAD_CLONE_HANDLER("/d/Emerald/leah/clone_handler");
}

int
read(string arg)
{
    notify_fail("Read what?\n");
    if (arg != "sign")
	return 0;
    write("The sign reads 'Welcome to Leah'.\n");
    return 1;
}

int
go_bridge()
{
    write("You step up onto and walk over the bridge toward the "+
          "small, forest-edged road ...\n\n");
     return 0;
}
