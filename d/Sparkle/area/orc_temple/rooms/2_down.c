/*
 *  /d/Sparkle/area/orc_temple/1_down.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
#include <language.h>
#include <macros.h>
#include <time.h>

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public void         init();
public string       exit_blocked_hook(object guard);
public int          climb_down_stair_hook();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("near some stairs at the end of a short corridor");
    set_long("A short corridor comes to a halt before stairs leading"
      + " down here. To the south, an east-west hallway is visible"
      + " in the dim torchlight. The smell here hits your nose like"
      + " a sledgehammer!\n\n");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "crumbled stair", "crumbled stairs",
                 "crumbled step", "crumbled steps",
                 "set of stairs", "set of crumbled stairs",
                 "long set of stairs",
                 "long set", "set",
                 "long set of crumbled stairs",
                 "stairway" }),
        "Crumbled stairs lead down into darkness below.\n");
    add_item( ({ "darkness", "darkness below", "below" }),
        "Well ... you'll have to do the whole walking thing to"
      + " discover more.\n");
    add_item( ({ "walking", "walking thing" }),
        "I know ... it's a lot to ask, but you can do it.\n");
    add_item( ({ "corridor", "short corridor", "tunnel", "passage" }),
        "The passage comes up short right before the stairs here.\n");
    add_item( ({ "north wall" }),
        "It is distinguished by the fact that stairs lead down"
      + " right in the middle of its length.\n");
    add_item( ({ "south", "hall", "hallway", "east-west hallway" }),
        "It is off to the south. You'd need to head that way for a"
      + " closer look.\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like you are stuck inside"
      + " the buttocks of a rhynocerous who died a week ago -"
      + " from dysentery!\n");
    try_item( ({ "sledgehammer" }),
        "Good Gods ... the reek!\n");
    try_item( ({ "reek" }),
        "One has to wonder if these orcs really do have noses, or if"
      + " those holes between their eyes and mouths are just a place"
      + " to put their fingers.\n");

    add_dungeon_items();

    add_exit("2_hall10", "south");
    add_exit("3_up", "down", climb_down_stair_hook, 1, 0);

    set_stair_climb("down");

    add_npc(NPC_DIR + "goblin_warrior", 5, &->arm_me());

    set_no_exit_msg( ({ "northeast", "southeast", "southwest", "east",
                        "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
    set_no_exit_msg( ({ "north" }),
        "A stairway is to the north. Do you want to climb down it?\n");

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */


/*
 * Function name:        exit_blocked_hook
 * Description  :        provide a message that can be customized
 *                       when an npc blocks the path moving in a given
 *                       direction in the dungeons.
 * Arguments    :        object guard - the npc blocking the path
 * Returns      :        string - the message
 */
public string
exit_blocked_hook(object guard)
{
    return capitalize(LANG_ADDART(guard->short()))
      + " steps in front of you as you head toward the stairs and"
      + " smiles grotesquely. He clearly will not let you pass.\n";
} /* exit_blocked_hook */


/*
 * Function name:        climb_down_stair_hook
 * Description  :        message to print to the player when they
 *                       climb down some stairs
 * Returns      :        int 1  - if guarded
 *                       int 0  - if not guarded
 *
 * Masking this for logging purposes
 */
public int
climb_down_stair_hook()
{
    int    blocked = ::climb_down_stair_hook();

#if LOG_MOVES
    if (!blocked)
    {
        write_file(LOG_DIR + "moves", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " moved down to LEVEL-3.\n");

        TELL_G(capitalize(this_player()->query_name()) + " moved down to"
          + " LEVEL-3!");
    }
#endif

    return blocked;
} /* climb_down_stair_hook */