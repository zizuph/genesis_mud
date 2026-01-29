/*
 *  /d/Sparkle/area/orc_temple/1_hall8.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1. This room contains part of a quest. (Secret Door Quest)
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>    /* for QCTNAME */
#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public int          do_smell(string arg);
public void         init();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("rounding a bend in the corridor");
    set_long("The corridor takes a turn here. One could march north into"
      + " the distant gloom where the way fades from view. Just a short"
      + " distance to the west, another corner is visible. A dreadful"
      + " smell seems to be coming from that direction.\n\n");

    try_item( ({ "gloom", "distant gloom" }),
        "One would think someone might create a cheerful dungeon one of"
      + " these days.\n");
    try_item( ({ "way", "the way" }),
        "Do you really expect a description for everything? Well, here"
      + " you go. That's the WAY it is.\n");
    try_item( ({ "cheerful dungeon" }),
        "Today is not that day.\n");
    try_item( ({ "that day" }),
        "Don't get cheeky!\n");
    try_item( ({ "bend", "bend in the corridor", "turn", "corner" }),
        "You are standing at a bend in the corridor that heads either"
      + " north or west.\n");
    try_item( ({ "turn to the west", "corner to the west",
                 "another corner" }),
        "You'd have to head west for a clearer view.\n");
    try_item( ({ "direction", "that direction" }),
        "You know ... west ... over that way.\n");
    try_item( ({ "smell", "faint smell", "dreadful smell",
                 "faint, yet dreadful smell" }),
        "This is the sort of smell one might encounter by"
      + " hanging around the morgue on a hot summer's day. Pleasant, it"
      + " is not.\n");
    try_item( ({ "view" }),
        "To the north, at least, it looks a bit faded.\n");
    try_item( ({ "north view", "view to the north" }),
        "Yeah. Faded.\n");
    try_item( ({ "faded view" }),
        "Fade to black.\n");
    try_item( ({ "black", "fade to black" }),
        "Of course, one could fade to white, but that would require"
      + " fog, and there isn't any fog down here.\n");
    try_item( ({ "fog", "white", "fade to white" }),
        "Nope. Maybe try a swamp somewhere.\n");
    try_item( ({ "swamp" }),
        "Somewhere.\n");
    try_item( ({ "view of a wall", "wall view", "view of the wall" }),
        "You know ... this is a really nice wall.\n");
    try_item( ({ "nice wall", "really nice wall" }),
        "On second thought ... ugh. I mean look at it.\n");
    try_item( ({ "northeast view", "east view", "southeast view",
                 "south view", "southwest view", "northwest view",
                 "view to the northeast", "view to the east",
                 "view to the southeast", "view to the south",
                 "view to the southwest", "view to the northwest" }),
        "That would be the view of a wall. Fantastic.\n");
    try_item( ({ "view to the west", "west view" }),
        "Not quite so faded as the view to the north. Smells worse,"
      + " though!\n");

    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 4 + (random(3)), &->arm_me());

    add_exit("1_hall7", "north");
    add_exit("1_hall9", "west");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest", "south", "east" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/* 
 * Function name:        do_smell
 * Description  :        Let players sniff the air here
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - if no arg, 0 - if arg
 */
public int
do_smell(string arg)
{
    if (strlen(arg))
    {
        /* let the mudlib handle it */
        return 0;
    }

    write("Ugh! Something smells of ... cabbage boiled in ... blood ..."
      + " oh, it's just bad!\n");
    say(QCTNAME(this_player()) + " sniffs the air, and looks a bit"
      + " green.\n");

    return 1;
} /* do_smell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */
