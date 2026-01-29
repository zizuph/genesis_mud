/*
 *  /d/Sparkle/area/orc_temple/1_hall9.c
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
    set_short("rounding a bend in the corridor");
    set_long("The corridor winds around a bend here, heading north"
      + " down a stretch of tunnel that is filled with a truly"
      + " dreadful smell. East, the tunnel dissapears around the"
      + " bend.\n\n");

    try_item( ({ "gloom", "distant gloom" }),
        "You don't really see any here, but you sure can feel it.\n");
    try_item( ({ "stretch", "stretch of tunnel", "north" }),
        "North of here, the corridor smells like something even a dog"
      + " would bury and never dig up.\n");
    try_item( ({ "bend", "bend in the corridor", "turn", "corner" }),
        "You are standing at a bend in the corridor that heads either"
      + " north or east.\n");
    try_item( ({ "smell", "truly dreadful smell", "dreadful smell" }),
        "This is the sort of smell one might encounter by"
      + " hanging around the morgue on a hot summer's day. Pleasant, it"
      + " is not.\n");

    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 4 + (random(3)), &->arm_me());

    add_exit("1_hall10", "north");
    add_exit("1_hall8", "east");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest", "south", "west" }),
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
      + " baked in ... bile and ... oh, it's just bad!\n");
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
