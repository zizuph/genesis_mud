/* 
 * This is the Grunts shop. They don't get a better deal here, though,
 * otherwise we would get a nasty tax bill. Many thanks to Nick & Tricky
 * for coding such nice shops for us to steal. #:-)
 */

inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "default.h"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_room()
{
    config_default_trade();
    set_short("Grunts shop");
    set_long(
            "This is the Grunts shop. You can buy & sell loot here.\n" +
      	"You can also use value or list commands, 'list armours',\n" +
      	"'list weapons', 'list <name>' and 'list' works too.\n" +
      	"There is also a small sign to read with more instructions.\n" +
            "The main Grunts guild room is back up the way you came.\n" +
      	"");

    add_exit(THIS_DIR+"store", "down", "@@wiz_check");
    add_exit(THIS_DIR+"main", "up", 0, 1);

    add_item("sign", "Even a Grunt could read this sign.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(THIS_DIR+"store");

    add_item(({"walls","wall"}), break_string(
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n"
        ,78));
    add_item(({"roof","ceiling"}), break_string(
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n"
        ,78));
    add_item(({"floor","ground"}), break_string(
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n"
        ,78));
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}
