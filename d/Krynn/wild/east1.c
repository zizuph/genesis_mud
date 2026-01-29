/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Outskirts of Solace, along the east road");
    set_long(
        "You are on the outskirts of the village of Solace, standing " +
        "on the east road. The trees are smaller and farther apart here " +
        "than they are to the west. West the road enters the village, " +
        "which is nestled amongst the great Vallenwood trees, and to " +
        "the east the road leaves the forest, winding through farmlands " +
        "towards a distant mountain range.\n");

    add_exit(C_SOL, "west");
    add_exit(TDIR + "east2", "east");
}

int
block()
{
    write("The tree village Solace is under attack by dragons and " +
	  "draconians. The wizards of Krynn, has yet again, gone into " +
	  "battle to defend their creation. The battle will go on for " +
	  "several hours, since the wizards are few and the dragons are " +
	  "many. The only thing you can do is to pray to the gods and " +
	  "give them all the support you can.\n");
    return 1;
}







