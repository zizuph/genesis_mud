/*
 * Road between Greenway and Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Shire/lib/herbsearch";
inherit "/d/Gondor/common/lib/drink_water.c";

int do_pry(string str);
public void drink_message(string from);

void

create_room()

{
    set_short("A dirt road between Longbottom and Sarn Ford");
    set_long("You are walking along a wide, well-travelled dirt road between " +
        "hobbit village of Longbottom, home of the Longbottom Leaf, and " +
        "Sarn Ford. Dense, green bushes mingle with the thick undergrowth " +
  	    "here. You can see the occcasional cluster of trees, " +
  	    "sprinkled liberally over the wild, grassy fields found on both " +
        "the north and south sides of the road. The constant buzzing of " +
        "insects, the many birds singing in the trees and even " +
        "the occasional animal stalking through the fields show " +
        "how active the local wildlife is. Down the road to the " +
  	    "west, this road continues into the heart of the Shire. " +
        "Somewhere to the east, is the Brandywine river and the " +
        "crossing known as Sarn Ford. A grey, stone bridge crosses " +
        "over a small river which crosses the road here.\n");
    add_item(({"track", "road", "path", "dirt"}),
        "The hard packed dirt beneath your feet has obviously been " +
        "worn down by the passing of countless wagons wheels, horses " +
        "and feet. Two wide, parralel ruts are dug in a little deeper, " +
        "indicating where the wagons commonly run. \n");
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
    add_item(({"longbottom", "village"}),
        "If you continue west along this road, you will eventually " +
        "reach the village of Longbottom and the land known as the " +
        "Shire, home of the hobbits.\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in ever-increasing abundance on either " +
        "side of the road, their wide fields stretching off into the " +
        "distant horizon. The fields are unbroken save for the "+
        "occasional grove of trees.\n");
    add_item(({"sarn ford", "sarn", "ford", "Sarn Ford", "stone", "stones"}),
        "Sarn Ford provides a crossing of the great Brandywine river, " +
        "primarily for merchants travelling between the Shire and " +
        "Gondor. It should not be far away from here.\n");
    add_item(({"brandywine", "baranduin"}),
        "Somewhere nearby, to the east, is the legendary Brandywine river, " +
        "otherwise known as the Baranduin River. If you follow the " +
        "road you are currently on, you should reach the crossing " +
        "known as Sarn Ford.\n");
    add_item(({"river", "small river"}),
        "This is a small river, yet still strong enough to require a " +
        "bridge to cross over it. Given your knowledge of the area, " +
        "you suspect it join the Brandywine not far south of here.\n");
    add_item(({"bridge", "stone bridge"}),
        "There is a grey bridge here, constructed from field stones, " +
        "which crosses over the small, fast river which rushes " +
        "away from you to the south. It looks quite sturdy and " +
        "well maintained.\n");
    add_item(({"stone", "stones", "fieldstone", "fieldstones"}),
        "There are hundreds of fieldstones which have been used in the " +
        "construction of the bridge which crosses the river in " +
        "front of you. The stones are quite strong and in good " +
        "condition, having been well set in mortar.\n");
    add_item(({"mortar", "cement"}),
        "The bridge which crosses the river here has been crafted from " +
        "fieldstones sent into a cement mortar. It looks as if this " +
        "bridge is kept in excellent repair as the mortar has been " +
        "patched to ensure there are no cracks or fissures.\n");
    add_item(({"cracks", "fissures"}),
        "Search as you will, you cannot find any cracks or fissures " +
        "anywhere in the mortar which holds this bridge together. If " +
        "any of them ever existed, they have obviously been patched " +
        "by someone who wants to ensure this bridge is kept in good " +
        "repair.\n");
    add_item(({"patch", "patches"}),
        "Some of these patches are newer, some older, but all of them " +
        "solid and keeping the bridge in excellent condition.\n");
    add_item(({"old patch", "old patches"}),
        "Some of these patches are newer, some older, but all of them " +
        "solid and keeping the bridge in excellent condition.\n");
    add_item(({"new patch", "new patch"}),
        "Some of these patches are newer, some older, but all of them " +
        "solid and keeping the bridge in excellent condition.\n\nHold on " +
        "a second! It looks like one of the newer patches was not done " +
        "very well! You think you could probably pry it apart.\n");
    add_item(({"wildlife", "insects", "birds", "animals", "animal"}),
        "The fields around you are teeming with wildlife, most obviously " +
        "noticed from the constant buzzing of insects and the birds which " +
        "are swooping and diving all over. However, you will also notice " +
        "the occasional presence of some smaller animals too.\n");
    
    add_exit(SARNFORD_DIR + "wroad1.c", "east");
    add_exit(SARNFORD_DIR + "wroad3.c", "west");

    set_drink_from( ({ "river", "brandywine", "baranduin", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_std_herbs("river", 3);
}

void
init()
{
::init();
add_action("do_pry","pry");
init_drink();
}
int
do_pry(string str)
{
if(!str)
{
write("Pry what?\n");
return 1;
}
if((str != "patch") && (str != "new patch") && (str != "apart new patch") && (str != "apart patch") && (str != "new patches") && (str != "apart new patches") && (str != "apart patches") && (str != "patches"))
{ write("Pry what?\n");
return 1;
}
write("You pry apart some of the loose mortar and notice it was concealing " +
    "a hidden door! You quickly slip inside.\n");
SAYBB(" disappears under the bridge.");
TP->move_living("M","/d/Shire/sarnford/secret1.c",1,0);
SAYBB(" arrives climbing from underneath the bridge.");
return 1;
}

public void
drink_message(string from)
{
write("You bend down and cup your hands to drink a mouthful of water from " +
    "the river. It feels cool and refreshing going down your throat.\n");
say(QCTNAME(TP) + " bends down to drink some water from the river.");
}