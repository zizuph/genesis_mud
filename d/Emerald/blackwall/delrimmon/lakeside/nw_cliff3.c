/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff3.c
 *
 *  A large crack marks the sides of the cliffs here, on the northwestern
 *  shores of Del Rimmon in the Blackwall Mountains of Emerald.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    init();

/*
 * Function name:    create_cliff_room
 * Description  :    allows us to create the room with area presets
 */
 void
 create_cliff_room()
 {
     set_loc(3);
     set_side("northwest");
     set_extraline("A vast gaping crack runs from the base of the"
                 + " cliffs here to high above, where it appears to"
                 + " close. The cliffs run for a distance to the"
                 + " southwest, and appear to round a bend somewhat"
                 + " to the northeast.");
 
     add_item( ({"crack", "vast crack", "gaping crack",
                 "vast gaping crack"}), BSN(
         "The crack appears to be roughly three feet in width, and"
       + " runs for perhaps fifty yards high above, where it narrows"
       + " to a tiny slit. The crack is extremely dark, narrowing as"
       + " it travels into the side of the cliff, for what seems to"
       + " be a considerable distance."));
     add_item( ({"slit", "tiny slit"}), BSN(
         "The crack narrows to a tiny slit high above, where it appears"
       + " to close entirely, allowing the face of the cliff to run"
       + " without interruption at that height."));
     add_item( ({"distance", "considerable distance"}), BSN(
         "The depths of the crack are very dark, which would suggest"
       + " that it runs for a good distance into the side of the"
       + " cliff."));
     add_item( ({"depths of the crack", "depths"}), BSN(
         "The depths of the crack are quite beyond reach here."));
     add_item( ({"side of the cliff", "cliffside", "rock face",
                 "cliff face", "cliff faces", "cliff side",
                 "cliffsides", "cliff sides", "face of the cliff",
                 "face of the cliffs"}), BSN(
         "The sides of the cliff face are interrupted here by a vast"
       + " crack which runs from the base of the cliff to high above."));
     add_item( ({"base", "base of the cliff", "cliff base",
                 "base of the cliffs"}), BSN(
         "The base of the cliffs are interrupted here by a vast gaping"
       + " crack which runs high up the face of the rock."));
     add_item( ({"bend"}), BSN(
         "The cliffs appear to round a bend to the northeast, where"
       + " they then travel in a straight line to the east."));
     add_item( ({"straight line", "line"}), BSN(
         "The cliffs appear to be interrupted a good way to the"
       + " northeast where the waters ushering from the deadly"
       + " rapids far to the north have carved a path"
       + " through the Blackwall Mountains to empty into"
       + " Del Rimmon."));
     add_item( ({"sarn gebir", "rapids"}), BSN(
         "Though these rapids are well known in legend to have a"
       + " near deafening roar, even their mighty voice cannot be"
       + " heard from this distance."));
     add_item( ({"high above", "above"}), BSN(
         "High above, the crack seems to dwindle to nothing, and the"
       + " rock face runs uninterrupted. You see what appears to be"
       + " a ledge of some sort up there."));
     add_item( ({"ledge"}), BSN(
         "It is very difficult to make out from here, but there does"
       + " indeed appear to be a ledge running the length of the"
       + " cliffs high above."));
    add_item( ({"breeze", "cold breeze"}), BSN(
        "The breeze which issues from the crack in the rock seems"
      + " barely strong enough to lift a feather from the ground."
      + " The fact that it is coming from within the cliff seems"
      + " curious, though."));
 
     add_cmd_item( ({"crack", "vast crack", "gaping crack",
                     "vast gaping crack"}),
                   ({"enter", "probe"}), BSN(
         "Attempting to enter the crack, you find that it narrows"
       + " quickly to the point where it is impossible to go any"
       + " farther. You do feel what seems to be a cold breeze"
       + " blowing gently from the depths of the crack."));
     add_cmd_item( ({"crack", "vast crack", "gaping crack",
                     "vast gaping crack"}), 
                   ({"search"}), BSN(
         "Taking a closer look at the crack, you decide that it is"
       + " unlikely you could enter it, due to the fact that it narrows"
       + " sharply as it travels within the side of the cliff."));
    add_cmd_item( ({"crack", "into crack"}),
                  ({"crawl"}), BSN(
        "You get down on your hands and knees and begin to crawl"
      + " carefully into the crack. Soon, the crack narrows to the"
      + " point where even your head cannot go further. You are"
      + " forced to painstakingly back out of the crack."));
 
     add_exit(DELRIMMON_DIR + "lakeside/nw_cliff4","northeast");
     add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","east",0,1,1);
     add_exit(DELRIMMON_DIR + "lakeside/nw_wood2","southeast",0,1,1);
     add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b","south",0,1,1);
     add_exit(DELRIMMON_DIR + "lakeside/nw_cliff2","southwest");

    set_no_exit_msg( ({ "west", "northwest", "north" }),
        "The towering cliffs block your progress.\n");
 } /* create_cliff_room */

/*
 * Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(em_climbing_hook, "climb");
} /* init */
