/*
 *  /d/Sparkle/area/tutorial/farm/crossroads.c
 *
 *  The crossroads north of Greenhollow in Silverdell. This room
 *  teaches about what to do next.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    34  /* the chapter for the sign */

/* prototypes */
public void        create_silverdell();
public string      describe(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("at a crossroads north of Greenhollow");
    set_long(&describe("long"));

    add_outdoor_items();
    add_road_items();
    add_forest_items();
    add_river_items();
    add_mountain_items();

    add_item( ({ "here", "area", "crossroads",
                 "crossroad" }), &describe("long"));
    add_item( ({ "north", "farm", "farmlands", "farmer brown's farm",
                 "farmer browns farm" }), &describe("farm"));
    add_item( ({ "smoke", "smoke clouds", "black smoke",
                 "cloud of smoke", "clouds of smoke",
                 "black cloud", "black clouds",
                 "black clouds of smoke" }), &describe("smoke"));
    add_item( ({ "town", "south", "greenhollow", "gate", "north gate",
                 "town of greenhollow", "burning town", "fire" }),
        &describe("town"));

    add_exit("crossroad_2", "north");
    add_exit("crossroad_3", "east");
    add_exit("crossroad_1", "south");
    add_exit("crossroad_4", "west");

    reset_room();
} /* create_silverdell */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    string  cross_txt = "You stand at a crossroads. A dirt road makes"
                      + " its way between the town of Greenhollow to"
                      + " the south and farmlands to the north. ";

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return cross_txt + "West, the road travels toward the"
                  + " mountains where Baron von Krolock now rules these"
                  + " lands. East, the road winds down toward what used"
                  + " to be the Silverdell River and beyond to the"
                  + " now barren Sterling Forest.\n\n";
                break;
            case "farm":
                return "The farm itself is not visible from here, but"
                  + " you get the distinct impression that something"
                  + " very bad has happened to the north.\n";
                break;
            case "smoke":
                return "Clouds of black smoke rise from the farm to the"
                  + " north. You smile at the thought of what destruction"
                  + " must lie in that direction.\n";
                break;
            case "town":
                return "Greenhollow is burning! So much for Lars'"
                  + " promise to protect the town from harm. It seems"
                  + " that even he couldn't protect them from you.\n";
                break;
        }
    }

    switch(arg)
    {
        case "long":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                return cross_txt + "West, the road travels toward the"
                  + " now majestic and gleaming peaks of the mountains."
                  + " East, the road winds down toward the Silverdell"
                  + " River, and beyond to the noble trees of the"
                  + " Sterling Forest.\n\n";
            }

            return cross_txt + "West, the road travels toward rather"
              + " ominous mountain peaks. East, the road winds down"
              + " toward the Silverdell River, and beyond to the"
              + " Sterling Forest.\n\n";
            break;
        case "farm":
            return "To the north lies Farmer Brown's farm. It is well"
              + " known throughout Silverdell as a place that welcomes"
              + " strangers. It is yet too distant to see from here.\n";
            break;
        case "smoke":
            this_player()->command("$exa white cloud");
            if (this_player()->query_wiz_level())
            {
                return "Normally, we would have the player do"
                  + " <exa white cloud> here using command. Since you"
                  + " are a wizard, it won't work for you.\n";
            }
            else
            {
                return "";
            }
            break;
        case "town":
            return "Greenhollow is a ways to the south, beyond the"
              + " north gate of town.\n";
            break;
    }
} /* describe */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */
