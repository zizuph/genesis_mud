/*
 * blacksmith_forge.c
 *
 * Forge of the blacksmith of Port Macdunn.
 *
 * Khail - March 30/97
 */
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

#define STORE "/d/Khalakhor/se_speir/port/room/blacksmith_store"

inherit "/std/room";
inherit "/lib/shop";

object smith;

public int *
query_local_coords()
{
    return ({10,6});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: reset_room
 * Description  : Resets the room, mainly to make sure the smith
 *                is where he's supposed to be.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (!smith)
    {
        smith = clone_object(NPC + "gruoch");
        smith->move(TO);
        tell_room(TO, QCTNAME(smith) + " wanders in from " +
            "the back room.\n");
        return;
    }
    else if (!present(smith))
    {
        if (smith->query_attack())
            return;
        else
        {
            tell_room(environment(smith), QCTNAME(smith) +
                "suddenly looks around with a start, and rushes " +
                "off somewhere.\n");
            smith->move_living("M", TO);
            tell_room(TO, QCTNAME(smith) + " rushes in from " +
                "the street outside.\n");
        }
    }
}

/*
 * Function name: create_room
 * Description  : Turns this object into a post office.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("a hot smithy");
    set_long("There's no mistaking the forge of a blacksmith, " +
        "and you're standing beside one now. This is the " +
        "shop of the local blacksmith, and although he " +
        "doesn't appear to be very busy, the ordered and " +
        "relatively clean workshop indicates he's quite " +
        "skilled in what he does. A heavy stone forge stands " +
        "in the center of the room, and a bellows rests on " +
        "floor beside it. Near the door stands a massive anvil. " +
        "Bins of stock metal line the walls beside barrels of " +
        "water and oil for quenching hot metal. A sign " +
        "hangs from one wall, and a smaller plaque beneath " +
        "it.\n");

    add_item(({"sign", "plaque"}),
        "It looks worth reading.\n");
    add_item(({"forge"}),
        "The heavy forge in the center of the room is full of " +
        "brightly-glowing coals.\n");
    add_item(({"coals", "brightly-glowing coals"}),
        "Within the stone forge in the center of the room, a " +
        "pile of coals glow brightly, hot enough to soften " +
        "steel for working.\n");
    add_item(({"anvil", "heavy anvil", "iron anvil"}),
        "A heavy, iron anvil stands near the forge, where countless " +
        "iron tools and weapons have been hammered out.\n");
    add_item(({"bin", "large bin"}),
        "The large bin contains piles of iron, both scrap and " +
        "raw ingots, to be used for the forging of new blades.\n");
    add_item(({"iron", "piles of iron"}),
        "There's two distinct different piles of iron in the bin, " +
        "one appears to be pure, raw ingots of iron, the other " +
        "contains shreds of scrap iron left over from projects, or " +
        "from items that broke and couldn't be repaired.\n");
    add_item(({"ingots", "pile of ingots"}),
        "Regular-shaped blocks of pure iron, the ingots get used " +
        "in the blades of finer-quality weapons.\n");
    add_item(({"scrap iron", "pile of scrap iron"}),
        "The scrap iron pile is somewhat larger than the one with " +
        "the iron ingots, and full of pretty much what you'd " +
        "expect in a scrap heap, nothing useful.\n");
    add_item(({"barrels"}),
        "The barrels contain a couple different liquids, presumably " +
        "for quenching blades off the forge. One barrel holds " +
        "fresh water, the other some sort of oil, but neither " +
        "strike you as all that interesting.\n");
    add_item(({"floor", "ground"}),
        "The floor of forge is hard-packed dirt, and pock-marked " +
        "where bits of hot iron landed.\n");
    add_item(({"walls", "wall"}),
        "The walls of the smithy are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the forge is also made of stone, somehow " +
        "cunningly placed and mortared in place, so no wood was " +
        "used in the construction of the building, reportedly a " +
        "building technique known only to the masters of the " +
        "different smithy crafthalls.\n");

    INSIDE;

    add_exit(ROOM + "road_10_7", "south");
    set_alarm(0.5, 0.0, reset_room);

    config_default_trade();
    set_store_room(STORE);    
}

/*
 * Function name: read_plaque
 * Description  : ALlows players to attempt to read the plaque.
 * Arguments    : str - What the player's trying to read as a string.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
read_plaque(string str)
{
    NF("Read what?\n");

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] [small] 'plaque'"))
        return 0;

    write("The plaque says:\n" +
        "    I make a variety of items such as tools and\n" +
        "    equipment, as well as repair older weapons.\n" +
        "    The fastest way to get my attention is by using\n" +
        "    the following commands, if I'm around.\n" +
        "        repair <what> - Repair a weapon.\n" +
        "        polish <what> - Clean the rust from a weapon.\n" +
        "\n");
    return 1;
}

/*
 * Function name: cmd_lock
 * Description  : Rather than use the default init_shop() call here
 *                to add all the shop commands to players entering
 *                the store, we'll manually redefine these commands
 *                that require a shopkeeper be present so we can
 *                easily ensure the shopkeeper actually is in the
 *                room.
 * Arguments    : str - String arguments to whichever command the
 *                      player used.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
cmd_lock(string str)
{
    string verb = query_verb();

    if (!smith || !present(smith, TO))
    {
        write("You cannot " + verb + " anything, the blacksmith " +
            "seems to be elsewhere.\n");
        return 1;
    }

    if (verb == "buy")
        return do_buy(str);
    else if (verb == "sell")
        return do_sell(str);
    else if (verb == "value")
        return do_value(str);
    else if (verb == "show")
        return do_show(str);
    else if (verb == "list")
        return do_list(str);
    return 0;
}

public void
init()
{
    ::init();
    add_action(read_plaque, "read");
    add_action(cmd_lock,   "buy");
    add_action(cmd_lock,  "sell");
    add_action(cmd_lock, "value");
    add_action(cmd_lock,  "show");
    add_action(cmd_lock,  "list");
    add_action(do_read,  "read");
    add_action(do_store, "store");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects the player intend
 *		  to sell. Here we allow only the sale of weapons that have
 *                a bludgeon weapon type.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
public int
shop_hook_allow_sell(object ob)
{
    string str;
    int wt;

    if (!(str = function_exists("check_weapon", ob)) ||
        str != "/std/weapon")
    {
        smith->command("say I'm only interested in weapons, " +
            "try Brom, he buys and sells most anything in his " +
            "shop.");
        NF("");
        return 0;
    }

    if (!(ob->query_wt() & W_BLUDGEON))
    {
        smith->command("say I'm only interested in bludgeoning " +
            "weapons. Have you been to Rohm? he's the local " +
            "bladesmith and usually deals with anything else.");
        NF("");
        return 0;
    }

    return 1;
}
