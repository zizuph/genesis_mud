/*
 *  Basefile for Harondor add_items, tells, etc.
 *  Serif, July 2001 - April 2002.
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/harondor/lib/harondor_herbs.h"

/* Prototypes */

public string    sky_desc();

public int       add_bank_items();
public int       add_bank_tells();
public int       add_camp_items();
public int       add_camp_tells();
public int       add_cave_items();
public int       add_cave_tells();
public int       add_ford_items();
public int       add_ford_tells();
public int       add_harnen_items();
public int       add_harnen_tells();
public int       add_harondor_items();
public int       add_harondor_tells();
public int       add_hill_items();
public int       add_hill_tells();
public int       add_path_items();
public int       add_path_tells();
public int       add_road_items();
public int       add_road_tells();
public int       add_scrub_items();
public int       add_scrub_tells();
public int       add_sky_items();
//int              set_harondor_herbs();
//int              set_hill_herbs();
//int              set_path_herbs();
//int              set_scrub_herbs();

string           sky_text;
object           actor;

/* These items are common to the river path rooms of Harondor. */

public int       
add_bank_items()
{
	
    add_item(({"surroundings"}), "There is little to be seen here "
        + "except for the bushes which surround you.\n");
} 

/* These tells are common to the river path rooms of Harondor. */

public int       
add_bank_tells()
{
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp somewhere nearby.\n");
    add_tell("The humidity begins to stifle you.\n");
    add_tell("Something stirs in the bushes nearby.\n");
    add_tell("Chirping sounds come from nearby.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("Everything suddenly become very quiet.\n");
    add_tell("The trill of a songbird rings out from somewhere nearby.\n");
}

/* These items are common to the south road rooms of Harondor. */

public int       
add_camp_items()
{
    add_item(({"camp"}), "You are standing in the middle of a sizeable "
        + "camp. The ground is trampled and barren, and litter and other "
        + "refuse is everywhere.\n");
    add_item(({"material", "fabric"}), "The tents are made of heavy "
        + "fabric coloured black, with gold embroidery and red markings.\n");
    add_item(({"gold thread", "embroidery", "gold embroidery"}), "Gold "
        + "thread adorns much of the fabric of the tents.\n");
    add_item(({"markings", "red markings", "scene", "scenes"}), "Red "
        + "markings cover much of the tents. They depict scenes of "
        + "warriors riding huge oliphaunts into battle. Some of the "
        + "markings are more abstract, and have the vague shapes of spears "
        + "waves, eyes and other things not as recognisable.\n");
    add_item(({"ground"}), "The ground shows clear signs that many people "
        + "and animals have been here for a few days. The vegetation has "
        + "been trampled until nothing is left growing. Refuse is "
        + "everywhere, giving off an odor.\n");
    add_item(({"surroundings", "harondor"}), "The scrublands and "
        + "savannahs of Harondor spread out around you, interrupted "
        + "here by a large camp.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
        "Scrublands and savannahs spread out in the distance, filled with "
        + "lush grass, dense bushes and occasional trees. This part of "
        + "the scrublands has been trampled barren, however.\n");
    add_item(({"western horizon"}), "The scrublands stretch as far as "
	    + "the eye can see to the west.\n");
    add_item(({"plant", "plants", "bush", "bushes", "dense bushes", "thicket",
        "thickets", "thorn", "thorns", "vegetation"}), "Dense thickets of "
        + "bushes and other plants rise above the grass in the distance. "
        + "Nothing grows in the immediate vicinity, however, for the ground "
        + "has been trampled and polluted.\n");
    add_item(({"grass", "dead grass", "trampled grass", 
        "dead trampled grass"}), "There is only a little grass here, and "
        + "it is dead and and trampled.\n");
    add_item(({"fly", "flies", "biting fly", "biting flies", "black fly",
        "black flies", "black biting fly", "black biting flies"}), "Numerous "
        + "black flies buzz through the humid air.\n");
    add_item(({"air", "stench", "humid air", "humidity"}), "The air is "
        + "warm and heavy with humidity and the stench of trampled "
        + "ground, domestic animals and waste.\n");
    add_item(({"insect", "insects"}), "Numerous insects fly through the "
        + "air and hop across the vegetation around you.\n");
    add_item(({"sky", "skies"}), "The sky is high above you.\n");
    add_item(({"waste", "refuse", "litter"}), "Piles of waste are "
        + "strewn about the camp. They give off a stench.\n");
} 

/* These tells are common to the south road rooms of Harondor. */

public int       
add_camp_tells()
{
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp somewhere nearby.\n");
    add_tell("The humidity begins to stifle you.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("The scrublands suddenly become very quiet.\n");
    add_tell("The stench of refuse almost overpowers you.\n");
    add_tell("Flies buzz around the piles of refuse.\n");
    add_tell("The gleam of the gold thread on the tent catches your eye.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("Several flies swarm around you.\n");
    add_tell("You hear a loud trumpeting from somewhere nearby.\n");
    add_tell("A black fly lands on you and bites you painfully before you "
        + "can slap it away.\n");
}

/* These items are common to the south road rooms of Harondor. */

public int       
add_cave_items()
{
    add_item(({"ground"}), "The ground is made of the same stone "
        + "as the rest of the cave.\n");
    add_item(({"surroundings", "harondor"}), "The scrublands and "
        + "savannahs of Harondor spread out around you, interrupted "
        + "here by a large camp.\n");
    add_item(({"stone", "stones", "rock", "rocks", "wall", "walls"}),
        "Stone surrounds you on all sides, cool to the touch and slightly "
        + "moist.\n");
    add_item(({"air", "humid air", "humidity", "still air"}), "The air is "
        + "still and heavy with humidity.\n");
    add_item(({"sky", "skies"}), "You cannot see the sky from "
        + "inside the cave.\n");
    add_item(({"water", "drip", "drips"}), "Now and then, water drips "
        + "somewhere nearby.\n");
} 

/* These tells are common to the cave rooms of Harondor. */

public int       
add_cave_tells()
{
    add_tell("Echoes reverberate around you.\n");
    add_tell("Water drips somewhere nearby.\n");
    add_tell("The still air begins to stifle you.\n");
    add_tell("Echoes reverberate around you.\n");
    add_tell("Water drips somewhere nearby.\n");
    add_tell("The still air begins to stifle you.\n");
    add_tell("The sounds from your own movement echo around you.\n");
    add_tell("Water drips somewhere nearby.\n");
    add_tell("You think you can hear something moving somewhere "
        + "nearby.\n");
}

public int       
add_ford_items()
{
    add_item(({"ford", "fords", "river", "poros", "river poros"}),
        "The River Poros widens here, becoming shallow enough to cross "
        + "safely during most of the year. The ford continues to the "
        + "north and the south.\n");
    add_item(({"rock", "rocks", "riverbed", "slippery rock", 
        "slippery rocks"}), "The riverbed here is lined with slippery "
        + "rocks which shift underfoot and in the current, making "
        + "passage treacherous.\n");
    add_item(({"channel", "river channel"}), "The river channel widens "
        + "out here and the water is often shallow enough to cross. "
        + "The current is still strong though, and pushes against you "
        + "firmly.\n");
    add_item(({"current"}), "The current pushes at you relentlessly "
        + "as you stand in the middle of the river.\n");
    add_item(({"shore", "shores"}), "There are shores on the north and "
        + "south of the ford.\n");
    add_item(({"north shore", "north shores", "ithilien"}), "The land "
        + "of Ithilien lies to the north of the river, beginning at "
        + "the north shore of the ford.\n");
    add_item(({"south shore", "south shores", "southern shore", 
        "harondor"}), "The land of Harondor lies to the south of the "
        + "river, beginning at the south shore of the ford.\n");
    add_item(({"road", "harad road"}), "Across the river to the north, "
        + "the Harad Road continues through Ithilien. To the south, "
        + "the road crosses Harondor on its way toward Harad.\n");
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks"}), "The peaks of the Ephel Duath loom ominously "
        + "in the east.\n");
    add_item(({"plant", "plants", "bush", "bushes", "dense bushes", 
        "thicket", "thickets", "thorn", "thorns", "vegetation"}), "On "
        + "the shores, dense thickets of bushes and other plants crowd "
        + "along the river.\n");
    add_item(({"ripple", "ripples", "surface"}), "The surface of the "
        + "river constantly ripples and moves.\n");
    add_item(({"surroundings"}), "You are standing in the middle of "
        + "a ford in a wide, shallow river. The water courses around "
        + "you.\n");
    add_item(({"fly", "flies", "biting fly", "biting flies", "black fly",
        "black flies", "black biting fly", "black biting flies"}), "A few "
        + "black flies buzz through the humid air.\n");
    add_item(({"insect", "insects"}), "A few insects fly through the "
        + "air and over the water around you.\n");
    add_item(({"sky", "skies"}), "The sky is high above you.\n");
} 

/* These tells are common to the south road rooms of Harondor. */

public int       
add_ford_tells()
{
    add_tell("The river rushes around you.\n");
    add_tell("Something heavy splashes in the river.\n");
    add_tell("Something small splashes in the river.\n");
    add_tell("You feel more tired as the river pushes against you.\n");
    add_tell("The surface of the river ripples.\n");
    add_tell("You almost lose your footing as you stumble over a rock.\n");
    add_tell("Something quickly floats by but is gone before you can "
        + "examine it closer.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("A large black fly whizzes past your head.\n");
}

/* These items are common to the south road rooms of Harondor. */

public int       
add_harnen_items()
{
    add_item(({"harad", "shore", "opposite shore", "plains", "plain"}), 
        "The plains of Harad line the opposite shore of the river.\n");
    add_item(({"bird", "birds", "songbird", "songbirds"}), "Now and then "
        + "a bird flies overhead or calls out from the vegetation.\n");
    add_item(({"river", "harnen", "river harnen", "flow", "channel"}), 
        "Down the banks, the River Harnen flows through its channel "
        + "west toward the sea.\n");
    add_item(({"bank", "banks", "edge", "riverbank", "riverbanks", "mud",
        "willow", "willows", "tangle", "muddy riverbanks", "muddy bank",
        "muddy banks", "muddy riverbank"}), "The road winds along the "
        + "edge of the muddy riverbanks, which slope down steeply to the "
        + "river. Thick tangles of willows prevent easy access to the "
        + "water.\n");
    add_item(({"surroundings", "harondor"}), "The scrublands and savannahs "
        + "of Harondor spread out to the north. South of the road, "
        + "the River Harnen flows west towards the sea.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
        "Scrublands and savannahs spread out to the north, filled with "
        + "lush grass, dense bushes and occasional trees. To the east, "
        + "the dark mountains rise out of the scrublands.\n");
} 

/* These tells are common to the south road rooms of Harondor. */

public int       
add_harnen_tells()
{
    add_tell("A large bird soars by high overhead.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp somewhere nearby.\n");
    add_tell("The grass sways slightly in the humid air.\n");
    add_tell("The humidity begins to stifle you.\n");
    add_tell("Something stirs in the grass nearby.\n");
    add_tell("The scent of herbs fills the humid air.\n");
    add_tell("The river gurgles softly along its channel.\n");
    add_tell("You hear something rustle nearby.\n");
    add_tell("Chirping sounds come from the north.\n");
    add_tell("Something heavy splashes in the river.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("The scrublands suddenly become very quiet.\n");
    add_tell("A rodent scurries by and disappears into the grass.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("Several flies swarm around you.\n");
    add_tell("A black fly lands on you and bites you painfully before you "
        + "can slap it away.\n");
    add_tell("The trill of a songbird rings out from a nearby thicket.\n");
}

/* These items are common to most rooms of Harondor. */

public int       
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

public int       
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

/* These items are common to the hill rooms of Harondor. */

public int       
add_hill_items()
{
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "east", "dark mountains", "dark peak", "dark peaks",
		"dark mountain"}), "The peaks of the Ephel Duath "
	    + "loom ominously a few leagues to the northeast, dark and "
        + "forbidding.\n");
    add_item(({"hill", "hills", "foothill", "foothills"}), "The foothills "
        + "begin rising out of the scrublands here, giving way further "
        + "east to the bleak peaks of the Ephel Duath.\n");
    add_item(({"surroundings", "harondor"}), "The scrublands and "
	    + "savannahs of Harondor spread out to the west.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
		"Scrublands and savannahs spread out to the west and south, filled "
        + "with lush grass, dense bushes and occasional trees. To the "
        + "east, the dark mountains rise out of the scrublands.\n");
    add_item(({"western horizon"}), "The scrublands stretch as far as "
	    + "the eye can see to the west.\n");
	add_item(({"plant", "plants", "bush", "bushes", "dense bushes", 
        "thicket", "thickets", "thorn", "thorns", "vegetation"}), "Dense "
        + "thickets of bushes and other plants grow downhill in the "
        + "scrublands.\n");
	add_item(({"grass", "short grass", "tough grass", "short tough grass"}), 
		"Short, tough grass grows on the stoney ground.\n");
	add_item(({"fly", "flies", "biting fly", "biting flies", "black fly",
		"black flies", "black biting fly", "black biting flies"}), "A few "
	    + "black flies buzz through the humid air.\n");
    add_item(({"air", "scent", "humid air", "humidity"}), "The air is "
	    + "warm and heavy with humidity and the scent of stone and "
		+ "grass.\n");
    add_item(({"insect", "insects"}), "A few insects fly through the "
	    + "air and hop across the vegetation around you.\n");
    add_item(({"sky", "skies"}), "The sky is high above you.\n");
    add_item(({"ground", "stone", "stones"}), "The ground is hard and "
        + "stoney, but short tough grass manages to grow here. A few "
        + "herbs might even be able to grow here as well.\n");
} 

/* These tells are common to the river path rooms of Harondor. */

public int       
add_hill_tells()
{
    add_tell("Something small scurries over a rock and disappears from "
        + "sight.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp in the distance.\n");
    add_tell("Warm, humid air wafts up the hill from below.\n");
    add_tell("Something stirs in the grass nearby.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("Several flies swarm around you.\n");
    add_tell("Something flashes briefly on the scrublands below to the "
        + "west.\n");
    add_tell("A black fly lands on you and bites you painfully before you "
	    + "can slap it away.\n");
}

/* These items are common to the river path rooms of Harondor. */

public int       
add_path_items()
{
	
	add_item(({"ithilien", "shore", "opposite shore", "forest", "forests"}), 
		"The forests of Ithilien line the opposite shore of the river.\n");
	add_item(({"bird", "birds", "songbird", "songbirds"}), "Now and then "
	    + "a bird flies overhead or calls out from the vegetation.\n");
    add_item(({"river", "poros", "river poros", "flow", "channel"}), 
        "Down the banks, the River Poros flows through its channel "
	    + "west toward the sea.\n");
    add_item(({"bank", "banks", "edge", "riverbank", "riverbanks", "mud",
		"willow", "willows", "tangle", "muddy riverbanks", "muddy bank",
		"muddy banks", "muddy riverbank"}), "The path winds along the "
	    + "edge of the muddy riverbanks, which slope down steeply to the "
		+ "river. Thick tangles of willows prevent easy access to the "
		+ "water.\n");
	add_item(({"path", "trampled path"}), "A path has been trampled "
	    + "through the lush grass here, winding along the banks of the "
		+ "river.\n");
	add_item(({"grass", "tall grass", "lush grass", "tall lush grass"}), 
		"Tall, lush grass grows thickly in this area, but it has been "
	    + "trampled and flattened here into a sort of path.\n");
    add_item(({"surroundings", "harondor"}), "The scrublands and savannahs "
        + "of Harondor spread out to the south. North of the path, "
		+ "the River Poros flows west towards the sea.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
		"Scrublands and savannahs spread out before you, filled with "
	    + "lush grass, dense bushes and occasional trees. To the east, "
		+ "the dark mountains rise out of the scrublands.\n");
} 

/* These tells are common to the river path rooms of Harondor. */

public int       
add_path_tells()
{
    add_tell("A large bird soars by high overhead.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Crickets chirp somewhere nearby.\n");
    add_tell("The grass sways slightly in the humid air.\n");
    add_tell("The humidity begins to stifle you.\n");
    add_tell("Something stirs in the grass nearby.\n");
    add_tell("The scent of herbs fills the humid air.\n");
    add_tell("The river gurgles softly along its channel.\n");
    add_tell("You hear something moving ahead on the path.\n");
    add_tell("Chirping sounds come from the south.\n");
    add_tell("Something heavy splashes in the river.\n");
    add_tell("A large insect settles on you, then flies away.\n");
    add_tell("The scrublands suddenly become very quiet.\n");
    add_tell("A rodent scurries by and disappears into the grass.\n");
    add_tell("Something buzzes around your head.\n");
    add_tell("Several flies swarm around you.\n");
    add_tell("A black fly lands on you and bites you painfully before you "
	    + "can slap it away.\n");
    add_tell("The trill of a songbird rings out from a nearby thicket.\n");
}

/* These items are common to the eastern rooms of Harondor. */

public int       
add_road_items()
{
    add_item(({"road", "harad road", "outline", "route", "trade route",
        "ancient trade route", "ancient road", "ancient route", "ground",
        "stone", "stones", "worn stone", "worn stones"}), "The Harad Road, "
        + "the ancient trade route between Gondor and Harad, runs across "
        + "the scrublands and savannahs of Harondor, its many stones "
        + "worn with age and use.\n");
} 

/* These tells are common to the road rooms of Harondor. */

public int       
add_road_tells()
{
    add_tell("A large bird soars by high overhead.\n");
    add_tell("The grass sways slightly in the humid air.\n");
    add_tell("Chirping sounds come from the south.\n");
    add_tell("Chirping sounds come from the north.\n");
    add_tell("Chirping sounds come from the west.\n");
    add_tell("Chirping sounds come from the east.\n");
    add_tell("The scrublands suddenly become very quiet.\n");
    add_tell("A rodent scurries by and disappears into the grass.\n");
    add_tell("The trill of a songbird rings out from a nearby thicket.\n");
    add_tell("Something skitters across the road and disappears from "
        + "sight.\n");
}

/* These items are common to the river path rooms of Harondor. */

public int       
add_scrub_items()
{
    add_item(({"grass"}), "The grass is tall and lush here.\n");
}

/* These tells are common to the river path rooms of Harondor. */

public int       
add_scrub_tells()
{
    add_tell("Something rustles nearby in the grass.\n");
}

/* This describes the sky for Harondor, depending on the time. */

public string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        sky_text = " The stars twinkle softly as they shine "
          + "faintly over the scrublands of Harondor";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale brightness of the full "
                + "moon."; 
            break;
        case "waxing crescent":
            sky_text += " as the crescent moon begins to rise.";
            break;
        case "waxing gibbous":
		    sky_text += " as the nearly full moon rises over the "
                + "mountains."; 
		    break;
        case "waning gibbous":
		    sky_text += ". The moon, slightly past full, casts a pale "
                + "glow over the area."; 
		    break;
        case "waning crescent":
            sky_text += ", as the moon tilts its sharp horns over the dark "
                + "landscape."; 
            break;
        default:
		          sky_text += ", but the moon cannot be seen.";
            break;
        }
        break;
    case "afternoon":
        sky_text = " The afternoon sun glares down harshly upon the landscape.";
        break;
    case "morning":
        sky_text = " The morning sun is riding low in the eastern horizon.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead.";
        break;
    case "evening":
        sky_text = " The sun is sinking into the western horizon, "
          + "bathing the area in deep orange light.";
        break;
    case "early morning":
        sky_text = " The first rays of the sun are peeking over the eastern "
          + "horizon.";
        break;
    default:
		sky_text = " The sky is obscured by gathering clouds.";
        break;
    }
    return (sky_text);
}

/* This adds the sky items for Harondor, depending on the time. */

public int
add_sky_items()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":
 
        add_item(({"star", "stars"}), "The stars twinkle faintly in the deep "
            + "night sky.\n");
        add_item(({"sky", "night sky"}), "The night sky is illuminated "
            + "faintly by the twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon shines "
                + "down from the night sky, its face slightly pale "
                + "and slightly golden.\n"); 
            break;
        case "waxing gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has almost "
                + "reached its full phase and will likely peak within a "
                + "few days.\n"); 
		          break;
        case "waning gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has passed "
                + "its full phase and grows increasingly less illuminating "
                + "with the passing of days.\n"); 
		          break;
        case "waxing crescent":
        case "waning crescent":
            add_item(({"moon", "crescent moon"}), "The crescent moon hangs "
                + "low upon the horizon, its sharp ends dangling with the "
                + "tilt of its axis.\n");
            add_item(({"end", "ends"}), "The ends of the moon dangle "
                + "with the tilt of its axis.\n");
            break;
        default:
            break;
        }
        break;
    case "afternoon":
        add_item(({"sky", "afternoon sky"}), "The afternoon sky is lit "
            + "by the glaring light of the sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun glares "
            + "down harshly upon the landscape.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit "
            + "by the growing light of the sun.\n");
        add_item(({"sun", "morning sun", "horizon", "eastern horizon"}), 
            "The morning sun rides low in the eastern horizon.\n");
        break;
    case "noon":
        add_item(({"sky", "noon sky"}), "The noon sky is illuminated by "
            + "the pounding light of the sun directly overhead.\n");
        add_item(({"sun", "noon sun"}), "The noon sun is directly overhead.\n");
        break;
    case "evening":
        add_item(({"sky", "evening sky"}), "The evening sky is lit "
            + "by the fading light of the sinking sun.\n");
        add_item(({"sun", "evening sun", "horizon", "western horizon"}), 
            "The evening sun is sinking behind "
            + "the mountains in the west.\n");
        break;
    case "early morning":
        add_item(({"sky", "early morning sky"}), "The morning sky is lit "
            + "by the first rays of the rising sun.\n");
        add_item(({"sun", "early morning sun", "morning sun", "horizon",
            "eastern horizon", "rays", "ray"}), "The early morning sun "
            + "is just peeking over the eastern horizon.\n");
        break;
    default:
        add_item(({"sky", "clouds", "gathering clouds"}), "The sky is "
            + "obscured by gathering clouds.\n");
        break;
    }
    return 1;
}

/* Set up the general herbs for Harondor. 

int
set_harondor_herbs()
{
    switch(random(100))
    {
    case 0..69:
        set_up_herbs( ({ ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS), 
            ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS) }),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            4 );
    break;
    case 70..75:
        set_up_herbs( ({ HERB_DIR + "suranie", 
            HERB_DIR + "attanar", HERB_DIR + "lissuin",
            HERB_DIR + "redweed", HERB_DIR + "lothore",
            HERB_DIR + "seregon", HERB_DIR + "morgurth"}),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            2 );
    case 76..99:
    default:
    break;
    }
    return 1;
}
*/
/* Set up the hill herbs for Harondor. 

int
set_hill_herbs()
{
    switch(random(8))
    {
    case 0..3:
    set_up_herbs( ({ HERB_DIR + "thyme", HERB_DIR + "sage", }),
		  ({ "ground", "plants", "scrub", "grass", "stone", "stones",
              "rock", "rocks"}), 5);
    break;
    case 4..5:
    set_up_herbs( ({ HERB_DIR + "tuo" }),
		  ({ "ground", "plants", "scrub", "grass", "stone", "stones",
              "rock", "rocks"}), 5);
    break;
    case 6..7:
    default:
    break;
    }
    return 1;
}
*/
/* Set up the path herbs for Harondor. 

int
set_path_herbs()
{
    switch(random(100))
    {
    case 0..69:
        set_up_herbs( ({ ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS), 
            ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS) }),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            4 );
    break;
    case 70..75:
        set_up_herbs( ({ HERB_DIR + "curugwath", HERB_DIR + "suranie", 
            HERB_DIR + "attanar", HERB_DIR + "lissuin",
            HERB_DIR + "redweed", HERB_DIR + "lothore",
            HERB_DIR + "seregon", HERB_DIR + "morgurth"}),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            2 );
    case 76..99:
    default:
    break;
    }
    return 1;
}
*/
/* Set up the scrub herbs for Harondor. 

int
set_scrub_herbs()
{
    switch(random(100))
    {
    case 0..69:
        set_up_herbs( ({ ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS), 
            ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS) }),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            4 );
    break;
    case 70..75:
        set_up_herbs( ({ HERB_DIR + "suranie", 
            HERB_DIR + "attanar", HERB_DIR + "lissuin",
            HERB_DIR + "redweed", HERB_DIR + "lothore",
            HERB_DIR + "seregon", HERB_DIR + "morgurth"}),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "thickets", "riverbank", "riverbanks", "thicket", 
            "plants" }),
            2 );
    case 76..99:
    default:
    break;
    }
    return 1;
}
*/