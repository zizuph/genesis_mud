/*
 *  /d/Sparkle/area/tutorial/farm/crossroad_2.c
 *
 *  A road travelling between the crossroads and Farmber Brown's
 *  farm in Silverdell.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

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
    set_short("on a dirt road near to a farm");
    set_long(&describe("long"));

    add_outdoor_items();
    add_road_items();

    add_item( ({ "here", "area" }), &describe("long"));
    add_item( ({ "north", "farm", "farmer brown's farm",
                 "farmer browns farm" }), &describe("farm"));
    add_item( ({ "smoke", "smoke clouds", "black smoke",
                 "cloud of smoke", "clouds of smoke",
                 "black cloud", "black clouds",
                 "black clouds of smoke" }), &describe("smoke"));
    add_item( ({ "filth", "debris", "road", "lane", "fence",
                 "fences", "field", "fields", "dusty road",
                 "dirt road", "path", "track" }), &describe("road"));
    add_item( ({ "crossroad", "crossroads", "south" }),
        "The crossroads are visible in the distance to the south.\n");

    add_exit("barnyard", "north");
    add_exit("crossroads", "south");
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
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return "Filth is strewn along the road here, which"
                  + " heads north toward what used to be a very happy"
                  + " farm. The black clouds of smoke which which are"
                  + " trailing up into the sky suggest that things are"
                  + " not so happy there anymore. The crossroards lie"
                  + " south of here.\n\n";
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
            case "road":
                return "The road is choked with filth and debris here."
                  + " The fences which lined the road have been ripped"
                  + " from their posts and in some cases burned.\n";
                break;
        }
    }

    switch(arg)
    {
        case "long":
            return "You are on a dusty road which runs north toward a"
              + " farm which is barely visible in the distance. Fences"
              + " on either side of the road border fields which"
              + " extend as far as the eye can see. The"
              + " crossroads lie south of here.\n\n";
            break;
        case "farm":
            return "To the north lies Farmer Brown's farm. It is well"
              + " known throughout Silverdell as a place that welcomes"
              + " strangers. You can only get small glimpses of it from"
              + " here.\n";
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
        case "road":
            return "The road runs between fences on either side which"
              + " separate the fields from the lane.\n";
            break;
    }
} /* describe */
