/*
 * Trail to orc camp near Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Shire/lib/herbsearch";

void
create_room()
{
    set_short("A narrow trail in a grassy field");
    set_long("You are walking along a narrow trail which seems to " +
        "constantly wind its way back and forth as it skirts any " +
        "heavy clumps of underbrush. The occasional grove of trees " +
        "seems to pop up out of the fields here and there, breaking " +
        "up the endless field of tall grasses which sway with every " +
        "breeze that passes by. You notice a solitary, oddly-shaped " +
        "hill peeking up near the trail you are on, it seems to be " +
        "the only one of its kind here. Hundreds, if not thousands, of " +
        "insects seem to gather around you with every step you take, " +
        "buzzing and biting ceaselessly. Dozens of birds are calling " +
        "out to each other as they fly from one cluster of trees to " +
        "another. Somewhere to the north, is the original road you " +
        "were following, while the trail continues to penetrate the " +
        "fields to the south.\n");
    add_item(({"track", "road", "path", "dirt"}),
        "Somewhere to the north is the road you were following before " +
        "deciding to explore this trail.\n");
    add_item(({"bush", "bushes", "undergrowth", "underbrush"}),
        "There are many thick clumps of bushes and undergrowth which " +
        "have been scattered all across the fields. Thankfully, the " +
        "trail you are on goes out of its way to avoid them.\n");
    add_item(({"tree", "trees"}),
        "There are not too many trees here, as the landscape is mostly " +
        "open grass fields, however each small cluster of trees you spy " +
        "makes you wonder if there is an orc ambush waiting for you!\n");
    add_item(({"grass", "grasses", "field", "fields"}),
        "Tall, wild grasses grow in ever-increasing abundance on either " +
        "side of the road, their wide fields stretching off into the " +
        "distant horizon. The fields are unbroken save for the "+
        "occasional grove of trees and the narrow trail you are " +
        "currently following.\n");
    add_item(({"wildlife", "insects", "birds", "animals"}),
        "The fields around you are teeming with wildlife, most obviously " +
        "noticed from the constant buzzing of insects and the birds which " +
        "are swooping and diving all over. However, you will also notice " +
        "the occasional presence of some smaller animals too.\n");
    add_item(({"trail", "narrow trail"}),
        "The trail you are walking on has the unmistakable smell of orcs! " +
        "You strongly suspect that these orcs are bandits, waiting to " +
        "attack or ambush unwary travellers or merchants using the road.\n");
    add_item(({"hill", "odd hill", "shelter"}),
        "As you look closer, that odd hill is not a hill at all! It seems " +
        "to be a lookout shelter of some sort, perhaps for those orcs " +
        "you think are around here somewhere?\n");

    add_exit(SARNFORD_DIR + "orccamp/trail1", "north");
    add_exit(SARNFORD_DIR + "orccamp/track01", "southeast");

    add_std_herbs("field", 16);
}

void 
reset_room() 
{ 
    reset_shire_herbs(); 
}
