/*
 * File:    
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;
inherit MONK_LIB + "help";

void
create_room ()
{
    set_short("council chamber");
    set_long("This is a small, windowless room with three small "
        + "desks against each of the north, east, and south walls. "
        + "On each of the desks lies a blue tallow candle, which, "
        + "aside from the dim light that passes through the "
        + "red curtain to the west, offers the only light in "
        + "the room.\nA wide doorway in the north wall leads into "
        + "a small room.\n");

    add_item(({"desk", "desks"}), 
        "Which one? Perhaps you should specify which wall "
        + "the desk you want to examine is on.\n");
    add_item(({"north desk","north wall"}),
        "On the north wall is desk much like the others, very "
        + "plain and simple. It is made of pine that has many "
        + "layers of beeswax rubbed in, giving the surface a "
        + "soft sheen that sets the wood aglow in the mellow "
        + "candlelight. A blue candle rests atop the desk.\n");
    add_item(({"south desk","south wall"}),
        "The desk on the south wall is much like the others, being "
        + "plain and simple. It is made of pine that has many "
        + "layers of beeswax rubbed in, giving the surface a "
        + "soft sheen that sets the wood aglow in the mellow "
        + "candlelight. A blue candle rests atop the desk.\n");
    add_item(({"east desk","east wall"}),
        "On the east wall, opposite the red curtain, is a desk "
        + "of simple construction. It is made of pine with many "
        + "layers of beeswax rubbed in, giving the surface a "
        + "soft sheen that sets the wood aglow in the mellow "
        + "candlelight. A blue candle rests atop the desk.\n");
    add_item(({"candle","blue candle", "candles", "blue candles"}),
        "There are three blue candes in this room. Each one "
        + "burns with a small yellow flame that casts a waver"
        + "ing light along the stone walls.\n");
    add_cmd_item(({"candle","blue candle"}), ({"light"}),
        "It is already lit.\n");
    add_cmd_item(({"candle","blue candle"}), ({"extinguish"}),
        "try as you might to extinguish the candle, its flame "
        + "tseems to have a will of its own.\n");
    WIZINFO("This is the council room of the monks guild, where "
        + "council members, elders, and approved wizards can issue council "
        + "commands.\n");

    // where, command
    add_exit("meeting", "west");
    add_exit("post_council", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("west", "You walk through the curtain into "
        + "the small, dimly-lit council room.\n");

    // clone the board here
    m_clone_here(MONKBOARDPRIV);


    // set up council help files
    read_help_dir(MONK_DOC + "council/");
    set_help_type (({ "council" }));
}

void
init()
{
    ::init();

    m_vote_init();    // this is a voting room
    m_council_init(); // initialize council functions

    add_action(_help, "help"); // help files
}

/*
 * Function name: prevent_enter
 * Description:   Check to see if the interactive trying
 *                to gain access to this room is
 *                authorized. Unauthorized access attempts
 *                are logged.
 * Arguments:     who - the player trying to enter
 * Returns:       1 if they are not authorized
 */
public nomask int
prevent_enter(object who)
{
    // security check: only council members or
    // authorized wizards may enter this room
    if(!m_query_council_or_elder(who, 1))
    {
        /*
        m_log(who->query_real_name() + " tried to gain access "
            + "to " + file_name(TO) + ", but was not "
            + "authorized.\n");
        */
        who->catch_tell("You may not enter there.\n");
        return 1;

    }

    return 0;
}



