#pragma save_binary

inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include "../guild.h"

void
create_room()
{
    set_short("Mess hall");
    set_long("This is the Army's mess hall. Judging by the scraps of " +
	"food lying about the crumb-covered tables and chairs, you " +
	"feel it has been appropriately named.\n" +
	"Running the length of the north wall is a rough oak counter " +
	"behind which you see an array of different pots and saucepans" +
	".\n" +
	"Scratched up on a large black board is today's selection.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    add_item(({ "table", "tables", "crumb-covered tables" }), 
	"The tables are all in various states of degredation. Around " +
	"each, scattered on the floor are the remains of the previous " +
	"soldiers' meal.\n");
    add_item(({ "chair", "chairs" }),
	"The chairs lie about the hall, most of them near tables, " +
	"although some have strayed a little - perhaps the result of a " +
	"brawl that you missed.\n");
    add_item(({ "counter", "rough counter", "oak counter", 
	"rough oak counter" }),
	"This is the service counter. You can order your meal here.\n");
    add_item(({ "pots", "saucepans" }),
	"To be written.\n");
    add_item(({ "scraps", "food", "crumbs", "scraps of food" }),
	"To be written.\n");
    add_item(({ "menu", "board", "sign" }),
	"It has the day's dishes listed up on it with the corresponding " +
	"prices.\n");
    add_cmd_item(({ "sign", "board", "menu" }), "read",
	"@@my_menu");

    /* Please note that all prices were calculated using the formula in
       the manual page: man values
       and then had a 25% reduction due to guild previledges - Erane
     */
    add_food( "rhubarb crumble", ({ "crumble", "rhubarb" }), "rhubarb", 
	500, 315, "plate of rhubarb crumble", "plates of rhubarb crumble",
	"This is a very sticky and sickly-looking plate of rich " +
	"rhubard crumble.\n" +
	"It looks like it will keep you going for a while...\n", 0);

    add_food(({ "stew", "beef stew" }), ({ "stew", "beef", "slop" }), 
	({ "beef", "brown" }),
	95, 15, "bowl of brown slop", "bowls of brown slop", "This " +
	"is a steaming hot bowl of brown mushy stuff. It smells vaguely " +
	"of beef and doesn't look terribly apetising.\n",0);

    add_food(({ "soup", "pheasant soup" }), ({ "soup","pheasant" }),
	"pheasant", 180, 45,
	"bowl of pheasant soup", "bowls of pheasant soup",
        "This is a bowl of fairly decent-looking pheasant soup.\n", 0);

    add_exit(AA_DIR+"rooms/c3", "west");
}

public void
init()
{
    ::init();
    ::init_pub();
}

public string
my_menu()
{
    return "We are currently serving the following dishes:\n\n" +
	"   Beef stew.........................15 copper\n" +
	"   Pheasant soup.....................45 copper\n" +
	"   Rhubarb crumble...................25 silver\n";
}

