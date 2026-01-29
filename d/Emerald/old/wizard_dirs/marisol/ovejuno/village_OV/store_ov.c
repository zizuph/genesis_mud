/*
 * Equipment shop for Ten Alders
 * coded by Amelia for Ten Alders 11/16/97  
 * to sell backpacks, sacks, purses, torches, etc.
 * Modified to be used as a General Store in the Re Albi's village 
 * by Marisol (2/10/98) 1998
 * Modified by Marisol (07/20/98) to be used in the village of 
 * Ovejuno in Emerald.*/

#pragma no_clone
#pragma strict_types

inherit "/d/Emerald/std/room";

#include "defs.h"
#include <stdproperties.h>

static object storekeeper;

void
reset_room()
{
    if (!objectp(storekeeper))
    {
        storekeeper = clone_object(STOREKEEPER);
        storekeeper->move(this_object(), 1);
        storekeeper->command("emote walks in.");
    }
}

void
create_emerald_room()
{
    string sign;

    set_short("General store");
    set_long("The General Store of Ovejuno. Here you can find "+
        "very useful things that different craftmen have sold to the "+
        "owner of this shop. The store is really tidy and clean. "+
        "The owner of the store looks suspictiously around "+
        "no trusting its customers. He stands in front of his "+
        "inventory, like a hen over her eggs. There is "+
        "a wooden sign on the wall by a counter where the "+
        "storekeeper stands, watching the customers with a "+
        "wary eye to make sure no one steals anything. "+
        "If you want to buy something maybe you should read the "+
        "sign.\n");

    sign = 
          "The sign reads:\n" +
          "----------------------------------------------\n" +
          " Here you can buy the following NEW equipment \n" +
          " for your journeys: \n" +
          " ---------------------------------------------\n\n" +
          " - brand new large torch   100cc \n"+
          " - nice terra cota oil lamp   450cc\n"+
          " - buy some oil for your trusty lamp 250cc!\n"+
          " - beautiful new leather backpack 600cc\n"+
          "\n\n"+
          " You can <list equipment> or <list equip> to find out "+
          " what is in stock.\n"+
          "\n\n"+
          " * WE DO NOT DEAL IN USED MERCHANDISE!! *\n" +
          " ----------------------------------------------\n\n";

    add_item(({ "sign", "wooden sign" }), sign);
    add_cmd_item(({ "sign", "wooden sign" }), "read", sign);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());

    reset_room();

    clone_object(DOORS + "shop_door_in")->move(this_object(), 1);
}

int
buy_equip(string str)
{
    if (!present("ovejuno_storekeeper"))
    {
        notify_fail("The storekeeper is not here.\n");
    }

    return 0;
}

int
list_equip(string str)
{
    if (!present("ovejuno_storekeeper"))
    {
        notify_fail("There is no storekeeper here!\n");
    }

    return 0;
}                                                                

void
init()
{
    ::init();
    add_action(&buy_equip(), "buy");
    add_action(&list_equip(), "list");
}
