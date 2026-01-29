/*
 * Road between Greenway and Sarn Ford
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
    set_short("A dirt road between Longbottom and Sarn Ford");
    set_long("You are walking along a wide, well-travelled dirt road near the " +
        "hobbit village of Longbottom, home of the Longbottom Leaf, a little " +
        "ways from Sarn Ford. While there is a lot of bushes in the " +
        "undergrowth around the trees here, you also notice that " +
        "the tall grassy fields here are interupted by the occasional " +
        "hobbit farm growing pipeweed. The constant buzzing of " +
        "insects, the many birds singing in the trees and even " +
        "the occasional animal stalking through the fields show " +
        "how active the local wildlife is. Down the road to the " +
        "west, this road continues into the heart of the Shire. " +
        "Somewhere to the east, is the Brandywine river and the " +
        "crossing known as Sarn Ford.\n");
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
        "If you continue west along this road, you will soon " +
        "reach the village of Longbottom in the heart of the South " +
        "Farthing.\n");
    add_item(({"farm", "hobbit farm", "south farthing", "pipeweed"}),
        "You must be close to the village of Longbottom in the " +
        "South Farthing of the Shire, as you can see the occasional " +
        "hobbit farm growing pipeweed.\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in ever-increasing abundance on either " +
        "side of the road, their wide fields stretching off into the " +
        "distant horizon. The fields are unbroken save for the "+
        "occasional grove of trees.\n");
    add_item(({"sarn ford", "sarn", "ford", "Sarn Ford", "stone", "stones"}),
        "Sarn Ford provides a crossing of the great Brandywine river, " +
        "primarily for merchants travelling between the Shire and " +
        "Gondor. It should not be far away from here.\n");
    add_item(({"river","brandywine", "baranduin"}),
        "Somewhere nearby, to the east, is the legendary Brandywine river, " +
        "otherwise known as the Baranduin River. If you follow the " +
        "road you are currently on, you should reach the crossing " +
        "known as Sarn Ford.\n");
    add_item(({"wildlife", "insects", "birds", "animals", "animal"}),
        "The fields around you are teeming with wildlife, most obviously " +
        "noticed from the constant buzzing of insects and the birds which " +
        "are swooping and diving all over. However, you will also notice " +
        "the occasional presence of some smaller animals too.\n");
    
    add_exit(SARNFORD_DIR + "wroad5.c", "east");
    add_exit(SARNFORD_DIR + "wroad7.c", "west");

    add_std_herbs("field", 10);
}
