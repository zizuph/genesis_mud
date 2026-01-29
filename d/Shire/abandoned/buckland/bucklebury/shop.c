inherit "/d/Shire/room";
inherit "/d/Genesis/lib/shop";
#include <stdproperties.h>
#include "/d/Shire/buckland/buckdefs.h"

#define STORE_ROOM	BB_DIR + "store"
#define EXIT1 BB_DIR + "buroad10","west",0,1


/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_room()
{
    config_default_trade();
    set_short("The shop in Bucklebury");
    set_long(
      	"You are in the local shop. Here you can sell and buy stuff.\n" +
      	"You can also use value or list commands, 'list armours',\n" +
      	"'list weapons', 'list <name>' and 'list' works too.\n" +
      	"There is also a small sign to read with more instructions.\n" +
	"West is an exit to the street.\n" +
      	"");

    add_exit(STORE_ROOM, "north", "@@wiz_check");
    add_exit(EXIT1);

    add_item("sign", "A nice looking sign for you to read.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(STORE_ROOM);
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
