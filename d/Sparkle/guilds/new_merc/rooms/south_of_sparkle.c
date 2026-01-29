/*
 *  /d/Sparkle/guilds/new_merc/rooms/n.c
 *
 *  The inside of the old lumber mill. This is the room where players
 *  may freely join or leave the guild.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit "/std/room";

#include <stdproperties.h>
#include <time.h>

/* Prototypes */
public void        create_room();
public int         check_exit();
public int         turkey_exit();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("on a road before the southern gates of Sparkle");
    set_long("You stand on well-used road before the southern gates of"
      + " Sparkle. The city walls run for a great distance both east"
      + " and west separated by a great gate through which the road"
      + " passes in and out of town. South, the road travels beyond the"
      + " northern edges of the Jade Forest, and is lost from sight.\n\n");

    add_item( ({ "road", "street", "path", "well used road",
                 "used road", "well-used road" }),
        "The road is clearly seeing a lot of use these days. There are"
      + " signs of both foot and wagon along the way.\n");
    add_item( ({ "sign", "signs" }),
        "Unmistakable. This is a well used road.\n");
    add_item( ({ "gate", "gates", "southern gate", "southern gates",
                 "southern gate of sparkle", "southern gates of sparkle",
                 "south gate", "south gate of sparkle",
                 "great gate" }),
        "The gate is massive, rising high over the road as it travels"
      + " beneath on its way into the city.\n");
    add_item( ({ "city", "city of sparkle", "sparkle",
                 "sparkle city", "town" }),
        "Sparkle is the greatest city in the area. It dominates the"
      + " view to the north.\n");
    add_item( ({ "view", "view to the north" }),
        "Sparkle dominates it ... but we covered that.\n");
    add_item( ({ "wall", "walls", "city walls", "city wall",
                 "wall of the city", "walls of the city" }),
        "The walls of the city are very tall and very strong. It"
      + " would take a mighty force to lay siege to them if there"
      + " were enough troops in the city to mount a solid defence.\n");
    add_item( ({ "forest", "jade forest", "tree", "trees", "woods" }),
        "The Jade forest spreads out as far as the eye can see to"
      + " the south.\n");
    add_item( ({ "northern edge", "edge", "edges",
                 "northern edges", "northern edges of the forest",
                 "northern edge of the forest",
                 "edge of the forest", "edges of the forest",
                 "edge of the jade forest", "edges of the jade forest",
                 "northern edge of the jade forest",
                 "northern edges of the jade forest" }),
        "The forest ends quite close to the edge of the walls. Only"
      + " where the road runs through it do the trees fall away.\n");
    add_item( ({ "ground", "down", "floor", "dirt", "grass" }),
        "Grass grows alongside the road between the gates and the"
      + " edge of the forest.\n");
    add_item( ({ "sky", "up" }),
        "The sky is bright blue and filled with light.\n");
    add_item( ({ "light", "illumination" }),
        "It is steady and helps one to see.\n");
    add_item( ({ "cloud", "clouds" }),
        "There are no clouds in the sky right now. Perhaps they all"
      + " drifted away.\n");
    add_item( ({ "sun" }),
        "The sun shines brightly in the sky above.\n");
    add_item( ({ "newly-made road", "rather newly-made road",
                 "new road", "west" }),
        "This road looks much newer anything else around here.\n");

    add_exit("/d/Genesis/start/human/town/pier6",
             "north", check_exit, 1, 0);
    add_exit(ROOM_DIR + "path1", "south");
//  add_exit("/d/Genesis/ateam/aoe/events/turkey2014/turkey_farm",
//           "west", turkey_exit, 1, 0);
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        Send the players a message when they enter
 *                       town.
 * Returns      :        int 1 - prevent exit
 *                           0 - allow exit
 */
public int
check_exit()
{
    write("\nYou pass beneath the great gates and head north,"
      + " passing many buildings on your way toward the inner city.\n\n");

    return 0;
} /* check_exit */


/*
 * Function name:        turkey_exit
 * Description  :        Send the players a message when they enter
 *                       town.
 * Returns      :        int 1 - prevent exit
 *                           0 - allow exit
 */
public int
turkey_exit()
{
    int     right_now  = time();

    if (right_now < STAMP2TIME("Nov 27 2014"))
    {
        if (this_player()->query_wiz_level())
        {
            write("The event isn't yet open, but since"
              + " you are a wizard, you can pass.\n");
            return 0;
        }

        TELL_G("\n\n\t ----" + capitalize(this_player()->query_real_name())
          + " is halted by the turkey farmers!\n\n");

        write("As you approach the new road, a group of stern-looking"
          + " farmers emerges from the trees. They tell you that the"
          + " event will begin on \"The Day of Curse\" and not before."
          + " Whatever this might mean, they do not let you pass"
          + " yet.\n");
        return 1;
    }

    return 0;
} /* turkey_exit */
