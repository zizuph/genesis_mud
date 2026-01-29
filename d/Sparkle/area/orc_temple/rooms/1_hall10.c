/*
 *  /d/Sparkle/area/orc_temple/1_hall10.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>    /* for QCTNAME */
#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public int          do_smell(string arg);
public void         init();
public string       exit_blocked_hook(object guard);


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("beneath an archway in a narrow tunnel");
    set_long("A narrow tunnel travels north and south here, passing"
      + " beneath an archway that creates an intentional checkpoint"
      + " in the corridor. To the south, the corridor rounds a"
      + " bend. North of here, a dark opening is visible at the"
      + " end of the passage. The smell here is simply horrific.\n\n");

    try_item( ({ "tunnel", "narrow tunnel", "passage",
                 "corridor", "here" }),
        "This passage seems narrower than the other tunnels down"
      + " here.\n");
    try_item( ({ "arch", "archway", "crumbled archway",
                 "crude archway", "crude arch", "crumbled arch" }),
        "A crumbled arch extends over a checkpoint in the tunnel."
      + " Its sides are crumbled and it is very crudely constructed.\n");
    try_item( ({ "bend", "bend in the corridor", "turn", "corner" }),
        "The corridor rounds a bend south of here, turning east to"
      + " travel to another area of the dungeon.\n");
    try_item( ({ "smell", "truly dreadful smell", "dreadful smell" }),
        "This is the sort of smell one might encounter by"
      + " hanging around the morgue on a hot summer's day. Pleasant, it"
      + " is not. It seems to be getting worse here!\n");
    try_item( ({ "checkpoint", "intentional checkpoint" }),
        "The narrow width of the corridor combined with the protrusion"
      + " of the archway create an easily guarded checkpoint for the"
      + " orcs who seem to like to hang around down here.\n");
    try_item( ({ "opening", "dark opening", "end of the passage",
                 "end" }),
        "You'd have to head north to get a better look.\n");


    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 5 + (random(3)), &->arm_me());

    add_exit("1_down", "north", check_exit, 1, 0);
    add_exit("1_hall9", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest", "east",
                        "northwest", "west" }),
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
      + " baked in ... bile and ... fried in ... oh, it's just bad!\n");
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
    return "The " + guard->short() + " stands squarely in the archway"
      + " and shouts: Not pass! Not you!\n";
} /* exit_blocked_hook */