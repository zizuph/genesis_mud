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
    set_short("A dirt road near Longbottom in the South Farthing");
    set_long("You are walking along a wide, well-travelled dirt road which " +
        "travels around the hobbit village of Longbottom, home of the " +
        "Longbottom Leaf. The road also continues southeast towards Sarn " +
        "Ford, and out of the Shire. If you were to follow the road " +
        "northwest from here, you will find yourself quickly entering " +
        "the heart of the Shire. Almost everywhere you look, there " +
        "seems to be hobbit farms growing pipeweed. However, there are " +
        "still occasional fields of tall grass or clumps of bushes and " +
        "underbrush which gather around small groves of trees. You are " +
        "now standing in the heart of the South Farthing, deep withing " +
        "the Shire.\n");
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
        "You currently deep within the South Farthing in the Shire. " +
        "Far away lands such as Bree, or the even more distant Rohan " +
        "or Gondor can eventually be found by following the road southeast " +
        "from here.\n");
    add_item(({"bush", "bushes", "undergrowth"}),
        "There are a couple of  thick clumps of bushes and undergrowth which " +
        "have been scattered in the fields to the southwest of the " +
        "road you are on.\n");
    add_item(({"tree", "trees"}),
        "There are not too many trees here, as the landscape is mostly " +
        "farmer fields of pipeweed, however you can spy the occasional grove " +
        "on either side of the road as you walk along.\n");
    add_item(({"longbottom", "village", "valley"}),
        "You are currently on a road which overlooks the deep valley northeast " +
        "of you, where the village of Longbottom is situated. You can follow the " +
        "road in either direction to find a way there if you so desire.\n");
    add_item(({"farm", "hobbit farm", "south farthing", "pipeweed"}),
        "There are dozens of productive pipeweed farms scattered all around " +
        "you here in the South Farthing. It is probably to be expected, " +
        "Longbottom is world famous for the excellent pipeweed it produces.\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in the occasional open field here, but you " +
        "can see that most of the land is occupied by various hobbit farms.\n");
    add_item(({"sarn ford", "sarn", "ford", "Sarn Ford", "stone", "stones"}),
        "Sarn Ford provides a crossing of the great Brandywine river, " +
        "primarily for merchants travelling between the Shire and " +
        "Gondor. You can find it following the road southeast from here.\n");
    add_item(({"river","brandywine", "baranduin"}),
        "Somewhere far to the east, is the legendary Brandywine river, " +
        "otherwise known as the Baranduin River. If you follow the " +
        "road you are currently on, you should eventually reach the crossing " +
        "known as Sarn Ford.\n");
    add_item(({"wildlife", "insects", "birds", "animals", "animal"}),
        "The fields around you are teeming with wildlife, most obviously " +
        "noticed from the constant buzzing of insects and the birds which " +
        "are swooping and diving all over. However, you will also notice " +
        "the occasional presence of some smaller animals too.\n");
    
    add_exit(SARNFORD_DIR + "wroad10.c", "northwest");
    add_exit(SARNFORD_DIR + "wroad8.c", "southeast");

    add_std_herbs("field", 14);
}
