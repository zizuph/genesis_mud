/* Road to Haven by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit ROADBASE;

void
create_road()
{
    add_my_desc("The road here turns back to the south, heading southwest "+
      "around the protruding mountain range. To the east the road "+
      "continues and leads back into the passes through the mountains, "+
      "and it also continues to the southwest towards Haven. To your "+
      "southeast lies Darken Wood, and there is a break in the mountains "+
      "here forming a valley of dark green woods, which could head into "+
      "the haunted forests of Darken Wood.\n");

    add_exit(RDIR + "road4", "southwest");
    add_exit(RDIR + "road2", "east");

    OUTSIDE;
}

init()
{
    add_action("enter_forest", "enter");
    ::init();
}

int
enter_forest(string str)
{
    NF("What ?\n");
    if (!str)
	return 0;

    if (str != "valley" && str != "forest" && str != "woods")
	return 0;

    write("You step off the road here, into the dark forests to the "+
      "southeast, and feel a sense of dread as if the woods themselves "+
"were watching you. You quickly return to the road.\n");
    say(QCTNAME(TP)+" steps off the road here, into the forest to the "+
      "southeast, but quickly returns to the road, looking quite afraid.\n", TP);
    return 1;
}
