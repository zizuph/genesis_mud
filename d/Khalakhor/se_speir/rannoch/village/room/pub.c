/* File         : /d/Khalakhor/se_speir/rannoch/village/room/pub.c
 * Creator      : Darragh@Genesis
 * Date         : 00-11-03      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Loosely based on Khail's Wild Rover pub
 * Modifications: 
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
        landlord = clone_object(NPC + "bathar");
        landlord->arm_me();
        landlord->move(TO);
        tell_room(TO, QCTNAME(landlord) + " limps in from " +
            "the kitchen.\n");
        landlord->set_pub(TO);
        landlord->set_kitchen(ROOM + "pub_kitchen.c");
        return;
    }
    else if (!present(landlord))
    {
        if (landlord->query_attack())
            return;
        else
        {
            tell_room(environment(landlord), QCTNAME(landlord)
              + "suddenly looks around with a start, and rushes "
              + "off somewhere.\n");
            landlord->move_living("M", TO);
            if (landlord->query_prop(LIVE_O_LAST_ROOM) == 
                find_object(ROOM + "pub_kitchen.c"))
                tell_room(TO, QCTNAME(landlord) + " arrives limping "
                  + "from the kitchen.\n");
            else
                tell_room(TO, QCTNAME(landlord) + " rushes in through "
                  + "the door.\n");
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
void
create_add_items()
{
    add_item(({"floor","ground","planks","wooden planks"}),
               "The floor is made of wooden planks covered with " 
             + "dust and dirt.\n");
    add_item(({"layer","hay","dirt","straw"}),
               "The dirt on the floor was brought in from outdoors "
             + "by the customers.\n");
    add_item(({"furniture","table","tables","chair","chairs",
               "stool","stools","bench","benches"}),
               "All the furniture of this pub are simple wooden "
             + "constructions, durable and cheap.\n");
    add_item(({"wall","walls","wooden wall","wooden walls"}),
               "The walls are wooden, as grey and dull as every " 
             + "building in this village. A wide assortment of " 
             + "decorations have been hung on the walls, mostly "
             + "old fishing equipment and trophies.\n");
    add_item(({"trophy","trophies","decoration","decorations",
               "equipment","old equipment","fishing equipment"}),  
               "Everything from old nets, oars, bottles, and "
             + "tattered maps to stuffed animals and the occasional "
             + "painting hang on the walls.\n");
    add_item(({"net","nets","old net","old nets"}),
               "The nets are old, or made to look old, stained and " 
             + "riddled with holes.\n");
    add_item(({"oar","oars"}),
               "A pair of very long oars hangs crossed above the "
             + "entrance. A smaller oar, in an extremely bad shape, "
             + "hangs above the bar.\n");
    add_item(({"small oar","smaller oar"}),
               "It is small, because its upper half is missing. By "
             + "the looks of it, it seems to have been bitten off, "
             + "and the rest has large dents and scratches.\n");
    add_item(({"bottle","bottles","old bottle","old bottles"}),
               "The bottles are old, and some are very dirty.\n");
    add_item(({"map","maps","tattered map","tattered maps"}),
               "Someone made a lot of effort when trying to create "
             + "atmosphere to this pub. The maps are obvious fakes, "
             + "showing things and places these people would never "
             + "even get close to.\n");
    add_item(({"animal","animals","stuffed animal","stuffed animals",
               "fishing trophy","fishing trophies","hunting trophy",
               "hunting trophies"}),
               "You see only a few land animals represented on the "
             + "walls, including a badger, deer, and boar heads. "
             + "However, this seems to be the place you go to when "
             + "you finally catch that huge fish. Mounted on wooden "
             + "plaques throughout the pub are impressive remains, "
             + "either stuffed or skeletal, of many creatures of "
             + "the lake.\n");
    add_item(({"plaque","plaques","wooden plaque","wooden plaques"}),
               "The plaques are made of dark wood, polished bright "
             + "and cut in various shapes. A few of them, carrying "
             + "the more impressive trophies, have a little metal "
             + "plate nailed to them.\n");
    add_item(({"plate","plates","metal plate","metal plates"}),
               "The metal plates bears the inscription of the name "
             + "of what person were responsible for catching the "
             + "animal mounted on the plaque.\n");
    add_item(({"painting","paintings","drawing","drawings",
               "charcoal drawing","charcoal drawings"}),
               "A few charcoal drawings have been framed and hung "
             + "upon the walls. Most of them depicts boats, birds, "
             + "and fish, but some show grand stone formations, "
             + "and strange patterns.\n");
    add_item(({"stone formation","stone formations","grand stone formation",
               "grand stone formations"}),
               "The drawings looks genuine, as if someone actually saw "
             + "these stone formations and drew them on paper.\n");
    add_item(({"pattern","patterns","strange pattern","strange patterns"}),
               "The patterns shown on the few drawings are quite "
             + "remarkable. The lines are so skillfully intervowen "
             + "and intricate that you have trouble following them. "
             + "You can not help but to wonder what inspired these.\n");
    add_item(({"roof","ceiling"}),
               "The ceiling of the pub is a simple thatch and wooden "
             + "rafter construction.\n");
    add_item(({"roof","roofs","thatch"}),
               "Made of thick reeds and straw along with bark and "
             + "grass the thatch looks strong enough to keep rain "
             + "out and warmth in.\n");
    add_item(({"rafter","rafters","wooden rafter","wooden rafters",
               "thick wooden rafter","thick wooden rafters"}),
               "The thatch of the roof is supported by a handful of "
             + "thick wooden rafters.\n");
    add_item(({"bar","wooden bar","polished wooden bar"}),
               "A long, polished wooden bar stands against the west "
             + "wall, behind from which the landlord serves his customers. "
             + "In the wall behind the bar is the opening to the kitchen.\n");
    add_item(({"kitchen","opening"}),
               "You don't see much from what lies within, but you can "
             + "hear and smell what goes on in there.\n");
    add_item(({"customer","customers","patron","patrons"}),
               "Scattered across the pub they sit or stand. Some are "
             + "sitting by the bar on their stools, talking to each "
             + "other over a mug of ale. You see only men in here, "
             + "perhaps due to the theme of the pub.\n");
    add_item("menu", &dummy_menu());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(ROOM + "pub_kitchen.c", "west", VBFC_ME("kitchen_block"));
    add_exit(ROOM + "pub_terrace.c", "south");
    add_exit(ROOM + "road_15_10.c", "out");
}
void
create_room_tells()
{
    add_tell(({"You hear the cries of birds from outside the terrace.\n",
               "You hear a yell from the north.\n",
               "One of the patrons by the bar snores loudly.\n",
               "You hear some noise from kitchen, followed by loud "
             + "curses.\n",
               "A man at a nearby table begins to sing a little song "
             + "about the joys of catching eels by hand in the dark, "
             + "and soon the whole pub joins in.\n",
               "A man by the bar belches very loudly, earning him a few "
             + "applauds from the patrons.\n",
               "A young man at a nearby table passes out.\n",
               "A good-looking woman enters from the kitchen, puts "
             + "a tray of clean mugs on the bar, and leaves west.\n",
               "You can feel the unmistakable smell of fried "
             + "fish coming from the kitchen.\n",
               "A man walks by with a mug in his hand, looking at the "
             + "things on the walls.\n", 
               "You can not help staring at all the things on the walls.\n",}));             
}
public void
create_khalakhor_room()
{
    set_short("The Walkway Pub");
    set_long("This is the Walkway Pub, a small but cheerful " 
           + "establishment in the southern end of the village. "
           + "In here you see a lot of fishing memorabilia on "
           + "the walls, along with a polished wooden bar by "
           + "the west wall with a menu on it, and a couple of "
           + "tables scattered across the room. Behind the bar "
           + "in the west wall is the entrance to the kitchen. "
           + "The room opens up to the south, into what makes "
           + "this pub worth the visit. A long terrace has been "
           + "built there, where there are more tables.\n");

    create_add_items();

    set_tell_time(400);
    create_room_tells();

    reset_room();

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
}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Welcome to The Walkway Pub!"));
}  

/*
 * Function name: init (MASK)
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
 
