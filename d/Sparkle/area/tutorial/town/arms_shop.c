/*
 *  /d/Emerald/telberin/mercantile/arms_shop.c
 *
 *  This is the arms dealership in Telberin.
 *
 *  Modified from /d/Gondor/minas/rooms/mtarms.c
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit TELBERIN_BUILDING;
inherit "/d/Emerald/lib/shop";

#include <stdproperties.h>
#include <language.h>
#include "/d/Emerald/quest_handler/quest_handler.h"

#define STORE_ROOM "/d/Emerald/telberin/mercantile/arms_store"


/* prototypes */
public string describe_hilt();
public void reset_room();

/*
 * Function name:        create_shop
 * Description  :        set up the shop
 */
public void
create_telberin_building()
{
    set_short("The Telberin Arms Dealer");

    set_em_long("This appears to be a shop dedicated to the trading"
      + " of weapons and armour. Great care has gone into creating"
      + " an efficient means of displaying as many items as"
      + " prominently as possible."
      + " The shop is crowded with shelves and cases displaying many"
      + " fine wares, nearly all of which are for sale.\n");

    add_item( ({ "silver", "gilding", "silver gilding" }),
        "Silver gilding adorns a small display case which looks"
      + " distinguished compared with the others.\n");
    add_item( ({ "shop", "store", "arms shop", "telberin arms shop",
                 "room", "area" }), long);
    add_item( ({ "wall", "walls" }),
        "The walls of the shop are crowded with shelves, many of"
      + " which display interesting armours and weapons that"
      + " might possibly be for sale.\n");
    add_item( ({ "floor", "ground", "down", "carpet", "red carpet",
                 "worn carpet", "well-worn carpet",
                 "well-worn red carpet", "worn red carpet" }),
        "The floor of the shop is covered by a well-worn red carpet.\n");
    add_item( ({ "ceiling", "up", "roof", "beam", "beams",
                 "wooden beams", "wood", "powerful beams",
                 "powerful wooden beams" }),
        "The roof of the shop is supported by powerful wooden beams.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside this shop.\n");
    add_item( ({ "door", "doorway" }),
        "The door leads out of the shop onto Artisans Plaza.\n");
    add_item(({ "shelves", "cases", "shelf", "case",
                "shelves and cases", "cases and shelves",
                "display case", "display cases", "wares",
                "weapon", "weapons", "armour", "armours" }),
        "Shelves and cases display a number of the dealer's wares."
      + " You notice one smaller case which is gilded with silver.\n");
    add_item( ({ "small case", "smaller case", "silver case", "silver",
                "silver-gilded case", "case gilded with silver",
                "gilded case", "small display case" }),
        "Within the silver-gilded case, you see the hilt of a very"
      + " old sword. It is engraved with the emblem of Telberin,"
      + " and appears to be an antique of some kind.\n");
    add_item( ({ "hilt", "hilt of the old sword", "sword hilt",
                 "antique", "antique hilt",
                 "hilt of the very old sword" }), describe_hilt);



    set_shop_name("the Telberin Arms Shop");

    set_no_sell_prop( EMERALD_M_TELBERIN_NO_SELL );

    set_hated_race( ({ "goblin" }) );
    set_suspected_race( ({ "gnome", "dwarf", "hobbit" }));
    set_favoured_race( ({ "elf" }) ); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the arms shop.");


    add_exit("/d/Emerald/telberin/artisans_plaza", "west", 0, 1, 1);
    add_exit("/d/Emerald/telberin/artisans_plaza", "out");

    setup_shop();
    set_store_room(STORE_ROOM);

    reset_room();
}

public void
reset_room()
{
    object keeper;

    if (!query_keeper())
    {
        setuid();
        seteuid(getuid());
	keeper = clone_object(TELBERIN_MERCANTILE_DIR + "npc/arms_dealer");
        set_keeper(keeper);
        keeper->move(this_object(), 1);
        tell_room(this_object(),
		  ({ keeper->query_Met_name() + " arrives.\n",
		     LANG_ADDART(keeper->query_nonmet_name()) + " arrives.\n",
		     "" }));
    }
}

public void
init()
{
    ::init();
    init_shop();
}

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x) && !armour_filter(x))
        return "The shopkeeper says: I have no interest in your " + x->short() + " ... \n"+
               "The shopkeeper says: I trade exclusively in weapons and armours.\n";
    else
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


/*
 * Function name:        describe_hilt
 * Description  :        provide a description for the "hilt" add_item.
 *                       if the armourer is present, there is more
 *                       information provided
 * Returns      :        string - the descripion for the add_item
 */
public string
describe_hilt()
{
    string txt = "The hilt of the sword is finely engraved with the"
               + " emblem of Telberin. It looks very old indeed. ";

    if (present("_telberin_antique_sword_dealer", this_object()))
    {
        if (QH_QUERY_QUEST_COMPLETED(this_player(), "antique_sword"))
        {
            txt += "The shopkeeper smiles appreciatively in your"
                 + " direction and mutters: I don't dare display"
                 + " the one you found me ... far too precious!";

            return txt + "\n";
        }

        txt += "The shopkeeper notices as you closely examine the"
             + " case, and shouts out: Oh, I don't make weapons, but"
             + " I'm an avid collector of antique arms! That is one"
             + " of the rarest swords in Telberin, and I've never"
             + " managed to find one fully intact.";
    }

    return txt + "\n";
} /* describe_hilt */


public mixed
query_location_ids()

{
    return "[the] [east] [eastern] [long] [telberin] [arms] 'shop' / 'building' / 'dealer' / 'arms' [shop] [of] [telberin] [to] [the] [east]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "This is the Telberin Arms Dealer.\n";
}

public string
query_entry_desc()
{
    return "into the arms shop";
}
