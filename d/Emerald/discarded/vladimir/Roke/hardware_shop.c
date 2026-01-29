/*   This is a hardware shop in Calia

    coder(s):  Maniac 

    history:   2/2/94                     Created             Maniac 

    purpose:    shop
    exits:      w to general shop, nw to store

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/room";
inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define HARDWARE_STORE_ROOM (PALACE_DIR + "hardware_store")

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_short("The palace hardware shop");
    set_long(
        "This room is the hardware shop " +     
        "of the Calian Warriors Guild, but everyone is welcome to " +
        "use it.  You can buy any items here, but if " +
        "you want to do some selling, you may only sell back items " +
        "previously purchased at this store.  General items can be " +
        "sold next door.  You can use value or list commands here.  " +
        "There is also a small sign to read with more instructions.  " +
        "\n");

    add_exit(PALACE_DIR + "shop", "west", 0);
    add_exit(HARDWARE_STORE_ROOM, "northwest", "@@wiz_check");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(HARDWARE_STORE_ROOM);
}


int shop_hook_allow_sell(object ob)
{
  if (ob->id("_calia_hardware_shop_")) return 1;
  return 0;
}




/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
      	return 0;
    write("Some magic force keeps you from going northwest.\n");
    say(QCTNAME(this_player()) + " tries to go northwest but fails.\n");
    return 1;
}

int
do_read(string str)
{
object tp;
  tp = TP;

  if (str == "sign")  {
    tp->catch_msg("Commands work as for the shop next door, except " +
                  "you will not be able to sell items that were not " +
                  "purchased at this store.  The reason for this is " +
                  "that the general store next door should be used " +
                  "for this purpose.  Enjoy the shop!\n");
  return 1;
  }
  else {
    NF("Read what?  The sign?\n");
    return 0;
  }
}
/*
int 
do_sell(string str)
 
{
   object tp;

   tp = TP;

   tp->catch_msg("We don't buy anything here, try next door!\n");
   return 1;

}
*/




