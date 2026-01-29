/*
 * under bridge room
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
      "a wide underground lake. Not far above, a sturdy-looking rope bridge " +
      "runs from north to south, spanning the entire length of the lake. You " +
      "notice several black flowers floating on the surface of the water, " +
      "gently bobbing up and down as they ride the tiny waves which ripple " +
      "past. In the far distance, circling around you, dozens of torches " +
      "have been mounted on the walls of the cavern. The only reasonable " +
      "way out from here would be to climb back up the rope.\n\n");
    
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
             "rising and falling as tiny waves drift past. There are also " +
             "several black flowers floating on the surface here.\n");
    add_item(({"flower", "flowers", "black flowers", "black flower"}),
             "Several delicate looking black flowers float gently on the " +
             "surface of the water here, bobbing slowly up and down as " +
             "tiny waves on the lake ripple past.\n");
    add_item(({"torch", "torches"}),
             "You can spot dozens of torches, far away, circling the lake " +
             "as they have been mounted on the walls of the cavern.\n");
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

    add_cmd_item( ({"rope", "up"}),
                  "climb", 
                  "@@climb_rope");
} /* create_room */

/*
 * Function name:        climb_rope
 * Description  :        climb rope back to the bridge
 */
string
climb_rope()
{

    tell_room(this_object(), QCTNAME(this_player()) + " climbs up.\n");
    write("You climb up the rope.\n\n");

    this_player()->move_living("M", ROOMS_DIR + "level2/roomr3", 1);
    return "";
} /* climb_rope */

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
 * Description  :        picks black flower for goblin in love quest
 */
int
pick_flower(string s)
{
    notify_fail("Pick what? A flower?\n");
    if(s!="" && s!="flower" && s!="flowers")
        return 0;

    object flower = clone_object(OBJS_DIR + "l2_flower");
    flower->set_colour("black");
    flower->add_name(LEVEL2_QUEST_FLOWER);
    if(!flower->move(this_player()))
    {
        write("You picked one black flower.\n");
    }
    else
    {
        notify_fail("You tried picked one black flower. " + 
                    "But you couldn't hold it.\n");
        return 0;
    }
    
    return 1;
} /* pick_flower */
