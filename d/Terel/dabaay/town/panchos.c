/*
 *  Pancho's by Dabaay,
 *  Based on Shinto's Calathin Inn (5/13/99)
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"

inherit STDROOM;
inherit "/d/Terel/std/pub";

/*
 * Function name: query_object_list
 * Description:   return list of object to clone at each reset.
 */
public string*
query_object_list()
{
    return ({DABAAY_DIR +"npc/pancho"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Pancho's by Dabaay");
    set_long("You have entered into Pancho's by Dabaay.  There are"
        + " several simple-looking tables scattered throughout the"
        + " place.  Ahead of you, and towards the back, is a well-"
        + "used counter with a few stools set next to it.  The"
        + " smells of various cooked meats and fish tease your"
        + " nose and set your mouth to watering.\n"
        + "There is a menu on the wall which you can read. \n");

    add_item(({"table", "tables"}),
        "They are made of rough-sawn timbers, and are generally used"
        + " for eating at.\n");

    add_item(({"counter"}),
        "A long, plank-board counter, that has seen its share of"
        + " use and abuse.\n");

    add_item(({"stools","stool"}),
        "There are a few wooden stools standing next to the counter. "+
        "They are fairly simple in construction but look comfortable.\n");

    add_item(({"menu"}), "@@menu");
    add_cmd_item("menu", "read", "@@menu");

    INSIDE;

    add_food (({"chowder", "chowders"}), /* ids */
        ({"chowder", "chowders"}), /* names */
        "fish",                    /* adj */
        200,                       /* ammount */
        175,                       /* price */
        0,                         /* short */
        0,                         /* pshort */
        "A strong smelling, thick bowl of chowder.  Made from"
        + " several varieties of salt-water fish.\n", 0);

    add_food (({"stew", "stews"}), /* ids */
        ({"stew", "stews"}), /* names */
        "meaty",             /* adj */
        170,                 /* ammount */
        150,                 /* price */
        0,                   /* short */
        0,                   /* pshort */
        "A steaming bowl of stew, with large chunks of unknown meats"
        + " in it.\n", 0);

    add_food (({"wrap", "wraps"}), /* ids */
        ({"wrap", "wraps"}), /* names */
        "seafood",             /* adj */
        130,                 /* ammount */
        100,                 /* price */
        0,                   /* short */
        0,                   /* pshort */
        "Chunks of shrimp, fish, and squid wrapped up in an unleavened "+
        "disk of flour bread.\n", 0);

    add_food (({"sandwich", "sandwiches"}), /* ids */
        ({"sandwich", "sandwiches"}), /* names */
        "fish",             /* adj */
        110,                 /* ammount */
        90,                 /* price */
        0,                   /* short */
        0,                   /* pshort */
        "A folded disk of unleavened corn bread, filled with shredded "+
        "fish.\n", 0);

    add_exit(DAB_TOWN + "square3_6", "west", 0);

    reset_room ();

}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 *                Also call init_pub() to set up the pub.
 */
public void
init()
{
    ::init();
    init_pub();
}

/*
 * Function name: menu
 * Description:   Handle the read action for the menu
 * Returns:       the menu
 */
public string
menu()
{
    return ("The menu reads:\n\n" +
        "Fish Chowder .................175 Copper Coins\n" +
        "Meaty Stew .................. 150 Copper Coins\n" +
        "Seafood wrap .................100 Copper Coins\n" +
        "Fish Sandwich ................ 90 Copper Coins\n"); 
}


/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
void
pub_hook_player_buys(object ob, int price)
{
    ::pub_hook_player_buys(ob, price);

    ob->add_prop(OBJ_M_NO_SELL, 1);
}
