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
    set_short("A dirt road between Sarn Ford and the Greenway");
    set_long("You are walking along a weary dirt road, which perhaps " +
      	"might be more correctly deemed a track. On both the north and " +
      	"south sides of the road, dense bushes and thick undergrowth " +
      	"cluster around the occasional grove of trees which have been " +
      	"sprinkled liberally over the wild grasses. You can see all " +
      	"manner of wildlife thriving around you, from the swooping " +
      	"flights of birds across the fields, to the constant drone of " +
      	"buzzing insects which fills your ears. Down the road to the " +
      	"east, you can see a long, straight line of trees running off " +
      	"to the north, marking the Greenway. To the west, you know " +
      	"that Sarn Ford will cross the mighty Brandywine river before " +
      	"too much longer.\n");
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
        "either side of the road quite frequently as you walk along. " +
        "To the east, you can see a long, straight line of trees " +
        "stretching off to the north, marking the boundary of the " +
        "Greenway.\n");
    add_item(({"greenway", "Greenway"}),
        "You cannot see the Greenway itself from here, only the trees " +
        "which line the road, giving it the name. The Greenway is " +
        "the name of the road which runs south from Bree, turning into " +
        "the highway which runs to Rohan and Gondor.\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in ever-increasing abundance on either " +
        "side of the road, their wide fields stretching off into the " +
        "distant horizon. The fields are unbroken save for the "+
        "occasional grove of trees and a line of trees on the " +
        "eastern horizon.\n");
    add_item(({"sarn ford", "sarn", "ford", "Sarn Ford"}),
        "Sarn Ford provides a crossing of the great Brandywine river, " +
        "primarily for merchants travelling between the Shire and " +
        "Gondor. You know it lays somewhere west along this very road.\n");
    add_item(({"river", "brandywine"}),
        "You cannot see the Brandywine river from here, but it crosses " +
        "this road not far to the west.\n");
    add_item(({"wildlife", "insects", "birds", "animals"}),
        "The fields around you are teeming with wildlife, most obviously " +
        "noticed from the constant buzzing of insects and the birds which " +
        "are swooping and diving all over. However, you will also notice " +
        "the occasional presence of some smaller animals too.\n");

    add_exit("/d/Shire/common/gondorlink.c", "east");
    add_exit(SARNFORD_DIR + "eroad2.c", "west");

    add_std_herbs("field", 4);    
}
