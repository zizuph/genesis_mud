/*
 * pub.c
 *
 * Pub of Tabor Sogh
 *
 * Khail - March 30/97
*
* Modified - added inherit "/d/Khalakhor/lib/pub"
* with updated menu
* Damaris 01/2001
*/
#pragma strict_types

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/pub";

#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
string
dummy_menu()
{
    read_menu("menu");
    return "";
}
object landlord;

public int *
query_local_coords()
{
    return ({2, 8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: reset_room
 * Description  : Resets global vars, specifically
 *                makes sure the landlord is where he's
 *                supposed to be, behind the bar!
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (!landlord)
    {
        landlord = clone_object(NPC + "landlord");
        landlord->arm_me();
        landlord->move(TO);
        tell_room(TO, QCTNAME(landlord) + " straightens " +
            "up from behind the bar.\n");
        return;
    }
    else if (!present(landlord))
    {
        if (landlord->query_attack())
            return;
        else
        {
            tell_room(environment(landlord), QCTNAME(landlord) +
                "suddenly looks around with a start, and rushes " +
                "off somewhere.\n");
            landlord->move_living("M", TO);
            tell_room(TO, QCTNAME(landlord) + " rushes in from " +
                "the street outside.\n");
        }
    }
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a pub.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("The Summer Squall");
    set_long("   You're in a small tavern, not intended for " +
        "very large crowds. A single firepit contains some " +
        "brightly burning peat, its pungent smoke drifting " +
        "upwards through a smoke hole in the thatch roof. " +
        "The smell of the peat smoke mingles with "+
        "the smell of stale ale, spilled whiskey and smoked "+
        "fish. A simple bar made of a few planks salvaged " +
        "from a shipwreck stands against one wall, and a " +
        "couple of long tables and benches made of similar " +
        "material fill the floor.\n");
   add_item("menu", &dummy_menu());
   add_item(({"floor", "ground"}),
        "The floor of the pub is made simply from hard-packed " +
        "dirt.\n");
    add_item(({"walls", "wall"}),
        "The walls of the pub are made from thin slates of " +
        "of some dark grey stone, carefully stacked to form " +
        "a wall that is relatively weather-proof and strong " +
        "despite the absence of any joining material.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the pub is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"bar"}),
        "Nothing very fancy, the bar is made from a few planks " +
        "that appear to have been salvaged from a shipwreck, " +
        "placed across the top of several empty hogsheads. " +
        "A small sign is suspended from the front of the " +
        "bar.\n");
    add_item(({"planks","plank"}),
        "The planks are large boards, badly dried and split, " +
        "possibly from exposure to salt water.\n");
    add_item(({"hogshead","hogsheads"}),
        "The hogsheads are very large wooden casks, now empty " +
        "of their highly-alcoholic contents and turned to " +
        "more mundane chores.\n");
    add_item(({"table","tables"}),
        "The tables are long and low, constructed in similar " +
        "fashion to the bar, except fronted with a few small " +
        "benches.\n");
    add_item(({"benches","bench"}),
        "Looking at the splinters poking up from the dried " +
        "wooden benches, you wonder if anyone is ever " +
        "drunk or stupid enough to sit on one?\n");
    add_cmd_item(({"bench","benches","on bench","on benches"}),
        ({"sit"}), "One look at the splinters on those benches " +
        "and the thought of someone having to pull one out of " +
        "your ass overcomes your desire to rest your feet.\n");

    INSIDE;

    add_drink(({"bitter","mug","mug of bitter"}),
        ({"mug of bitter","bitter"}), "golden",
        250, 12, 24,
        "mug of bitter", "mugs of bitter",
        "The small wooden mug contains some strong-smelling, " +
        "golden bitter.\n", "");
    add_drink(({"bitter","pint","pint of bitter"}),
        ({"pint of bitter","bitter"}), "golden", 550, 27, 82,
        "pint of bitter","pints of bitter",
        "The large wooden mug contains a full pint of a strong-" +
        "smelling, golden bitter.\n", "");
    add_drink("whiskey", "whiskey", "golden",
        100, 40, 170,
        "glass of whiskey", "glasses of whiskey",
        "The small glass contains a golden whiskey with a " +
        "strong, smooth aroma.\n", "");

    add_food("herring", "herring", "fried",
        50, 10,
        "fried herring", "fried herrings",
        "The small herring has been deboned and fried.\n", "");
    add_food(({"halibut", "halibut steak"}), "steak", "halibut",
        150, 42,
        "halibut steak", "halibut steaks",
        "The halibut steak is lightly breaded and fried.\n", "");

    switch (random(3))
    {
        case 0:
            add_food("catch of the day", "squid", "fried",
                249, 100,
                "fried squid", "fried squids",
                "A squid body has been chopped into rings, which " +
                "were then fried in oil.\n", "");
            break;
        case 1:
            add_food("catch of the day", "steak", "shark",
                249, 100,
                "shark steak", "shark steaks",
                "A steak made from some kind of shark, which has " +
                "been lightly fried, and is surprisingly tender.\n", "");
            break;
        default:
            add_food("catch of the day", "salmon", "smoked",
                249, 100,
                "smoked salmon", "smoked salmons",
                "A fair-sized salmon that has been deboned, salted, " +
                "and hung to dry in a smoke house.\n", "");
    }

    add_exit(ROOM + "road_1_8", "west");

    reset_room();
}

void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Welcome to the Summer Squall!"));
}

/*
 * FUnction name: init (MASK)
 * Description  : Called when another object meets this object.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    init_pub();
}
