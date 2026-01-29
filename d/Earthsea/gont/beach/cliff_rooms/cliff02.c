/*
 * Cliff on Gont beach
 * By Finwe
 * May 1997
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include "default.h"

inherit CLIFFS_ROOM;
inherit "/d/Emerald/lib/shop_list";

#define BEACH_STORE "/d/Earthsea/gont/beach/beach_store"
#define OLD_MAN "/d/Earthsea/gont/beach/npc/old_man"

private object old_man;

public void
create_cliffs()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    config_default_trade();
    set_money_greed_sell(100);
    set_money_greed_buy(100);

    set_store_room(BEACH_STORE);
    set_short("A ledge on the cliff");
    set_long("You stand on a ledge below the cliffs. "+
        "The waves crash up and over you occasionally, but never seem to spray "+
        "you. A natural opening has been enlarged to the size of " +
        "a small home. A grizzled old man sits here, looking " +
        "out to sea. Various articles are scattered about, "+
        "and it seems the old man does some small business here. "+
        "In fact, you might be able to <buy>, <sell> or <list> "+
        "items here.\n");

    add_item("opening",
      "The opening is large but dark. It seems to have been " +
      "carved by the waves at one time but was enlarged. The " +
      "cave appears to be where the old man lives.\n");
    add_item("ledge",
      "This ledge is up out of the way of the crashing waves. " +
      "It is dry an quite large. It is swept clean of sand " +
      "and debris.\n");
    add_item(({"articles", "woven articles", "items", "woven items"}),
      "Various unfinished woven items are scattered around the " +
      "ledge. Some are in need of repair, while others are " +
      "only half completed.\n");
    reset_room();
    add_exit("cliff03", "up");
}

public void
reset_room()
{
    if(!old_man)
    {
        old_man = clone_object(OLD_MAN);
        old_man->move(this_object());
    } else if(!present(old_man)) {
        old_man->move_living("back to his shop", this_object());
    }
}

public int
check_old_man(string str)
{
    if(!objectp(old_man) || !present(old_man))
    {
        write("Hmm... the shop owner is not here.\n");
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();
    init_shop();
    add_action(check_old_man, "buy");
    add_action(check_old_man, "sell");
    add_action(check_old_man, "list");
}
