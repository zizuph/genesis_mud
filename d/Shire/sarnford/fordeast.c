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

void
create_room()

{
    set_short("The eastern edge of Sarn Ford at the Brandywine River");
    set_long("You are standing beside the wide, flowing waters of the " +
  	    "great Brandywine river. Several stone pillars peek out above " +
  	    "the water, running in two parralel lines where the road meets the " +
  	    "river, marking the edges of the massive stone slabs which " +
  	    "have created Sarn Ford. A hard-packed, dirt road travels away " +
  	    "to the east, winding its way through grassy fields towards the " +
  	    "highway known as the Greenway. A narrow path follows the river " +
  	    "to the southwest here, leading towards a tall building which " +
  	    "has been constructed by a modest looking dock. Aside from the " +
  	    "occasional cluster of trees or bushes, the land here appears " +
  	    "rather vacant.\n");
  
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
    add_item(({"river", "brandywine", "brandywine river"}),
        "This is the massive Brandywine river, which would be unpassable " +
        "if not for this wide ford which has been constructed. The river " +
        "flows down from the north, and passing you, empties out to " +
        "the sea southwest from here. You can clearly see Sarn Ford " +
        "right in front of you, and a small dock to the southwest.\n");
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
    add_item(({"building", "tall building"}),
        "You cannot see much from here, but there is a tall building " +
        "sitting alongside the river beisde a modest looking dock.\n");
    add_item(({"dock", "modest dock"}),
        "You are a little too far away to see any details, but the " +
        "narrow path southwest from here seems to lead towards a modest " +
        "looking dock with a tall building beside it.\n");
    add_item(({"path", "narrow path"}),
        "There is a small, narrow path which follows the riverbank, " +
        "leading away from the road, travelling southwest towards a " +
        "modest looking dock with a tall building beside it.\n");

    add_exit(SARNFORD_DIR + "eroad4.c", "east", "@@cross_ford@@");
    add_exit(SARNFORD_DIR + "dock.c", "southwest");
    add_exit(SARNFORD_DIR + "fordwest.c", "northwest");

    add_std_herbs("river", 6);
}

int
not_open()
{

    if (this_player()->query_wiz_level()) return 0;

    write("As you approach the ford, you notice that abnormally " +
	"high waters from recent flooding make the ford too " +
	"dangerous to cross right now.\n");
    return 1;
}

int
cross_ford()
{
    write("You cross Sarn Ford and leave the Southfarthing.\n\n");
    return 0;
}