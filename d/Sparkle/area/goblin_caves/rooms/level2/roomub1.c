/*
 * under bridge spider room
 * Boreaulam, Nov 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

object spider;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("under the bridge");
    set_long("You are in the middle of an enormous cavern, grasping tightly " +
      "to a thick, hemp rope as you dangle over the cold, black waters of " +
      "a wide underground lake. A massive spiderweb, the threads strong and " +
      "sticky, reach out from a small island all the way to the bottom of " +
      "the bridge beside you. Not far above, a sturdy-looking rope bridge " +
      "runs from north to south, spanning the entire length of the lake. You " +
      "notice dozens of tiny waves, rippling the surface of the water as " +
      "they travel past. In the far distance, circling around you, dozens of " +
      "torches have been mounted on the walls of the cavern. The only " +
      "reasonable way out from here would be to climb back up the rope.\n\n");
    
    add_item(({"bridge", "rope bridge"}),
             "You can see the wooden planks and the underside of the rope " +
             "bridge is not far above you, you could easily climb " +
             "back up to it at any time.\n");
    add_item(({"rope", "ropes", "hemp rope", "hemp ropes"}),
             "These thick ropes, which appear to be made of hemp, are " +
             "quite strong. Most of the ropes run across the length of the " +
             "lake, forming the bridge and handholds, but a few ropes " +
             "hang down from the bridge above, allowing someone to " +
             "climb either up or down.\n");
    add_item(({"plank", "planks", "wooden plank", "wooden planks"}),
             "These are the thick, wooden planks which enable people to " +
             "walk across the bridge.\n");
    add_item(({"water", "lake", "cave lake", "waters", "black water", "basin"}),
             "The cold, black water of the lake is right before you, gently " +
             "rising and falling as tiny waves drift past. A small island " +
             "is nearby, with a small hole in the surface.\n");
    add_item(({"torch", "torches"}),
             "You can spot dozens of torches, far away, circling the lake " +
             "as they have been mounted on the walls of the cavern.\n");
    add_item(({"island", "isle"}),
             "This is a very small island, standing in the middle of the " +
             "underground lake not far away from you. A massive spiderweb " +
             "stretches out from the island to reach the bottom of the " +
             "rope bridge near where you are hanging. On the surface of the " +
             "island, you can see a small hole which opens into a dark " +
             "tunnel, diving deep into the rock.\n");
    add_item(({"wave", "waves", "ripple", "ripples"}),
             "Out across the lake, you can see the light from the torches " +
             "dancing and twinkling on the gentle waves which ripple as " +
             "they rise and fall.\n");
    add_item(({"wall", "walls"}),
             "You cannot see the walls of the cavern clearly, but the light " +
             "from the torches outlines the edge of the cavern which " +
             "circles around you.\n");
    add_item(({"up", "ceiling", "shadows", "shadow"}),
             "The ceiling above is nothing more than a mass of jagged " +
             "shadows, as the light is not bright enough here to make out " +
             "any details.\n");
    add_item(({"web", "thread", "threads", "spiderweb", "spider web",
                    "web thread", "web threads"}),
             "@@get_threads_desc");
    add_item(({"hole", "small hole", "tunnel"}),
             "This small hole tunnels down into the surface of the small " +
             "island, you cannot reach it from here to see any further " +
             "details however.\n"); /* placeholder for spider caves entrance */

    add_cmd_item( ({"rope", "up"}),
                  "climb", 
                  "@@climb_rope");
    add_cmd_item( ({"web", "thread", "threads", "spiderweb", "spider web",
                    "web thread", "web threads"}),
                  "tear", 
                  "@@cut_thread");

    add_npc(NPCS_DIR + "l2_spider", 1, 0);

} /* create_room */

/*
 * Function name:        get_threads_desc
 * Description  :        returns threads description
 */
string 
get_threads_desc()
{
    if (present("_l2_spider", this_object())) 
    {
        return "A giant spider sits, waiting on the strong, sticky threads " +
            "of the web before you. A part of your mind wonders what might " +
            "happen if you tear these threads.\n";
    }

    return "The threads of spider web are strong and sticky, if you are " +
        "not careful, you might find yourself trapped down here, waiting " +
        "to provide a meal for a spider.\n";
} /* get_threads_desc */

/*
 * Function name:        cut_thread
 * Description  :        cuts thread and drops spider into water
 */
string 
cut_thread()
{
    object spider = present("_l2_spider", this_object());
    if (spider)
    {
        write_file("/d/Sparkle/area/goblin_caves/log/spider_dropped",
             ctime(time()) + " Spider was dropped into water by " +
             this_player()->query_name() + ".\n");
             
        spider->remove_object();        
        return "Tearing the threads of the web, you watch as the " +
            "spider falls with a splash into the black water below.\n";
    }

    return "Tearing the threads of the spider web, you watch as it flutters " +
        "down to the black water below. \n";
} /* cut_thread */

/*
 * Function name:        climb_rope
 * Description  :        climb rope back to the bridge
 */
string
climb_rope()
{

    if (present("_l2_spider", this_object())) 
    {
        return "You quickly attempt to climb up the rope, but a darting " +
            "stab from the spider knocks you back down and prevents you " +
            "from leaving.\n";
    }

    tell_room(this_object(), QCTNAME(this_player()) + " climbs up.\n");
    write("You climb up the rope.\n\n");

    this_player()->move_living("M", ROOMS_DIR + "level2/roomr1", 1);
    return "";
} /* climb_rope */

