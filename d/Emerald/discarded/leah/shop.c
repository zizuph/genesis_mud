/*
 * This is the village's shop. They don't get a better deal here, though,
 * otherwise we would get a nasty tax bill. Many thanks to Nick & Tricky
 * for coding such nice shops for us to steal. #:-)
 */

inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "/d/Emerald/defs.h"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_room()
{
    config_default_trade();
    set_short("Village shop");
    set_long("   You are in a small, dusty shop. East of here "+
      "you can make out what seems to be a store room, and to the "+
      "north, through a small window you can see a tower of some kind.  The shopkeeper will "+
      "allow you to buy and sell items from him as long as he makes "+
      "a profit.  You can also use value or list commands, 'list "+
      "armours', 'list weapons', 'list <name>' and 'list' works "+
      "too.  There is also a small sign to read with more "+
      "instructions.\n\n");

    add_exit(VILLAGE_DIR+"road3", "west",);
    add_exit(VILLAGE_DIR+"store", "east", "@@wiz_check");

    add_item("sign", "A nice sign for you to read.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(VILLAGE_DIR+"store");

    (VILLAGE_DIR + "store.c")->this_room();

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
