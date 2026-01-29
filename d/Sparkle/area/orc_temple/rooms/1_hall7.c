/*
 *  /d/Sparkle/area/orc_temple/1_hall7.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
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
    set_short("in a long north-south corridor");
    set_long("This dank corridor heads a ways to the north where"
      + " it trails into the gloom. A short distance to the south, you"
      + " can vaguely make out a turn to the west. A faint, yet"
      + " dreadful smell is present here.\n\n");

    try_item( ({ "gloom" }),
        "Rhymes with tomb. Actually, feels the same, too.\n");
    try_item( ({ "turn", "turn to the west" }),
        "You'd have to head south for a clearer view.\n");
    try_item( ({ "dank corridor", "north-south corridor" }),
        "This corridor stretches on to the north and south.\n");
    try_item( ({ "smell", "faint smell", "dreadful smell",
                 "faint, yet dreadful smell" }),
        "This is the sort of smell one might encounter by"
      + " hanging around the morgue on a hot summer's day. Pleasant, it"
      + " is not.\n");
    
    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());

    add_exit("1_hall6", "north");
    add_exit("1_hall8", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest", "west", "east" }),
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

    write("Ugh! Something smells of ... cabbage boiled in ... oh, it's"
      + " just bad!\n");
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
