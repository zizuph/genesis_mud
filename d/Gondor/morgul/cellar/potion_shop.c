/*
 *  Potion Shop
 *
 *  Originally coded by Falke@Angalon as herb shop
 *  Modified for Minas Morgul in Gondor@Genesis by Olorin, July 1994
 *
 *  Modification Log:
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";
inherit "/d/Gondor/common/lib/potion_shop.c";
inherit "/d/Gondor/morgul/feeling.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

#define MIN_STRENGTH	90

void
create_morgul_cellar_room()
{
    FIX_EUID;

    /* this line needed to created default trade configuration */
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(150);

    set_room_type("alchemist's shop");
    set_extra_long("A small lamp gives some light here, illuminating " +
      "a high stone bench which serves as counter. On the counter " +
      "stands a sign. Behind the counter, there are many wooden " +
      "boards filled with bottles, vials, mortars.");

    /* set the room to be used as storage room for this shop */
    set_store_room(CELLAR_DIR + "potion_storage");
    call_other(store_room, "load_me");

    set_level(1);

    add_floor();
    add_walls();
    add_stones();
    add_item(({"roof","ceiling"}), 
       "From the high vaulted ceiling a small lamp is hanging, " +
       "filling the room with faint light.\n");
    add_item(({"sign", "poster"}), read_sign());
    add_cmd_item(({"sign", "poster"}), "read", read_sign());
    add_item(({"small shop", "alchemist's shop","shop"}), 
       "In this dark and dusty room an alchemist buys and sells " +
       "the tools of his trade and all kinds of potions.\n");
    add_item(({"counter", "high stone bench", "stone bench", 
       "high bench", "bench"}), 
       "This is a narrow stone slab standing on one of its small " +
       "sides. The alchemist uses it as a counter. On it, there is " +
       "a sign with something written on it.\n");
    add_item(({"lamp", "light"}), 
       "A single lamp hanging from the ceiling tries to give light " +
       "to the room. But it is a rather feeble attempt.\n");
    add_item(({"windows"}), "There are no windows here.\n");
    add_item(({"board", "boards"}), 
       "There are many different things on the board. Some of them " +
       "you can buy, others are probably so valuable to the alchemist " +
       "that he is unlikely to be willing to part with them. Among " +
       "other items you can make out bottles filled with potions, " +
       "empty vials and a large collection of mortars on the boards.\n");
    add_item(({"mortar", "mortars", "vial", "vials"}),
       "On one board there are empty vials and mortars presented " +
       "for sale. If you have enough coins you can equip yourself " +
       "here with the tools of trade of an alchemist.\n");
    add_item(({"bottle", "bottles"}), 
       "Some bottles are empty, others are filled with liquids or " +
       "pills. Perhaps some of the potions and pills are for sale, " +
       "but probably not all are.\n");

    add_exit(CELLAR_DIR + "pass_1e2", "north", 0);

    add_prop(ROOM_I_LIGHT, 1);   /* A lamp is giving light in here */
    add_prop(ROOM_I_HIDE, 25);   /* But it's not much light, */
				 /*  so it's easy to hide */

    set_satchel_file("/d/Gondor/morgul/obj/satchel");
}

void
init()
{
   ::init();

   init_potion_shop();
}

string
read_sign()
{
   return "\t ___________________________________________\n" +
          "\t/                                           \\\n" +
          "\t|         The Alchemist's Provider          |\n" +
          "\t|        ~~~~~~~~~~~~~~~~~~~~~~~~~~         |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t|     From our large stock, we also sell    |\n" +
          "\t|        vials, satchels, and mortars,      |\n" +
          "\t|           but we do not buy them!         |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t|        You can list what we offer.        |\n" +
          "\t|         You buy at your own risk,         |\n" +
          "\t|       complaints will be laughed at!      |\n" +
          "\t\\___________________________________________/\n";
}

int
query_shop_no_business(mixed pl)
{
    if (stringp(pl))
    {
        pl = find_living(pl);
    }

    if (query_verb() == "buy")
    {
        if (IS_MORGUL_MAGE(pl) || pl->query_wiz_level()) return 0;
//        if (query_feeling(pl) >= 0)
            return 1;
    }
    else
    {
        if (query_feeling(pl) > 0)
            return 1;
    }

    return 0;
}

static int
shop_hook_allow_sell(object ob)  /*If not an potion, don't take it*/
{
    int     alco = -1;
    mixed   values;

    if (!(::shop_hook_allow_sell(ob)))
    {
        return 0;
    }

    // further checks only on Morgul potions:
    if (function_exists("create_potion", ob) != 
	       ("/d/Gondor/guilds/morgulmage/potions/base_potion"))
    {
        return 1;
    }

    if (pointerp(values = store_room->query_potion_values(MASTER_OB(ob))))
    {
        // Mean value of alco for potions in stock:
        if (sizeof(values) > 2)
        {
            alco = values[2] / values[0];
        }
    }

    if (((alco > 0) && (ob->query_alco_strength() < (alco * 9 / 10))) ||
	(ob->query_strength() < MIN_STRENGTH))
    {
        NFN("The alchemist refuses to buy your potion as he " +
            "recognizes its inferior quality.");
        return 0;
    }
    return 1;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object further if you
 *                allow it to be bought
 * Arguments:     ob - The object player wants to buy.
 * Returns:       1 if we allow it to be bought (default)
 */
int
shop_hook_allow_buy(object ob)
{
    if (function_exists("create_potion", ob) != 
	("/d/Gondor/guilds/morgulmage/potions/base_potion"))
    {
	/* not a morgul potion -- anyone may buy it */
	return 1;
    }
    if (TP->query_guild_name_occ() == "Morgul Mages")
    {
	/* a morgul mage may buy any potion */
	return 1;
    }
    /* morgul potion and not a morgul mage -- refuse */
    tell_room(TO,
	"The alchemist says: You are not authorized to purchase " +
	"that potion, fool!\n");
    tell_room(TO, "The alchemist glares at "+QTNAME(TP)+".\n", TP);
    notify_fail("The alchemist glares at you.\n");
    return 0;
}


public void
shop_hook_no_business(object pl)
{
    tell_room(TO,
        "The alchemist says: We don't deal with the likes of you!\n");
    tell_room(TO,
        "The alchemist spits at "+QTNAME(pl)+"\n", pl);
    tell_room(TO,
        "The alchemist says: Leave before I call the guards!\n");
    notify_fail("The alchemist spits at you.\n");
}
