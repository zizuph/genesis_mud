 /*
  * Beach room where the warriors landed their boat to setup the camp
  */
#pragma strict_types
  
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
  
inherit "/std/room";

void
create_room()
{
    set_short("a small beach");
    set_long("You are on a small patch of sandy beach, streching out beween the thick wilderness " +
             "to the north and clear water to the south. A bit across the water " +
             "the Cadu pier starts and continues further to the west. " +
             "The white sand is smooth and hot from the sun, but " +
             "in the middle of the patch the sand has a deep cut.\n");
    
    add_item("pier",
             "The pier stands across the water to the south and continues further to the west. Judging from " +
             "the water level at the pier the water must be shallow on this side of the pier, " +
             "but deeper on the other side.\n");
    add_item("sand",
             "The sand is white and hot from the sun.\n");
    add_item("beach",
             "It's a small patch of sandy beach, quite secluded between the wilderness to the north "+
             "and water to the south. The sand looks nice and warm, and would've looked like the " +
             "perfect beach if not for the many signs of disturbance. There are deep marks in the sand, as " +
             "if a boat has been dragged up from the water, and many footprints all over.\n");
    add_item(({"signs", "disturbance", "signs of disturbance", "cut", "deep cut"}),
             "The middle of the small beach is dominated by deep marks in the sand, " +
             "as if a boat has been dragged up from the water. Around it there are many " +
             "footprints.\n");
    add_item(({"marks", "deep marks"}),
             "The deep marks in the sand stretches from the water and quite a bit onto the beach." +
             "If only there would come some large waves to flatten the sand out again.\n");
    add_item("footprints",
             "Alot of the footprints are around the deep marks, making it look like several people " +
             "dragged a boat up onto the beach. Some footprints can be seen going north, " +
             "towards the wilderness.\n");
    add_item(({"wilderness", "green wall"}),
             "A little to the north the thick wilderness flanks the beach like an impenetrable " +
             "green wall. But when you look close you notice that someone has cleared a small opening " +
             "and you can see a small trampled path on the other side.\n");
    add_item(({"opening", "small opening", "path", "trampled path"}),
             "Someone has cleared an opening in the thick wilderness and trampled up a small "+
             "path leading north.\n");
    add_item("water",
             "The water looks nice and clear, whith small waves washing up on the beach. You notice a " +
             "narrow passage in the water where it looks shallow enough to wade south to the pier.\n");
    add_item(({"narrow passage", "passage", "shallow water", "sandbank"}),
             "Between the pier and beach you see a sandbank under the surface, creating a " +
             "narrow passage where it's shallow enough to wade south to the pier.\n");

    add_exit(CAMP_ROOM + "path-s-0", "north", 0, 0, 1);
    BEACH;
}

int
wade(string s)
{
    if(s == "s" || s == "south")
    {
        write("You wade out into the water and find the pasage to the pier.\n");
        say(QCTNAME(this_player()) + " wades out into the waster towards the pier.\n");
        tell_room(CAMP_ROOM + "beach-water",
            QCTNAME(this_player()) + " arrives wading from the north.\n");
        this_player()->move_living("M", CAMP_ROOM + "beach-water", 0, 0);
        return 1;
    }
    if(s == "sw" || s == "southwest" || s == "se" || s == "southeast")
    {
        notify_fail("You wade out into the water a bit, but it soon becomes " +
                    "too deep to wade further in that direction. Refreshing though!\n");
        return 0;
    }
    if(s == "nw" || s == "ne" || s == "e" || s == "n" || s == "w" ||
       s == "northwest" || s == "northeast" || s == "east" || s == "north" ||
       s == "west")
    {
        notify_fail("You try to wade around in the sand on the beach, but " +
                    "mostly you just look funny as you wobble around with your " +
                    "toes getting stuck in the sand all the time.\n");
        return 0;
    }
    if(s == "u" || s == "up")
    {
        notify_fail("It's not like you can fly.\n");
        return 0;
    }
    if(s == "d" || s == "down")
    {
        notify_fail("You kick down into the sand, but you just hurt yourself.\n");
        return 0;
    }
    else
    {
        notify_fail("Wade where?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action(wade, "wade");
}