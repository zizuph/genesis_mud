/*
 * File of common routines for all of Bree
 *
 * 2005/11/02 Last update
 * 2011/07/21 Lavellan - Don't use add_my_desc! This means the added text is
 *                       only present during lifetime of cloning object.
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
//inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit "/d/Shire/eastroad/std/treetop";

static string add_houses        = "",
              add_hobbit_holes  = "",
              add_gate          = "",
              add_outside_hedge = "",
              add_bushes        = "",
              add_inside_hedge  = "",
              add_dike          = "", 
              add_outside_smiths= "",
              add_claw_prints   = "", 
              add_hill          = "",
              add_on_hill       = "",
              add_hilltop       = "",
              add_trees         = "",
              add_ger           = "",
              add_orchard       = "",
              add_nroad         = "",
              add_hedge_road    = "",
              add_sky           = "";


void add_bree_desc(string desc);

/*
 * Function name : set_add_houses
 * Description   : adds standard house descriptions to rooms
 */

void set_add_houses()
{
    add_item(({"house", "houses"}),
        "The houses line the street. belonging to the humans that " +
        "live in Bree. They are all sizes, with fewer gardens than " +
        "those outside hobbit holes. Some are in good repair while " +
        "others look like " +
        "they will fall down anytime. The roofs are pointed or flat, " +
        "depending on the house. They all have windows with shutters " +
        "on both sides. Some are opened.\n");
    add_item(({"window", "windows"}),
        "The windows are made of glass and divided into " +
        "quarters. On either side of the windows are large shutters.\n"); 
    add_item(({"shutters", "large shutters", "open shutters",
            "large open shutters"}),
        "The shutters are wooden and are attached to either " +
        "side of the windows. They are large and during times " +
        "of bad weather, are closed to protect the windows.\n");
    add_item(({"gardens", "garden", "flower beds", "flower gardens", 
            "flower bed", "flower garden"}),
        "The gardens are small and grow alongside of the house. " +
        "Bright flowers grow alongside the house with a green lawn " +
        "extending out to the road.\n");
    add_item(({"flowers", "bright flowers", "flower", "bright flower"}),
        "The flowers grow alongside the house and are arranged in neat, " +
        "tidy rows. Tall flowers grow closest to the house and are " +
        "bordered with medium to small flowers. They are beautiful " +
        "and are a tapestry of color.\n");
    add_item(({"lawn", "grass"}),
        "The lawns are neatly clipped and a deep, velvet green. " +
        "They make up the majority of the human gardens and extend " +
        "from the edge of the flower gardens to the the street.\n");
    add_item(({"buildings", "building"}),
        "Buildings line the road. They are made from " +
        "of wood planks and stone. The buildings seem sturdy and " +
        "well crafted.\n");
    add_item(({"house", "houses"}),
        "There are some houses scattered about. They are sturdy " +
        "wooden structures.\n");
    add_item(({"roofs", "roof"}),
        "The roofs of the buildings are mostly peaked and made " +
        "of wood or stone shingles.\n");
    add_item("eaves",
        "The eaves extend from the roof by about an arm's length, " +
        "providing protection to anyone standing beneath them.\n");
    add_item(({"shingles"}),
        "The shingles cover the roof in an overlapping pattern, " +
        "The roofs are covered with wood shingles.\n"); 
    add_item(({"wood shingles", "wood shingle"}),
        "The shingles are made from rough cut lumber and are " +
        "attached to the roofs.\n");
    add_item(({"chimney", "chimnies"}),
        "The chimnies are made from stone and concrete. They " +
        "run up the side of some buildings. They are very wide " +
        "at the base and then become narrow about two thirds of " +
        "the way up the buildings.\n");
}

string daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Gentle sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Blazing afternoon sunlight";
        case EVENING:
            return "Evening light";
    }
}

 
string
day_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}
 
string
light_type()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle night light";
    }
}
public string
long_desc()
{
    string time;
    string desc;
    
    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
	desc += (extraline);
    if (functionp(vbfc_extra))
	desc += vbfc_extra();
    return (desc);
}

void set_add_trees()
{

    add_item(({"coniferous trees", "evergreen trees", "evergreens"}),
        "They are pyramidal shaped trees that are rather tall. The " +
        "trees are healthy and about the same height as the " +
        "deciduous trees.\n");
    add_item(({"deciduous trees"}),
        "The deciduous trees are the prominent trees growing on " +
        "the hill. They aren't numerous, but grow in small clusters " +
        "scattered about.\n");
}

/*
 * Function name : set_add_hobbit_holes
 * Description   : adds standard arch descriptions to rooms
 */

void set_add_hobbit_holes()
{
    add_item(({"hobbit hole", "hobbit holes", "smials", "smial"}),
        "The hobbit holes are dug into the hill. Round doors " +
        "mark their entrances and round windows line the side " +
        "of the hills. Large gardens surround the hobbit holes.\n");
    add_item(({"round doors", "round door"}),
        "The round doors are painted bright colors, green being " +
        "the predominate color. They are set into the hillside and " +
        "mark the entrances to hobbit holes.\n");
    add_item(({"round windows", "round window"}),
        "The round windows are made of glass and vary in size. " +
        "They are lined up horizontally on the hillside, allowing " +
        "light into the hobbit holes. Gardens grow outside the " +
        "windows.\n");
    add_item(({"gardens", "garden", "flower beds", "flower gardens", 
            "flower bed", "flower garden"}),
        "The gardens surround the hobbit holes. They are full of " +
        "bright flowers and look well tended.\n");
    add_item(({"bright flowers", "bright flower", "flowers", "flower"}),
        "The bright flowers grow in the garden and are well tended. " +
        "They are of different heights and types. They grow in " +
        "bunches and in rows throughout the gardens, depending on " +
        "the style of the garden.\n");
    add_item(({"buildings", "building"}),
        "There are very few, if any buildings here in this part " +
        "of Bree. What few are here are small and made of stone " +
        "and wood, and cared for by the hobbits.\n");
}

/*
 * Function name : set_add_outside_hedge
 * Description   : adds hedge descr outside the gate
 */

void set_add_outside_hedge()
{
    add_item(({"hedge"}),
        "The hedge grows around the outside of the town. It is " +
        "very thick and resembles a wall. It offers a measure of " +
        "protection, increased by a deep dike that has been dug " +
        "to the left of the hedge.\n");
    add_item("branches",
        "The branches are varied in size based on the tree growing " +
        "in the hedge. Some are long and thin while others are " +
        "short and thick. They are healthy looking.\n");
}

/*
 * Function name : set_add_bushes
 * Description   : adds bushes descr outside the gate
 */

void set_add_bushes()
{

    add_item(({"shrubs", "trees", "bushes"}),
        "They grow thick together, making up the hedge that " +
        "surrounds the town.\n");

}

/*
 * Function name : set_add_inside_hedge
 * Description   : adds hedge descr inside the town
 */

void set_add_inside_hedge()
{
    add_item(({"hedge"}),
        "The hedge grows along the outside of the town. It acts " +
        "as a barrier to protect the inhabitants of the town, " +
        "keeping ruffians and other undesirables out.\n");
}


/*
 * Function name : set_add_dike
 * Description   : adds dike descr outside the gate
 */

void set_add_dike()
{
    add_item(({"dike", "trench"}),
        "The dike is a very wide, deep trench that looks like it " +
        "was dug ages ago. Nonetheless, it is kept in good repair " +
        "and surrounds the town. It is outside the hedge and offers " +
        "another defense in protecting Bree.\n");
}


/*
 * Function name : set_add_outside_smiths
 * Description   : adds outside of smiths guild along the road.
 */

void set_add_outside_smiths()
{
    add_item(({"wall", "stone wall"}),
        "The stone wall is tall, blocking your view of what is on " +
        "the other side. It is constructed of gray stone blocks. " +
        "Beyond the wall, two tall buildings rise above it.\n");
    add_item(({"stone blocks", "gray stone blocks", "blocks", "block", 
            "stone block", "gray stone block"}),
        "The stone blocks are fitted neatly together, making the " +
        "wall secure. They are smooth, apparently handled by a skilled " + 
        "stonemason.\n");
    add_item(({"tall buildings", "two tall buildings"}),
        "The two tall buildings are expertly crafted. They are " +
        "easily the tallest buildings in Bree, probably belonging " +
        "to someone of great prestige in Bree.\n");
}

/*
 * Function name : set_add_claw_prints
 * Description   : adds claw prints from orcs and such on the ground.
 */

void set_add_claw_prints()
{
    add_item(({"prints", "claw prints"}),
        "The prints look like they are from wild animals that " +
        "passed by here. They look like there are claws attached " +
        "to the feet. Perhaps they were only from some wild animals, " +
        "or maybe worse.\n");
}

/*
 * Function name : set_add_hill
 * Description   : adds hill description
 */

void set_add_hill()
{
    add_item(({"hill", "hillside"}),
        "The hill gently rises above you to the east. It is grass " +
        "covered with a road that winds its way across it to the " +
        "top. Its base is broad at the bottom here, rising to a " +
        "dome-like shape at the top.\n");
    add_item(({"trees"}),
        "They grow alongside the road and in the gardens. The " +
        "trees are large and ancient looking. Most are deciduous " +
        "with some evergreens growing among them.\n");
    add_room_tell("Some travellers pass by.");
    add_room_tell("A friendly hobbit smiles and passes by.");

    set_add_trees();
}

/*
 * Function name : set_add_hill
 * Description   : adds hill description
 */

void set_add_on_hill()
{
    add_item(({"hill", "hillside"}),
        "The hill rises before you and slopes down to the road " +
        "below. It is covered with grass and dotted with hobbit " +
        "holes that are dug into its side. Gardens surround the " +
        "holes. The road winds across the hill lazily.\n");
    add_item(({"trees"}),
        "Some trees dot the the hill, growing in small groups. The " +
        "trees are large, deciduous types with some evergreens " +
        "growing among them.\n");
    set_add_trees();

    add_room_tell("A hobbit passes by you.");

}

/*
 * Function name : set_add_hilltop
 * Description   : adds hill description
 */

void set_add_hilltop()
{
    add_item(({"hill", "hillside"}),
        "The top of the hill flattens out as it spreads out to " +
        "the east. Trees dot the edge of the hill, which mark the " +
        "border of Bree. The track continues in a general east " +
        "direction until it's lost in the trees, and runs back " +
        "down the hill.\n");
    add_item(({"forest"}),
        "The forest grows beyond the eastern edge of the hill. It " +
        "looks thick and seems to spread to the east, filling your " +
        "view of that area with a carpet of green.\n");
    add_item(({"meadow", "field"}),
        "It covers the hilltop and is a blanket of green grass. " +
        "Lovely wildflowers grow scattered across the hilltop.\n");
    add_item(({"flowers", "wildflowers"}),
        "The wild flowers are all sizes and shapes. They grow " +
        "scattered across the meadow like dots of red, blue, orange, " +
        "yellow and other beautiful colors.\n");
    add_item(({"track", "path"}),
        "The track runs in a general northeast direction across " +
        "the meadow. It is nothing more than a path thru the meadow, " +
        "heading to the trees.\n");
    add_item(({"grasses", "grass", "green grass", "tall grass", 
            "tall green grass"}),
        "The grasses are tall and green. They cover the hilltop, " +
        "punctuated with some wildflowers and an occasional tree " +
        "growing. The track cuts through the grass as it wanders " +
        "across the hilltop.\n");
    add_item(({"trees", "tree"}),
        "They are tall and majestic looking. They grow scattered " +
        "about the hilltop, like silent sentinals on top of the hill.\n");
    add_room_tell("Wildflowers move gently in the breeze.");
    add_room_tell("Something rustles in the grass.");
    add_room_tell("The breeze blows across the meadow.");

set_add_trees();
}

/*
 * Function name : set_add_ger
 * Description   : adds great east road descr
 */
void set_add_ger()
{
    add_item(({"great east road", "east west road", "great road", 
            "east road", "old road"}),
        "The Great East Road is an ancient road that runs through " +
        "Eriador. Legends speak that it was once a great highway " +
        "trodden by the First-born in ages long forgotten. Now it " +
        "is little more than a dusty road that seems to run east " +
        "and west forever.\n");
}

/*
 * Function name : set_add_orchard
 * Description   : adds orchard descriptions to room
 */
void set_add_orchard()
{

    set_areadesc("small");
    set_area("path in");
    set_areaname("the orchard");
    set_land("Bree");

    add_bree_desc("The sweet smell of apple blossom hangs lazily in " +
        "the air. The apple trees stand in perfect rows, all full " +
        "of sweet, ripe fruit. A path wanders among the apple trees. ");

    add_item(({"apple","apples", "fruit"}),
        "The apples are large, red, and juicy. They hang from the " +
        "branches like ruby jewels, ready to be picked and enjoyed.\n");
    add_item(({"blossom","apple blossom"}),
        "The apple blossoms are soft and pink. Many hang from the " +
        "branches while a carpet of blossoms lay on the ground.\n");
    add_item(({"apple tree", "apple trees", "trees", "fruit trees"}),
        "The are tall and old looking. They are lined up in neat " +
        "rows. Many large, juicy apples hang from the branches. Some " +
        "are even low enough to be picked easily.\n");
    add_item(({"path"}),
        "The path wanders down the rows of apple trees. It is " +
        "nothing more then a track of trampled grass from the many " +
        "people who come and pick the apples.\n");
    add_item(({"road"}),
        "The road can barely be seen from here, but what is " +
        "visible is that it is a dirt path that wanders throughout " +
        "Bree, and up the Hill.\n");
    add_item(({"grass"}),
        "The grass is velvet green and ankle high. It grows under " +
        "the trees, providing a carpet of green. Much of it is trampled " +
        "by many feet that come here. There are indentations in the " +
        "grass where apples have fallen to the ground.\n");
    add_room_tell("Sweet apples swing from the branches.");
    add_room_tell("Large bumblebees dance from blossom to blossom.");
    add_room_tell("A hummingbird darts from flower to flower.");


}

/*
 * Function name : set_add_nroad
 * Description   : adds descr of north road
 */
void set_add_nroad()
{
    set_long("@@long_desc@@");

    add_item(({"weeds"}),
        "They grow on the road and are generally low growing. " +
        "Some have thorns or are ratty looking.\n");
    add_item(({"road", "highway"}),
        "The highway is wide and broad. Looking at it, the highway " +
        "looks like it was once paved with stone blocks. Now, it is " +
        "broken and decrepit, with weeds and grass browing between " +
        "the broken stones.\n");
    add_item(({"stone blocks", "blocks", "cracked stone blocks"}),
        "The stone blocks are carved of grey stone. They were once " +
        "level and smooth and used as pavers for the road. Now " +
        "they are cracked and buckled from lack of care. Grass and " +
        "weeds grow between the cracks.\n");
    add_item(({"grasses", "grass"}),
        "The grass is green and grows between the stone blocks. Some " +
        "is trampled from travellers.\n");
    add_item(({"cracks"}),
        "The cracks are irregular splits in the stone blocks. Grasses " +
        "grow between the cracks.\n");
    add_item("thorns",
        "The thorns are stunted bushes that grow in groups alongside " +
        "the road. They look pretty sad and are not healthy look, " +
        "or so it seems.\n");
    add_item(({"ground", "dirt"}),
        "It is brown and dry looking with weeds and grasses growing in it. " +
        "A wide highway runs across the ground.\n");
    add_item(({"trees", "tall trees"}),
        "The tall trees grow scattered about on both sides of the highway. " +
        "The trees have naturally grown back and seem quite hardy in this " +
        "deserted area.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
}

/*
 * Function name : set_add_hedge_road
 * Description   : adds descr of north road
 */
void set_add_hedge_road()
{
    set_areadesc("small");
    set_area("path");
    set_areaname("outside the hedge");
    set_land("Bree");
    
    set_add_outside_hedge();
    set_add_dike();
    add_item(({"road", "path", "track"}),
        "The path runs between a large dike and the hedge. It is " +
        "nothing more than a well-trodden track of trampled grass.\n");
    add_item(({"bree"}),
        "It's hard to see the village of Bree because of the tall " +
        "hedge blocking your view. Nonetheless, sounds from the " +
        "village filter through the hedge.\n");
    add_item("grass",
        "The grass is short and matted down where countless travellers " +
        "have passed this way.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("The hedges move in the breeze.");
    add_room_tell("A score of birds fly suddenly out of the hedge.");
    add_room_tell("Something shakes some branches in the hedge.");
    add_room_tell("An animal pokes its head out of the bottom of " +
        "the hedge, then dashes back in.");


}

/*
 * Function name : set_add_sky
 * Description   : adds descr of sky
 */
void set_add_sky()
{
    add_item("sky",
        "It is @@day_desc@@, with @@light_type@@ filling " +
        "the sky.\n");
}

/*
 * Function name : add_bree_desc
 * Description   : This used to override add_my_desc.  However,
                   add_my_desc works very differently now, so this 
                   has been moved to a new name and called code update
                   to use this new name.
 */
void add_bree_desc(string desc)
{
    if (extraline)
        set_extraline(extraline + desc);
    else
        set_extraline(desc);
}
