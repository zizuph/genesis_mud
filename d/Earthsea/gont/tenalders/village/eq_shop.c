/*
 * coded by Amelia for Ten Alders 11/16/97
 * equipment shop for Ten Alders and Gont Port
 * to sell backpacks, sacks, purses, torches, etc.
*/

inherit "/d/Earthsea/std/room";
inherit "/sys/global/money";

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>

#define PRICE_SACK  300
#define PRICE_BACKPACK 600
#define PRICE_TORCH 100
#define PRICE_PURSE 250
#define PRICE_LAMP 250
#define PRICE_FLASK 150
#define SACK "/d/Earthsea/gont/tenalders/obj/items/sack"
#define BACKPACK "/d/Earthsea/gont/tenalders/obj/items/dufflebag"
#define PURSE "/d/Earthsea/gont/tenalders/obj/items/scrip"
#define LAMP "/d/Earthsea/gont/tenalders/obj/items/oil_lamp"
#define TORCH "/d/Earthsea/gont/tenalders/obj/items/torch"
#define FLASK "/d/Earthsea/gont/tenalders/obj/items/oilflask"

private object storekeeper;

public void
reset_room()
{
    if(!objectp(storekeeper))
    {
        storekeeper = clone_object("/d/Earthsea/gont/tenalders/npc/storekeeper");
        storekeeper->move(this_object());
        storekeeper->command("emote walks in.");
    }
}

public void
create_earthsea_room()
{
    object door;

    set_short("Equipment shop");
    set_long("An equipment shop. You smell the " +
        "pungent aroma of new leather as you look around at " +
        "the items in this shop. There are new packs, sacks " +
        "and other implements for the traveller lying arranged " +
        "in heaps and hanging from hooks on the walls. There is " +
        "a wooden sign on the wall by a counter where the " +
        "storekeeper stands, watching the customers with a " +
        "wary eye to make sure no one steals anything. " +
        "This is clearly the shop of a craftsman who takes pride in " +
        "his work, as you can tell from the shine of the polished " +
        "NEW equipment.\n");
    add_item((({"equipment", "packs", "sacks",
        "implements", "heaps", "items" })),
        "You can see quantities of new leather dufflebags, sacks, " +
        "purses, torches and other equipment on display for sale. " +
        "Read the sign for more information.\n");
    add_item("sign", "Why don't you read it?\n");
    reset_room();
    add_prop(ROOM_I_INSIDE, 1);
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/shop_door_in");
    door->move(this_object());
}

public int
read_sign(string str)
{
    if(str != "sign" && str != "wooden sign")
    {
        return notify_fail("Read what?\n");
    }

    write("The sign reads:\n" +
        "----------------------------------------------\n" +
        " Here you can buy the following NEW equipment \n" +
        " for your journeys: \n" +
        " ---------------------------------------------\n\n" +
        " - brand new large torch   100cc \n"+
        " - finely crafted leather sack   300cc\n"+
        " - keep your money safe! buy a purse for only 250cc!\n"+
        " - rugged leather dufflebag 600cc\n"+
        " - oil-lamp      250cc\n"+
        " - oil-flask     150cc\n"+
        "\n\n"+
        " You can <list equipment> or <list equip> to find out"+
        " what is in stock.\n"+
        "\n\n"+
        " * WE DO NOT DEAL IN USED MERCHANDISE!! *\n" +
        " ----------------------------------------------\n\n");

    return 1;
}

public int
no_afford(object who)
{
    int act;

    if(!objectp(storekeeper))
    {
        return notify_fail("There is no storekeeper here.\n");
    } else if((act = random(3)) == 0) {
        storekeeper->command("say You can't afford that much!");
        storekeeper->command("poke " + who->query_real_name());
        return 1;
    } else if (act == 1) {
        storekeeper->command("say Get out of my store, " +
            "you bum!");
        storekeeper->command("peer " + lower_case(who->query_real_name()));
        return 1;
    }

    storekeeper->command("hmm");
    storekeeper->command("say I'm not doing charity!");
    storekeeper->command("say No money no deal.");
    storekeeper->command("nudge " + lower_case(who->query_name()));
    return 1;
}

public int
too_heavy(object who, object thing)
{
    storekeeper->command("say Hmmm...seems you are too "+
        "loaded down. I will just set it here for you.\n");
    thing->move(this_object());
    return 1;
}

public int
buy_equip(string str)
{
    object dummy, tp = this_player();

    if(!str)
    {
        return notify_fail("Buy what?\n");
    }

    setuid();
    seteuid(getuid(this_object()));

    if(!objectp(storekeeper))
    {
        return notify_fail("The storekeeper is not here.\n");
    }

    switch(str)
    {
        case "sack":
        case "leather sack":
            if(take_money(tp, PRICE_SACK) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(SACK);
        break;
        case "backpack":
        case "pack":
        case "dufflebag":
        case "leather dufflebag":
        case "rugged leather dufflebag":
            if(take_money(tp, PRICE_BACKPACK) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(BACKPACK);
        break;
        case "lamp":
        case "oil lamp":
        case "oil-lamp":
        case "oillamp":
            if(take_money(tp, PRICE_LAMP) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(LAMP);
        break;
        case "oil":
        case "oil-flask":
        case "flask":
        case "oilflask":
            if(take_money(tp, PRICE_FLASK) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(FLASK);
            dummy->set_short("oil-flask");
        break;
        case "purse":
        case "leather purse":
        case "scrip":
            if(take_money(tp, PRICE_PURSE) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(PURSE);
        break;
        case "torch":
        case "large torch":
            if(take_money(tp, PRICE_TORCH) == 0)
            {
                no_afford(tp);
                return 1;
            }

            dummy = clone_object(TORCH);
        break;
        default:
            return notify_fail("Buy what?\n");
        break;
    }

    if(dummy->move(tp))
    {
        too_heavy(tp, dummy);
        return 1;
    }

    write("You pay the storekeeper and get your " +
        dummy->query_short() + ".\n");
    return 1;
}

public int
list_equip(string str)
{
    if(!objectp(storekeeper))
    {
        write("There is no storekeeper here!\n");
        return 1;
    } else if(str == "equipment" || str == "equip") {
        storekeeper->command("say I have the following items in " +
            "stock:\nBackpacks, sacks, purses and torches.");
        storekeeper->command("emote points at the sign.");
        storekeeper->command("say Read the sign for current prices.");
        return 1;
    }

    return notify_fail("List what? Maybe you should read the sign.\n");
}

public int
sell_something(string str)
{
    if(objectp(storekeeper))
    {
        storekeeper->command("say I don't buy back used equipment!");
        storekeeper->command("point sign");
        return 1;
    }

    return notify_fail("There is no storekeeper here.\n");
}

public void
init()
{
    ::init();
    add_action(read_sign, "read");
    add_action(buy_equip, "buy");
    add_action(list_equip, "list");
    add_action(sell_something, "sell");
}
