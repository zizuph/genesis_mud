/*
 *  /w/serif/harondor/lib/std_funcs.c
 *
 *  Functions that contain base-room repeats for Harondor.
 *
 *  Serif 20 June 2001
 *  Tells inspired by Alto.
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define ROAD_HARONDOR "/w/serif/harondor"

/* These items are common to most rooms of Harondor. */

void
add_harondor_items()
{
    add_item(({"surroundings", "harondor"}), "The scrublands and "
	    + "savannahs of Harondor spread out around you, interrupted "
		+ "here by the Harad Road.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
		"Scrublands and savannahs spread out before you, filled with "
	    + "lush grass, dense bushes and occasional trees. To the east, "
		+ "the dark mountains rise out of the scrublands.\n");
    add_item(({"western horizon"}), "The scrublands stretch as far as "
	    + "the eye can see to the west.\n");
	add_item(({"plant", "plants", "bush", "bushes", "dense bushes", "thicket",
		"thickets", "thorn", "thorns", "vegetation"}), "Dense thickets of "
	    + "bushes and other plants rise above the grass, many of them armed "
		+ "with thorns.\n");
	add_item(({"grass", "tall grass", "lush grass", "tall lush grass"}), 
		"Tall, lush grass grows on either side of the road.\n");
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "east", "dark mountains", "dark peak", "dark peaks",
		"dark mountain"}), "The peaks of the Ephel Duath "
	    + "loom ominously several leagues to the east.\n");
	add_item(({"fly", "flies", "biting fly", "biting flies", "black fly",
		"black flies", "black biting fly", "black biting flies"}), "Numerous "
	    + "black flies buzz through the humid air.\n");
    add_item(({"air", "scent", "humid air", "humidity"}), "The air is "
	    + "warm and heavy with humidity and the scent of herbs and other "
		+ "plants.\n");
    add_item(({"insect", "insects"}), "Numerous insects fly through the "
	    + "air and hop across the vegetation around you.\n");
	add_item(({"bird", "birds", "songbird", "songbirds"}), "Now and then "
	    + "a bird flies overhead or calls out from the vegetation.\n");
    add_item(({"sky", "skies"}), "The sky is high above you.\n");
} 

/* These tells are common to most rooms of Harondor. */

void
add_harondor_tells()
{
    add_tell("A large bird soars by high overhead.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp somewhere nearby.\n");
    add_tell("The humidity begins to stifle you.\n");
    add_tell("Something stirs in the grass nearby.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("Several flies swarm around you.\n");
    add_tell("A black fly lands on you and bites you painfully before you "
	    + "can slap it away.\n");

}
