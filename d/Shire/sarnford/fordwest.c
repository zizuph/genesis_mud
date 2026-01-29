/*
 * Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Shire/lib/herbsearch";
inherit "/d/Gondor/common/lib/drink_water.c";

public void drink_message(string from);

void
create_room()

{
    set_short("The western edge of Sarn Ford at the Brandywine River");
    set_long("The turbulent rush of the mighty Brandywine river churns " +
        "at your feet immediately to the east. Stone pillars cautiously " +
  	    "poke out of the water in two parralel lines where they mark " +
  	    "the edges of several massive stone slabs which have been laid " +
  	    "down to create the Sarn Ford. A hard-packed, dirt road travels away " +
  	    "to the west, winding its way through grassy fields and into the " +
  	    "Shire, home of the hobbits. Tall, wild grasses dominate the " +
        "fields on either side of the river, and you can see the " +
        "road continue east, on the other side of the river, trailing " +
        "off into the distance.\n");
  
    add_item(({"ford", "sarn ford"}),
        "The road seems to plunge head-first, directly into the river, " +
        "with frequent stone pillars to mark the edges of the road. As " +
        "you take a closer look, you can see that many massive, granite " +
        "slabs have been laid flat upon the riverbed, between the " +
        "pillar rows. The slabs reach all the way across the widest " +
        "point in the river, to eventually meet up with the road on " +
        "the west bank in the far distance.\n\nYou also notice that " +
        "the ford appears to be remarkably well maintained, even if " +
        "there is no sign of any caretakers at this moment.");
    add_item(({"pillar", "pillars", "stone pillars", "stone", "stones"}),
        "Two long rows of tall stone pillars peek above the gentle waters " +
        "of the massive river. They follow the line of the road, obviously " +
        "making sure that any merchants using the ford do not accidently " +
        "slip off of the massive stone slabs which provide the easy " +
        "crossing.\n");
    add_item(({"slabs", "stone slabs"}),
        "There are many flat, stone slabs, just under the surface of the " +
        "water here, which have obviously been put in place to ensure " +
        "a safe and easy fording of the massive Brandywine river. There " +
        "are two rows of stone pillars which border the slabs, to make " +
        "certain that everyone knows where it is safe to travel.\n");
    add_item(({"river", "brandywine", "brandywine river", "baranduin"}),
        "This is the massive Brandywine river, otherwise known as " +
        "the Baranduin river, which would be completely unpassable " +
        "if not for this wide ford which has been constructed. The river " +
        "flows down from the north, and passing you, empties out to " +
        "the sea southwest from here. You can clearly see Sarn Ford " +
        "right in front of you.\n");
    add_item(({"road", "dirt road", "dirt"}),
        "The hard packed dirt beneath your feet has obviously been " +
        "worn down by the passing of countless wagons wheels, horses " +
        "and feet. Two wide, parralel ruts are dug in a little deeper, " +
        "indicating where the wagons commonly run. The road runs " +
        "directly into the Brandywine river here at Sarn Ford.\n");
    add_item(({"rut", "ruts"}),
        "These ruts are simply deep crevacies, dug into the road " +
        "by the countless wagon wheels of the merchants travelling " +
        "between Gondor and the Shire.\n");
    add_item(({"gondor", "shire", "rohan", "bree"}),
        "You can reach the Shire by travelling west along this very " +
        "road, while continuing east and then south will bring you " +
        "first to Rohan and then to Gondor. The town of Bree is " +
        "located east and north of here.\n");
    add_item(({"bush", "bushes", "undergrowth"}),
        "There are many thick clumps of bushes and undergrowth which " +
        "have been scattered in the fields both north and south of the " +
        "road you are on.\n");
    add_item(({"tree", "trees"}),
        "There are not too many trees here, as the landscape is mostly " +
        "open grass fields, however you can spy several clusters on " +
        "either side of the road quite frequently as you walk along.\n");
    add_item(({"greenway", "Greenway"}),
        "You cannot see the Greenway itself from here, it is somewhere " +
        "off in the distance of the eastern horizon. The Greenway is " +
        "the name of the road which runs south from Bree, turning into " +
        "the highway which runs to Rohan and Gondor.\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in ever-increasing abundance on either " +
        "side of the road, their wide fields stretching off into the " +
        "distant horizon. The fields are unbroken save for the "+
        "occasional grove of trees.\n");
    add_item(({"path", "narrow path"}),
        "There is a small, narrow path which follows the riverbank, " +
        "leading away from the road, travelling southwest towards a " +
        "modest looking dock with a tall building beside it.\n");

    add_exit(NS_RD_DIR + "rooms/road01.c", "west");
    add_exit(SARNFORD_DIR + "fordeast.c", "southeast", "@@cross_ford@@");

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_std_herbs("river", 6);
}

void
init()
{
::init();
init_drink();
}

public void
drink_message(string from)
{
write("You bend down and cup your hands to drink a mouthful of water from " +
    "the Brandywine river. It feels cool and refreshing going down your throat.\n");
say(QCTNAME(TP) + " bends down to drink some water from the Brandywine river.");
}

int
cross_ford()
{
    write("You cross Sarn Ford and enter the Southfarthing.\n\n");
    return 0;
}