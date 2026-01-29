/*
 *  /d/Sparkle/area/orc_temple/rooms/2_hall10.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public int          go_exit(string which_way);
public int          flee_stairs(string arg);
public void         init();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("at a bend in a tunnel leading north and west");
    set_long("A sickening, primal urge to flee batters your mind"
      + " as you stand at this bend in the tunnel. The northern"
      + " walk down the tunnel feels like an extremely good idea."
      + " Anything would be better than what is to the west. In"
      + " that direction, at the end of a short passage, you"
      + " glimpse a dark stairway leading down, and madness"
      + " beyond.\n\n");

    add_item( ({ "urge", "primal urge", "urge to flee",
                 "primal urge to flee", "sickening urge",
                 "sickening urge to flee", "sickening primal urge",
                 "sickening, primal urge",
                 "sickening primal urge to flee",
                 "sickening, primal urge to flee" }),
        "The horror closes in on you here. You can feel it. It"
      + " knows you! It knows you approach! It ... knows ...\n");
    add_item( ({ "bend", "corner", "bend in the tunnel" }),
        "The tunnel rounds the bend here, but surely the only"
      + " reasonable choice is north.\n");
    add_item( ({ "it", "horror" }),
        "No! It cannot enter your mind! You must ... escape ... \n");
    add_item( ({ "north", "northern walk", "tunnel", "long tunnel",
                 "walk" }),
        "Oh, look at that long tunnel. Oh, what a good idea. Yes,"
      + " yes that would be the perfect way to walk RIGHT NOW.\n");
    add_item( ({ "idea", "good idea" }),
        "Yes! The more you think about it, the more you are sure."
      + " Walking north is the best thing. The smart thing! The thing"
      + " to do. Oh, it feels better just knowing that. Phew.\n");
    add_item( ({ "west", "short passage" }),
        "No ... not that way ... not ... that ... way ...\n");
    add_item( ({ "stair", "stairs", "stairway", "dark stairway",
                 "dark stairs", "dark stair", "madness" }),
        "As your gaze meets the stairway, it seems to shift, twisting"
      + " into the pulsing visage of amorphous flesh filled with"
      + " so many hideous twisting eyes ... all of which can see"
      + " you standing here ... waiting to ... AAAAAAIGH! No. Only"
      + " stairs. But stairs you must NEVER approach. EVER.\n");
    add_item( ({ "eye", "eyes", "amorphous flesh", "flesh", }),
        "@@yogsothoth@@");

    add_dungeon_items();

    add_exit("3_hall9", "north", &go_exit("north"), 1, 0);
    add_exit("3_down", "west", &go_exit("west"), 1, 0);

    set_no_exit_msg( ({ "northeast", "southeast", "east",
                        "southwest", "northwest", "south" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Have this room use madness tells.
 */
public void
add_dungeon_tells()
{
    add_madness_tells();
} /* add_dungeon_tells */


/*
 * Function name:        go_exit
 * Description  :        provite feedback to the player on their
 *                       choice of exits
 * Arguments    :        string which_way - the dir they chose
 * Returns      :        int 1 - blocked, 0 - not blocked
 */
public int
go_exit(string which_way)
{
    if (which_way == "north")
    {
        write("Ah ... yes ... the right choice. Your mind immediately"
          + " feels relief walking this direction.\n\n");
        return 0;
    }

    write("Before you even take your first step, the dungeon vanishes,"
      + " and you find yourself alone and naked standing transfixed"
      + " before a great amorphous form whose many glistening eyes"
      + " pulse and throb. As each eye passes its gaze over you, you"
      + " feel a layer of flesh ripped from you, tearing you down first"
      + " by the skin, then by the fat, then by the muscle, and finally"
      + " by the bone until only your own glistening and tender organs"
      + " remain. Slowly, you feel the tiny portions of you that are left"
      + " drawn slowly into the oblivion of the horror until only your"
      + " brain, shaking and quivering with terror, remains. Your brain"
      + " spasms, ripping itself open as you hear your own high-pitched"
      + " screams! With a snap, you are again standing at the bend in the"
      + " passage. Hands trembling, you wipe your face, certain that you"
      + " can never go that way.\n");

    return 1;
} /* go_exit */


/*
 * Function name:        flee_stairs
 * Description  :        The player gives in to terror and flees.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
flee_stairs(string arg)
{
    if (strlen(arg))
    {
        notify_fail("No need to be specific! Just flee!\n");
        return 0;
    }

    write("Just as the horror seems about to snatch your last memories"
      + " of sanity, you do the only sensible thing, and sprint down the"
      + " narrow passage to the north!\n\n.\n.\n.\n\nPhew!\n\n");
    this_player()->command("$north");

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player north here using"
          + " command(). Since you're a wizard that won't work, so you"
          + " can just type it yourself.\n");
    }

    return 1;
} /* flee_stairs */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(flee_stairs, "flee");
    add_action(flee_stairs, "escape");
} /* add_action */
