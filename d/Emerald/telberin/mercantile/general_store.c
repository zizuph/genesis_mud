/*
 *  /d/Emerald/telberin/mercantile/general_store.c
 *
 *  This is the general store in Telberin.
 *
 *  Modified from /d/Gondor/minas/rooms/mtshop.c
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit TELBERIN_BUILDING;
inherit "/d/Emerald/lib/shop";
inherit "/d/Genesis/delivery/office";

#include <stdproperties.h>
#include <language.h>
#include "/d/Emerald/telberin/defs.h"

#define STORE_ROOM "/d/Emerald/telberin/mercantile/gs_store"

/* prototypes */
public string       exa_poster();


/*
 * Function name:        create_shop
 * Description  :        set up the shop
 */
public void
create_telberin_building()
{
    set_short("The General Store of Telberin");
    set_em_long("This is the General Store of Telberin. The ambiance"
      + " here is that of simplicity and practicality. Wares which are"
      + " useful to the average adventurer are displayed prominently"
      + " on various shelves and cases around the room, and a poster"
      + " has been nailed to the wall.\n");

    add_item( ({ "counter", "long counter" }),
        "A long counter is situated at the front of the store. It is"
      + " behind this that the owner spends most of his time.\n");
    add_item( ({ "shop", "store", "general store", 
                 "general store of telberin", "room", "area" }), long);
    add_item( ({ "wall", "walls" }),
        "The walls of the shop are crowded with shelves, many of"
      + " which display interesting items useful to adventurers.\n");
    add_item( ({ "floor", "ground", "down", "carpet", "green carpet",
                 "worn carpet", "well-worn carpet",
                 "well-worn green carpet", "worn green carpet" }),
        "The floor of the shop is covered by a well-worn green carpet.\n");
    add_item( ({ "ceiling", "up", "roof", "beam", "beams",
                 "wooden beams", "wood", "powerful beams",
                 "powerful wooden beams" }),
        "The roof of the shop is supported by powerful wooden beams.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside this shop.\n");
    add_item( ({ "door", "doorway" }),
        "The door leads out of the shop onto Artisans Way.\n");
    add_item(({ "shelves", "cases", "shelf", "case",
                "shelves and cases", "cases and shelves",
                "display case", "display cases", "wares" }),
        "Shelves and cases display a number of the owner's wares. You"
      + " can <list> what is available if the owner is present.\n");


    set_hated_race( ({ "goblin" }) );
    set_suspected_race( ({ "gnome", "dwarf", "hobbit" }));
    set_favoured_race( ({ "elf" }) ); 

    add_cmd_item( ({ "poster" }),
                  ({ "exa", "read" }), exa_poster());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the general store.");

    add_exit("/d/Emerald/telberin/artisans_way07", "north", 0, 1, 1);
    add_exit("/d/Emerald/telberin/artisans_way07", "out");

    set_office("the General Store of Telberin", 10);

    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the General Store of Telberin");
    set_no_sell_prop( EMERALD_M_TELBERIN_NO_SELL );

    reset_room();
} /* create_shop */


/*
 * Function name:        exa_poster
 * Description  :        give text for the poster add_item
 * Returns      :        string - the desc
 */
public string
exa_poster()
{
    return "Welcome to the General Store of Telberin!\n" +
        "You can try these instructions: \n" +
        "    buy bag for gold and get copper back\n" +
        "    buy bag for gold coins\n" +
        "    sell bag for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                items you wield or wear.\n" +
        "    sell all! - will let you sell ALL items you have,\n" +
        "                except armours and weapons.\n" +
        "    sell bag, sell second bag, sell bag 2, sell two bags\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too. Beware, you will never buy\n"+
        "                more than one item at a time. So if you really\n" +
        "                want those three expensive bags, you have to\n" +
        "                repeat yourself three times.\n\n"+
        "Delivery tours:\n" +
        "    ask for a delivery tour\n" +
        "    deliver packet - to deliver a packet here.\n" +
        "    return packet  - to return a packet you do not want to deliver.\n\n";
} /* exa_poster */

public void
print_message(string str)
{
    keeper->command("say " + str);
}

int
do_buy(string args)
{
  if (check_keeper()) return ::do_buy(args);
  return 0;
}

int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}

int
do_sell(string args)
{
  if (check_keeper()) return ::do_sell(args);
  return 0;
}

int
do_list(string args)
{
  if (check_keeper()) return ::do_list(args);
  return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("frown");
    keeper->command("say Where did you get this "+ob->short()+"?");

    if (ob->query_prop(EMERALD_M_TELBERIN_NO_SELL))
    {
        keeper->command("say This is the armament of our very own city!");
        keeper->command("say You could not have come by this honorably ...");
        keeper->command("say Get out, before I summon the Protectorate!");
    }
}

mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x) || armour_filter(x))
    {
      keeper->command("say Sorry, I don't trade in weapons and armours.");
      return "The shopkeeper says: The weapon dealer might want your "
        + x->short()+".\n"+
        "The shopkeeper says: He is just east of Artisans Plaza.\n";
    }
    else
      return 0;
}

void
init()
{
    ::init();
    init_shop();
    init_office();
}

void
reset_room()
{
    object keeper;

    if (!query_keeper())
    {
        setuid();
        seteuid(getuid());
	keeper = clone_object(TELBERIN_MERCANTILE_DIR + "npc/store_owner");
        set_keeper(keeper);
        keeper->move(this_object(), 1);
        tell_room(this_object(),
		  ({ keeper->query_Met_name() + " arrives.\n",
		     LANG_ADDART(keeper->query_nonmet_name()) + " arrives.\n",
		     "" }));
    }

    reset_office();
}


public mixed
query_location_ids()
{
    return "[the] [south] [southern] [broad] [broad,] [green]"
      + " [green-roofed] [roofed] [general]"
      + " 'shop' / 'store' / 'building' [of] [telberin] [to] [the] [south]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "This is the General Store of Telberin.\n";
}

public string
query_entry_desc()
{
    return "into the general store";
}
