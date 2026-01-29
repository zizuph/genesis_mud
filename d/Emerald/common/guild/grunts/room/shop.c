/* This is the Grunts shop. They don't get a better deal here, though,   */
/* otherwise we would get a nasty tax bill. Many thanks to Nick & Tricky */
/* for coding such nice example shops for us to steal. *grin*            */
/* Recoded on 21/08/95 by Tulix III.                                     */

inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "default.h"
#include "../guild.h"

void
create_room()
{
    config_default_trade();
    set_short("Grunts shop");
    set_long(
	"   This is the Grunts shop. You can buy & sell loot here.\n" +
	"You can also use value or list commands, 'list armours',\n" +
	"'list weapons', 'list <name>' and 'list' works too.\n" +
	"There is also a small sign to read with more instructions.\n" +
      "The main Grunts guild room is back up the way you came.\n\n");

    add_exit(THIS_DIR + "store", "down", "@@wiz_check");
    add_exit(THIS_DIR + "main", "up", 0, 1);
    add_exit(THIS_DIR + "post", "east", 0, 1);
    add_exit(THIS_DIR + "train", "west", 0, 1);

    add_item("sign", "Even a Grunt could read this sign.\n");

    add_prop(ROOM_I_INSIDE, 1);

    set_store_room(THIS_DIR + "store");

    add_item(({"walls","wall"}),
	"The walls are cold, and damp to touch. It seems to be volcanic " +
	"rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
	"What little you can see above you suggests that the roof is made " +
	"of the same rock as the walls, volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock.\n");
}

void
init()
{
    ::init();
    init_shop(); /* Get the commands from the shop */
}
