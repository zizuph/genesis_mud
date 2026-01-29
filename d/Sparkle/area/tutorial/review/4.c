/*
 *  /d/Sparkle/area/tutorial/review/4.c
 *
 *  These rooms are part of the original character creation tutorial,
 *  which has since been replaced. It is left in the library in Greenhollow
 *  as a quest of sorts to provide players with review and practice of
 *  basic concepts.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 3, 2016 to fix some typos
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit REVIEW_DIR + "skip";
inherit LIB_DIR + "lib_sign";

/* definitions */
#define  TUTORIAL_CHAPTER    4  /* the chapter for the sign */

#include <stdproperties.h>


/* prototypes */
public void        create_room();
public void        reset_room();
public int         do_enter(string arg);
public void        init();
public int         hint(string arg);


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("4");
    set_short("a square stone chamber with no exits");
    set_long("You have entered a square chamber made entirely of stone."
      + " The walls which surround you each appear different in some way,"
      + " as do the floor and ceiling. Directly in the center of the room"
      + " is a large sign mounted on a post.\n\n");

    add_item( ({ "surface", "surface of the floor", "seamless surface" }),
        "The surface of the floor is so seamless that it almost takes on"
      + " the look of polished glass.\n");
    add_item( ({ "w", "west" }),
        "Use <exa west wall> to examine the west wall.\n");
    add_item( ({ "n", "north" }),
        "Use <exa north wall> to examine the north wall.\n");
    add_item( ({ "e", "east" }),
        "Use <exa east wall> to examine the east wall.\n");
    add_item( ({ "s", "south" }),
        "Use <exa south wall> to examine the south wall.\n");
    add_item( ({ "chamber", "square chamber", "area", "here" }),
        "This chamber is comprised of four walls, a ceiling, and a floor."
      + " There is a lot to look at here, if you choose to do so.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall do you wish to examine? The north wall, east wall,"
      + " south wall, or west wall?\n");
    add_item( ({ "north wall", "north", "northern wall" }),
        "The north wall is completely bare.\n");
    add_item( ({ "east wall", "east", "eastern wall" }),
        "The east wall is covered with ivy.\n");
    add_item( ({ "ivy" }),
        "Ivy covers most of the east wall. Looking closer, you notice"
      + " that the ivy has grown over an opening that you could probably"
      + " fit through if you tried. It is possible to go <southeast> from"
      + " here.\n");
    add_item( ({ "opening" }),
        "The opening is fairly well hidden by the ivy. It looks large"
      + " enough for you to pass through if you wished to travel"
      + " <southeast>.\n");
    add_item( ({ "south wall", "south", "southern wall" }),
        "A beautiful painting hangs on the south wall.\n");
    add_item( ({ "painting", "beautiful painting" }),
        "The painting depicts a toroid shaped planet drifting before"
      + " a backdrop of countless stars. You notice that the frame of"
      + " the painting has been engraved.\n");
    add_item( ({ "star", "stars", "backdrop", "countless stars",
                 "backdrop of stars", "backdrop of countless stars" }),
        "The artist who created this painting spent a great deal of time"
      + " making the stars look beautiful and very real.\n");
    add_item( ({ "frame", "frame of the painting", "engraving",
                 "engravings" }),
        "Engraved on the frame are the words: 'The Lands of Genesis.'\n");
    add_item( ({ "planet", "toroid", "toroid shape",
                 "toroid planet", "toroid shaped planet",
                 "land", "lands", "land of genesis", "lands of genesis",
                 "world", "genesis" }),
        "You can't help but notice that this planet is really in the"
      + " shape of a massive doughnut, dotted with continents and seas.\n");
    add_item( ({ "continent", "continents", "sea", "seas",
                 "continents and seas" }),
        "The continents and seas wrap around the exterior of the donut"
      + " just as they might on any normal spherical planet.\n");
    add_item( ({ "donut", "doughnut" }),
        "Whatever god created Genesis must have been hungry or"
      + " something.\n");
    add_item( ({ "west wall", "western wall", "west" }),
        "The west wall is made up mostly of stone. However, you notice"
      + " that a large rectangle at the center of the wall is made up"
      + " of bricks.\n");
    add_item( ({ "brick", "bricks", "rectangle", "rectangle of bricks",
                 "brick rectangle" }),
        "The bricks in the west wall make it look as if someone has"
      + " intentionally blocked a perfectly good passageway. Upon"
      + " closer inspection, you notice that the bricks shimmer now and"
      + " then, almost as if they were a mere illusion.\n");
    add_item( ({ "illusion", "shimmer" }),
        "If these bricks are an illusion, then you would probably be"
      + " able to travel west from here.\n");

    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling above your head is comprised of wooden beams.\n");
    add_item( ({ "wood", "beam", "beams", "wooden beam", "wooden beams" }),
        "The wooden beams look very sturdy and are finely polished.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor at your feet is made up of flagstones.\n");
    add_item( ({ "stones", "stone", "flagstone", "flagstones" }),
        "Flagstones have been carefully fit together to form a"
      + " nearly seamless surface for the floor.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_tutorial", 1);
    add_prop(ROOM_S_MAP_FILE, "tutorial_map.txt");

    add_exit("5", "southeast", 0, 1, 1);
    add_exit("3", "west");

    reset_room();
} /* create_room */


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


/*
 * Function name:        do_enter
 * Description  :        allow players to try to enter the opening
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to enter?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [hidden] 'opening' / 'ivy'"))
    {
        return 0; /* can't parse the syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'east' here, using"
          + " command. Since you are a wizard, that won't work. Simply"
          + " type <southeast> yourself.\n");
    }

    write("You pass through the opening and come into another room.\n");
    this_player()->command("$southeast");
    return 1;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some commands to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
    add_action(hint, "hint");
    add_action(skip, "skip");
    add_action(tutorial_quit, "quit");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    if (arg == "full")
    {
        write("Here's what you should do:\n\n"
          + "    <l>\n"
          + "    <exa east wall>\n"
          + "    <exa ivy>\n"
          + "    <exa opening>\n"
          + "    <se>\n\n"
          + "There are other, fun things to <exa> here though. :-)\n");

        return 1;
    }

    write("Sure, here's a hint. The concept of deeper room descriptions"
      + " means that you should examine more than just the things you"
      + " see in the main room description. Also examine what you find"
      + " when you examine something. Here's an example:\n\n"
      + "    <l>\n"
      + "    This room has a fern in it.\n"
      + "    <exa fern>\n"
      + "    There is a strange liquid beneath the fern.\n"
      + "    <exa liquid>\n"
      + "    You find a gold coin in the liquid!\n\n"
      + "That was nothing more than an example, of course. In this room"
      + " you might start by examining the east wall. If you still need"
      + " more help, you can type <hint full>.\n");

    return 1;
} /* hint */
