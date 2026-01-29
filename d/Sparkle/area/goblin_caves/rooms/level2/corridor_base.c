/*
 * corridor room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

string get_add_room_long();
string get_lake_dir();
string get_exit_dir();
string get_flowers_desc();

int flowers;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("lake path");
    set_long("You are currently standing at the " + get_exit_dir() + " edge " +
        "of an enormous cavern. In the middle of the cavern, an underground " +
        "lake spreads out before you to the " + get_lake_dir() +
        ", where the black waters are gently lapping at your " +
        "feet. A narrow path winds around the pale stalagmites which jut up " +
        "out of the ground, closely following the lake edge. Occasional " +
        "tufts of vegetation seem to be growing near the lake, barely " +
        "visible in the shadowy darkness. Several torches have been mounted "+
        "on the cave walls, partially hidden by the jagged stalactites which " +
        "hang down from the ceiling, providing enough light to make " +
        "your way along the path. An irregular opening in the " +
        "grey stone of the " + get_exit_dir() + " wall appears to lead into " +
        "a new cave." + get_add_room_long());
 
    add_item(({"lake", "basin", "underground lake"}), 
        "Dark and silent, this wide lake spreads across the middle of " +
        "this massive cavern. Shimmering light reflects on the tiny ripples " +
        "of waves which gently glide across the surface of the lake, " +
        "twinkling like little stars in a night sky.\n");
    add_item(({"water", "black water"}), 
        "Black water fills the massive basin which is the underground lake " +
        "before you. Low, gentle waves are visible as light from the torches " +
        "bounces and twinkles off of the tiny ripples which lap against the " +
        "shoreline.\n");
    add_item(({"vegetation", "growth", "tuft", "tufts"}),
        "Scattered along the shore of the lake, small tufts of vegetation " +
        "are occasionally visible growing up out from tiny crevices which " +
        "open in the stone floor. Tiny patches of green grass and clumps of " +
        "wet moss seem to hide the odd, small flower, all growing peacefully " +
        "despite the lack of light.\n");
    add_item(({"grass", "patch", "patches", "green grass", "pale grass"}),
        "There are some small patches of a pale green grass which grow along " +
        "the edge of the lake. The grass has a faded appearance, probably " +
        "from the lack of sunlight. You spot the occasional splash of colour " +
        "from the flowers which hide between the grass and the moss.\n");
    add_item(({"moss", "wet moss", "grey moss", "clump", "clumps"}), 
        "Several clumps of a wet, grey moss are visible along the shore of " +
        "the lake. The moss mostly grows near the patches of pale grass in " +
        "the crevices which open in the floor here.\n");
    add_item(({"flowers", "flower"}), 
        "@@get_flowers_long_desc");
    add_item(({"path", "narrow path"}), 
        "A winding narrow path weaves in and around the various stalagmites " +
        "and stalactites as it follows the shore of the dark lake which " +
        "dominates the middle of the cavern.\n");
    add_item(({"opening", "irregular opening", "cave"}),
        "An irregular opening in the " + get_exit_dir() + " wall of the " +
        "cavern appears to lead into a small cave. You cannot really see " +
        "any details from here, but the opening is wide enough for you " +
        "to pass through if you wanted to investigate further.\n");
    add_item(({"waves", "wave", "ripple", "ripples", "star", "stars"}), 
        "You can hear the gentle sounds of the waves lapping up against the " +
        "shore near your feet. Tiny ripples of waves sparkle across the " +
        "surface of the lake, catching and reflecting light from the torches " +
        "to shine like millions of tiny stars in a dark, night sky.\n");
    add_item(({"cavern", "enormous cavern", "underground cavern", "here"}),
        "You are currently standing at the " + get_exit_dir() + " edge " +
        "of an enormous cavern. In the middle of the cavern, an underground " +
        "lake spreads out before you to the " + get_lake_dir() +
        ", where the black waters are gently lapping at your " +
        "feet. A narrow path winds around the pale stalagmites which jut up " +
        "out of the ground, closely following the lake edge. Occasional " +
        "tufts of vegetation seem to be growing near the lake, barely " +
        "visible in the shadowy darkness. Several torches have been mounted "+
        "on the cave walls, partially hidden by the jagged stalactites which " +
        "hang down from the ceiling, providing enough light to make " +
        "your way along the path. An irregular opening in the " +
        "grey stone of the " + get_exit_dir() + " wall appears to lead into " +
        "a new cave." + get_add_room_long());
    add_item(({"stalagmites", "stalactites"}), 
        "The cavern is decorated with several pale stalagmites and " +
        "stalactites, closing around you like massive sets of shadowy, " +
        "jagged teeth. The narrow path you are on, twists and turns " +
        "so that you can easily go around them.\n");
    add_item(({"shadow", "shadows"}), 
        "Long shadows stretch across the entire breadth of the cavern, " +
        "flickering in the torch light which eminates from the walls. " +
        "Perhaps it is just your imagination, but it almost feels like " +
        "there are unseen eyes watching you from the darkest shadows.\n");
    add_item(({"eyes", "unseen eyes"}), 
        "You cannot actually see any eyes, it is just a nagging feeling " +
        "you get from some of the darkest shadows which surround you.\n");
    add_item(({"wall", "walls"}),
        "These walls have been crudely carved out of the mountain " +
        "itself, the dull grey of the granite being broken only " +
        "by the occasional torch which has been mounted on the walls.\n");
    add_item(({"ceiling", "up"}),
        "You can barely make out the ceiling of the cavern from here, " +
        "as most of the stalactites block your view and cast shadows " +
        "everywhere else. All you can see of the ceiling itself is just " +
        "an impression of the same rough, grey granite of the walls.\n");
    add_item(({"stone", "granite", "grey stone", "grey granite"}),
        "Seemingly carved out of the heart of the mountain, the walls, " +
        "ceiling and floor here are all composed of the same pale, grey " +
        "granite. Most of the stone appears to be in a natural state, but " +
        "it is clear that some of it has been chiseled away by hands to " +
        "make it more accessible for people.\n");
    add_item(({"floor", "down", "ground"}), 
        "Aside from the occasional stalagmite jutting up out of the ground, " +
        "the floor here is smooth, mostly following a narrow path which " +
        "is obviously well travelled.\n");
    add_item(({"crevice", "crack", "narrow crevice", "fissure", "crevices"}), 
        "The floors and walls are filled with many narrow crevices, some " +
        "of which appears to hold tiny tufts of vegetation.\n");
    add_item(({"torch", "torches"}), 
        "A small handful of torches have been scattered across the " +
        get_exit_dir() + " wall of the cavern, mounted in such a manner " +
        "that they provide as much light as possible down here. Yet, " +
        "despite this effort, there are many long, sinister shadows " +
        "which stretch in all directions.\n");
    add_item(({"sun", "sunlight", "sky", "night", "night sky"}), 
        "You are inside an enormous, underground cavern! You could only " +
        "see that if you were actually outside!\n");

    add_npc(NPCS_DIR + "goblin2_1", 2, &->arm_me());
    
    flowers = 3;
} /* create_room */

/*
 * Function name:        reset_room
 * Description  :        regrowths flowers
 */
void 
reset_room()
{
    ::reset_room();
    flowers = 3;
} /* reset_room */

/*
 * Function name:        init
 * Description  :        on init hook
 */
void
init()
{
    ::init();
    add_action("pick_flower", "pick", 0);
} /* init */


/*
 * Function name:        pick_flower
 * Description  :        picks flower
 */
int
pick_flower(string s)
{
    notify_fail("Pick what? A flower?\n");
    if(s!="" && s!="flower" && s!="flowers")
        return 0;

    if(flowers <= 0)
    {
        write("There is no flowers you can reach. Probably more will " +
            "grow in time.\n");
        return 1;
    }
    
    object flower = clone_object(OBJS_DIR + "l2_flower");
    flowers = flowers - 1;
    flower->set_colour(get_flowers_desc());
    if(!flower->move(this_player()))
    {
        write("You pick a " + get_flowers_desc() + " flower.\n");
    }
    else
    {
        notify_fail("You try to pick one of the " + get_flowers_desc() + 
            " flowers tucked in a narrow crevice of stone, but your " +
            "fingers are too thick to reach it.\n");
        return 0;
    }
    
    return 1;
} /* pick_flower */

/*
 * Function name:        get_flowers_long_desc
 * Description  :        returns flowers description
 */
string
get_flowers_long_desc()
{
    return "Hiding in amongst the grass and moss, you see some " + 
        get_flowers_desc() + " flowers.\n";
} /* get_flowers_long_desc */

/*
 * Function name:        get_flowers_desc
 * Description  :        blank function to override to return flowers colour
 */
string
get_flowers_desc()
{
    return "wrong colour";
} /* get_flowers_desc */

/*
 * Function name:        get_add_room_long
 * Description  :        blank function to override to return additional long 
 *                       description
 */
string
get_add_room_long()
{
    return "\n\n";
} /* get_add_room_long */

/*
 * Function name:        get_exit_dir
 * Description  :        blank function to override to return outer room exit
 */
string
get_exit_dir()
{
    return "wrong";
} /* get_exit_dir */

/*
 * Function name:        get_lake_dir
 * Description  :        blank function to override to return dir to lake
 */
string
get_lake_dir()
{
    return "wrong";
} /* get_lake_dir */

/*
 * Function name:        get_flowers_left
 * Description  :        test function to return number of flowers left
 */
int 
get_flowers_left()
{
    return flowers;
} /* get_flowers_left */

