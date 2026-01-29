/*
 *  coded by Amelia for Ten Alders 11/16/97
 *  equipment shop for Ten Alders and Gont Port
 *  to sell backpacks, sacks, purses, torches, etc.
 *  
 *  Fixed a bug in no_afford--Amelia, 6/11/98
 *  Changed backpack to dufflebag-- Amelia 7/5/98
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/sys/global/money";

#include <stdproperties.h>

#define PRICE_SACK  300
#define PRICE_BACKPACK 600
#define PRICE_TORCH 100
#define PRICE_PURSE 250
#define PRICE_LAMP 250
#define PRICE_FLASK 150

#define STOREKEEPER "/d/Earthsea/gont/gont_city/liv/storekeeper"
#define SACK "/d/Earthsea/gont/tenalders/obj/items/sack"
#define BACKPACK "/d/Earthsea/gont/tenalders/obj/items/dufflebag"
#define PURSE "/d/Earthsea/gont/tenalders/obj/items/scrip"
#define TORCH "/d/Earthsea/gont/tenalders/obj/items/torch"
#define LAMP "/d/Gondor/common/obj/oil_lamp"
#define FLASK "/d/Gondor/common/obj/oilflask"

private object storekeeper;

public void
reset_room()
{
    if(!objectp(storekeeper))
    {
        storekeeper = clone_object(STOREKEEPER);
        storekeeper->move(this_object(), 1);
        storekeeper->command("emote walks in.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Equipment shop");
    set_long("An equipment shop. You smell the "+
        "pungent aroma of new leather as you look around at "+
        "the items in this shop. There are new packs, sacks "+
        "and other implements for the traveller lying arranged "+
        "in heaps and hanging from hooks on the walls. There is "+
        "a wooden sign on the wall by a counter where the "+
        "storekeeper stands, watching the customers with a "+
        "wary eye to make sure no one steals anything. "+
        "This is clearly the shop of a craftsman who takes pride in "+
        "his work, as you can tell from the shine of the polished "+
        "NEW equipment.\n");
    add_item((({"equipment", "packs", "sacks",
        "implements", "heaps", "items" })),
        "You can see quantities of new leather backpacks, sacks, "+
        "dufflebags, "+
        "purses, torches and other equipment on display for sale. "+
        "Read the sign for more information.\n");
    add_item("sign", "Why don't you read it?\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("city_street/city_road32", "north");
    reset_room();
}

public void
too_heavy(object who, object thing)
{
    storekeeper->command("say Hmmm...seems you are too "+
        "loaded down. I will just set it here for you.\n");
    thing->move(this_object(), 1);
}

public void
no_afford(object who)
{
    int act = random(3);

    if(act == 0)
    {
        storekeeper->command("say You can't afford that much!");
        storekeeper->command("poke " + who->query_name());

        return;
    }

    if(act == 1)
    {
        storekeeper->command("say Get out of my store, "+
            "you bum!");
        storekeeper->command("peer " + who->query_real_name());

        return;
    }

    storekeeper->command("hmm");
    storekeeper->command("say I'm not doing charity!");
    storekeeper->command("say No money no deal.");
    storekeeper->command("nudge " + who->query_real_name());
}

public int
buy_equip(string str)
{
    object ob, tp = this_player();
    string item;
    int price;

    if(!str)
    {
        return notify_fail("Buy what?\n");
    }

    setuid();
    seteuid(getuid());

    if(!objectp(storekeeper))
    {
        return notify_fail("The storekeeper is not here.\n");
    }

    switch(str)
    {
        case "sack":
        case "leather sack":
            price = PRICE_SACK;
            item = SACK;
        break;

        case "backpack":
        case "pack":
        case "rugged leather dufflebag":
        case "dufflebag":
        case "leather dufflebag":
            price = PRICE_BACKPACK;
            item = BACKPACK;
        break;

        case "lamp":
        case "oil lamp":
        case "oil-lamp":
        case "oillamp":
            price = PRICE_LAMP;
            item = LAMP;
        break;

        case "oil":
        case "oil-flask":
        case "flask":
        case "oilflask":
            price = PRICE_FLASK;
            item = FLASK;
        break;

        case "purse":
        case "leather purse":
        case "scrip":
            price = PRICE_PURSE;
            item = PURSE;
        break;

        case "torch":
        case "large torch":
            price = PRICE_TORCH;
            item = TORCH;
        break;

        default:
            return notify_fail("Buy what?\n");
    }

    if(take_money(tp, price) == 0)
    {
        no_afford(tp);
        return 1;
    }

    ob = clone_object(item);

    if(ob->move(tp))
    {
        too_heavy(tp, ob);
        return 1;
    }

    write("You pay the storekeeper and get your "+
        ob->short() + ".\n");
    return 1;
}

public int
list_equip(string str)
{
    if(!objectp(storekeeper) || !present(storekeeper, this_object()))
    {
        write("There is no storekeeper here!\n");
        return 1;
    }

    if(str == "equipment" || str == "equip")
    {
        storekeeper->command("say I have the following items in "+
            "stock:\nBackpacks, sacks, purses and torches.");
        storekeeper->command("emote points at the sign.");
        storekeeper->command("say Read the sign for current prices.");

        return 1;
    }

    return notify_fail("List what? Maybe you should read the sign.\n");
}

public int
read_sign(string str)
{
    if(str == "sign" || str == "wooden sign") 
    {
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
            " You can <list equipment> or <list equip> to find out\n"+
            " what is in stock.\n"+
            "\n\n"+
            " * WE DO NOT DEAL IN USED MERCHANDISE!! *\n" +
            " ----------------------------------------------\n\n");

        return 1;
    }

    return notify_fail("Read what?\n");
}

public void
init()
{
    ::init();
    add_action(read_sign, "read");
    add_action(buy_equip, "buy");
    add_action(list_equip, "list");
}
