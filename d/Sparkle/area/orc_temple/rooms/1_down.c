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
#include <time.h>
#include <macros.h>

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public void         init();
public int          do_smell(string arg);
public string       exit_blocked_hook(object guard);
public int          climb_down_stair_hook();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("near some stairs at the end of a long corridor");
    set_long("A long and narrow corridor ends here at the top of a"
      + " long set of crumbled stairs that lead down into a dark"
      + " opening in the north wall. South you can see the tunnel"
      + " passing beneath an archway. Oh ... the smell here is truly"
      + " god-forsaken!\n\n");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "crumbled stair", "crumbled stairs",
                 "crumbled step", "crumbled steps",
                 "set of stairs", "set of crumbled stairs",
                 "long set of stairs",
                 "long set", "set",
                 "long set of crumbled stairs",
                 "stairway" }),
        "The stairs lead down into darkness.\n");
    add_item( ({ "darkness" }),
        "It's the spooky kind.\n");
    add_item( ({ "deeper level", "deeper level of the dungeons" }),
        "If you are interested, let your feet do the walking ... or,"
      + " in this case, climbing.\n");
    add_item( ({ "long corridor", "narrow corridor",
                 "long and narrow corridor", "tunnel", "passage" }),
        "You seem to be at the end of the passage here. One could"
      + " climb down the stairs or head south.\n");
    add_item( ({ "opening", "dark opening" }),
        "These are the sorts of scenes that get drawn in children's"
      + " stories about dark and scary places.\n");
    add_item( ({ "north wall" }),
        "Just your typical north wall ... oh, except for that dark"
      + " opening leading downward. That part is different.\n");
    add_item( ({ "archway", "arch" }),
        "It is off to the south. You'd need to head that way for a"
      + " closer look.\n");
    try_item( ({ "smell", "truly dreadful smell", "dreadful smell" }),
        "This is the sort of smell one might encounter by"
      + " hanging around the morgue on a hot summer's day. Pleasant, it"
      + " is not, and it seems to be coming from the stairs!\n");

    add_dungeon_items();

    add_exit("1_hall10", "south");
    add_exit("2_up", "down", climb_down_stair_hook, 1, 0);

    set_stair_climb("down");

    add_npc(NPC_DIR + "goblin_warrior", 1, &->arm_me());

    set_no_exit_msg( ({ "northeast", "southeast", "southwest", "east",
                        "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
    set_no_exit_msg( ({ "north" }),
        "A stairway is to the north. Do you want to climb down it?\n");

    setuid();
    seteuid(getuid());
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
      + " baked in ... bile and ... fried in ... SHOE POLISH!!!\n");
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
    return "The " + guard->short() + " plants himself firmly before the"
      + " dark opening at the top of the stairs and grins at you with"
      + " an expression that clearly says - not while I live, you"
      + " don't!\n";
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
          + " moved down to LEVEL-2.\n");

        TELL_G(capitalize(this_player()->query_name()) + " moved down to"
          + " LEVEL-2!");
    }
#endif

    return blocked;
} /* climb_down_stair_hook */