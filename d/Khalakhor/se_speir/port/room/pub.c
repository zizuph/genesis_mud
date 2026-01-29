/*
 * pub.c
 *
 * Pub of Port MacDunn
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
    return ({14, 8});
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
        landlord = clone_object(NPC + "murah");
        landlord->arm_me();
        landlord->move(TO);
        tell_room(TO, QCTNAME(landlord) + " wanders in from " +
            "the kitchen.\n");
        landlord->set_pub(TO);
        landlord->set_kitchen(ROOM + "kitchen");
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
            if (landlord->query_prop(LIVE_O_LAST_ROOM) == 
                find_object(ROOM + "kitchen"))
                tell_room(TO, QCTNAME(landlord) + " saunters in " +
                    "from the kitchen.\n");
            else
                tell_room(TO, QCTNAME(landlord) + " rushes in from " +
                    "the street outside.\n");
        }
    }
}

/*
 * Function name: kitchen_block
 * Description  : A VBFC that blocks the kitchen exit to anyone
 *                except wizards and npc's (at the moment).
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.
 *                1 - Player can't pass.
 */
public int
kitchen_block()
{
    if (!interactive(TP))
        return 0;

    if (TP->query_wiz_level())
        return 0;

    write("You aren't allowed in the kitchen!\n");
    return 1;
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
    set_short("The Wild Rover");
    set_long("   You're in The Wild Rover, what appears to " +
        "be the local pub. The room is fairly large, and " +
        "low-ceilinged, with grey stone walls adorned by " +
        "a sparse assortment of paintings and objects. " +
        "A bar stands against the north wall, behind which " +
        "the pub's landlord is usually constantly busy doing " +
        "whatever landlords do behind their bars. A menu " +
        "above the bar looks to be worthwhile reading.\n");

   add_item(({"floor", "ground"}),
        "The floor of the pub is made simply from hard-packed " +
        "dirt, and looks plain.\n");
    add_item(({"walls", "wall"}),
        "The walls of the pub are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay. Here and there, they are " +
        "decorated with a few paintings and assorted objects.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the pub is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"paintings"}),
        "None of the paintings are very good, most seem to " +
        "depict different ships, and a few look to be battle " +
        "scenes.\n");
    add_item(({"objects", "assorted objects"}),
        "Here and there around the pub, various objects adorn " +
        "the walls. You see a wheel from a ship of some sort, " +
        "an old lochaber axe, and a targe, but none of them " +
        "are very interesting.\n");
    add_item(({"wheel"}),
        "The wheel is made from wood and surrounded with " +
        "spokes, used the turn the rudder on larger ships.\n");
    add_item(({"lochaber axe", "axe"}),
        "It appears to be very old, the handle is pretty badly " +
        "dried out, and the blade covered in nicks and rust.\n");
    add_item(({"targe"}),
        "The targe is pretty plain, as far as they go. The small " +
        "shield has a spiked, brass boss in the front, and is " +
        "covered by a bright red cloth.\n");
    add_item(({"bar"}),
        "A long, wooden bar stands against the north wall, " +
        "behind which the landlord keeps all the good stuff.\n");
   add_item("menu", &dummy_menu());
    INSIDE;

    add_drink(({"watered wine","wine","water wine"}),({"watered wine","wine"}),"watered",
        200, 2, 10,
        "cup of watered wine", "cups of watered wine",
        "The cheap tin cup contains a small amount of " +
        "watered-down wine.\n", "");
    add_drink(({"ale","mug","mug of ale"}),({"mug of ale","ale"}),"dark",
        250, 12, 24,
        "mug of ale", "mugs of ale",
        "The wooden mug contains a rich brew of dark, foamy " +
        "ale.\n", "");
    add_drink("pint of ale", ({"pint of ale", "ale"}), "dark",
        550, 27, 82,
        "pint of ale", "pints of ale",
        "The tin mug contains a full pint of a rich brew of " +
        "dark, foamy ale.\n", "");
    add_drink("whiskey", "whiskey", "golden",
        100, 40, 170,
        "glass of whiskey", "glasses of whiskey",
        "The small glass contains a golden whiskey with a " +
        "strong, smooth aroma.\n", "");

    add_food("herring", "herring", "fried",
        50, 10,
        "fried herring", "fried herrings",
        "The small herring has been deboned and fried.\n", "");
    add_food(({"steak", "venison steak", "venison"}), "steak", "venison",
        250, 109,
        "venison steak", "venison steaks",
        "The venison steak, or deer steak, isn't very big, " +
        "but has been well cooked.\n", "");
    add_food("mutton", ({"mutton", "mutton shank"}), "",
        400, 271,
        "mutton shank", "mutton shanks",
        "The mutton shank has been slowly roasted over an open " +
        "fire.\n", "");
    add_food("haggis", "haggis", "",
        600, 605,
        "haggis", "haggis",
        "The haggis is a sheep's stomach, filled with various " +
        "meats and vegetables, then boiled for several hours.\n", "");
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

    add_exit(ROOM + "pub_kitchen", "east", VBFC_ME("kitchen_block"));
    add_exit(ROOM + "road_13_7", "northwest");
    add_exit(ROOM + "dining", "west");

    reset_room();
}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Welcome to The Wild Rover!"));
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
 
