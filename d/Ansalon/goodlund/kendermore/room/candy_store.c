/* Redin's Candy Store in Kendermore by Gwyneth May 17, 1999 */
/* Based on the General Shop in Calia by Maniac         */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit "/lib/shop";
inherit KENDERMORE_IN;
#define STORE_ROOM KROOM + "candy_store2"
#define TO this_object()
#define TP this_player()
#define NF(xxx) notify_fail(xxx)
#define P(str, ob) present(str, ob)

object redin;


void
reset_kendermore_room()
{
    if (!redin)
        if (!P(redin, TO))
        {
            redin = clone_object(KNPC + "redin");
            redin->move(this_object());
        }
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/

void
create_room()
{
    config_default_trade();
    set_short("Redin's candy store");
    set_long("The walls are coloured with red stripes like candy canes. " + 
        "There is a large glass case displaying various sorts of candy. " + 
/*
        "The shopkeeper stands behind the case sucking on a lollipop. " + 
*/
        "There is a sign firmly nailed down to the wall " + 
        "with instructions.\n");
    add_item("walls", "Looking at them makes you slightly dizzy.\n");
    add_item(({"case", "glass case"}), "Your mouth waters at the sight " + 
        "of such a variety of candy. It's firmly locked to prevent even " + 
        "an expert lock picker from breaking in.\n");
    add_cmd_item("sign", "read", "@@do_read");
    set_store_room(KROOM + "candy_store2");
    add_exit(KROOM + "street20", "northwest", 0);
    add_invis_exit(STORE_ROOM, "south", "@@wiz_check");
    
    add_prop(ROOM_I_INSIDE, 1);

    query_store_room()->load_me();
    reset_kendermore_room();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
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
    if (TP->query_wiz_level())
	return 0;
    write("There is no obvious exit south.\n");
    return 1;
}

int
do_read(string str)
{   
    if (str == "sign")
    {
        write("   Welcome to Redin's Candy Store!\n" + 
              "   I sell a variety of delicious\n" + 
              "   sweets! I can show each piece to\n" + 
              "   you. I don't buy anything here, sorry!\n" + 
              "   \n" + 
              "   Candy List:\n" + 
              "   Butterscotch       20cc\n" + 
              "   Caramel            20cc\n" + 
              "   Licorice           20cc\n" + 
              "   Lollipop           20cc\n" + 
              "   Maple              20cc\n" + 
              "   Rock Candy         20cc\n" + 
              "   Taffy              20cc\n" + 
              "   Toffy              20cc\n" + 
              "\n" +
              "   I only have a limited supply!\n");

	return 1;
    }
    else
    {
	NF("Read what? The sign?\n");
	return 0;
    }
}

int
do_sell(string str)
{
    NF("You may not sell items here.\n");
    return 0;
}

int
do_buy(string str)
{
    NF("The shopkeeper is not here to buy from.\n");
    if (!P(redin, TO))
	return 0;

    if (KMASTER->query_enemy(this_player()->query_real_name()))
    {
        write("The shopkeeper won't deal with the likes of you!\n");
        return 1;
    }

    return ::do_buy(str);
}

int
do_list(string str)
{
    NF("Please read the sign.\n");
    return 0;
}

