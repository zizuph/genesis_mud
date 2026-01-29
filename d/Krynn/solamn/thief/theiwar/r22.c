/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;
inherit "/lib/shop";

#define STORE    THEIWAR + "store"

void
create_ld_room()
{
    set_short("In the accessory store");
    set_long("This is an accessory store. A huge sign hangs overhead, " +
      "and a counter divides the room. Behind the counter stands a " +
      "@@dwarf_adj@@ long-bearded dwarf. Shelves line the cavern's " +
      "east wall and cans, tools and flasks are piled there.\n");
    add_item(({"cans","can","tool","tools","flask","flasks"}),
	     "The items in the store room are too far away to be looked " +
	     "at in detail.\n");
    add_item("counter", "It's a stone counter, fitting perfectly into this " +
	     "room.\n");
    add_item(({"sign","huge sign"}),
	     "There are letters on it.\n");
    add_item(({"dwarf"}),
	     "This is the storekeeper, who can sell you accessories.\n");

    add_exit(THEIWAR + "r21", "south");
    add_exit(THEIWAR + "store", "east","@@wiz_check");
    
    config_default_trade();
    set_store_room(STORE);
}

string
dwarf_adj()
{
    if (query_prop(ROOM_I_LIGHT))
      return "friendly";
    else
      return "grumpy";
}

void
init()
{
    ::init();
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_list", "list");
    add_action("do_read", "read");
}

int
do_sell(string str)
{
    write("You cannot sell anything here. Maybe you want to buy something " +
	  "instead?\n");
    return 1;
}

int
do_read(string str)
{
    if (!str)
      return 0;
    if (str == "sign" || str == "huge sign")
      {
	  write("On the huge sign you read:\n" +
		"       ACCESSORY STORE\n" +
		"       ===============\n" +
		"You can 'list'  the items that are\n" +
		"currently in the store room to see\n" +
		"what is there. You can also  'buy'\n" +
		"them of course.\n");
	  return 1;
      }
    
    return 0;
    
}
