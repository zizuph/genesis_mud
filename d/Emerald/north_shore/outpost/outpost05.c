/*
 *  /d/Emerald/north_shore/outpost/outpost05.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;


/*
 * Function name:    create_outpost_inside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_inside_room()
{
    set_short("a strange dug-out chamber within the outpost");
    set_em_long("This room is ghastly to behold. A number of dead"
      + " elven bodies are piled in the corner, presumably the"
      + " slain that have been recovered from the courtyard and"
      + " from outside the outpost in the recent raids. The stone"
      + " which forms the floor of the rest of the outpost has been"
      + " lifted here, and the earth dug up and then recovered. The"
      + " smell of death is heavy, and lessens in the direction of"
      + " the corridor to the northwest.\n");

    add_item( ({ "chamber", "strange chamber" }), long);
    add_item( ({ "body", "bodies", "dead", "the dead",
                 "dead bodies", "dead body", "dead elf",
                 "dead elves", "dead elven body", "dead elven bodies",
                 "pile", "pile of bodies", "elves", "elf" }),
        "These elves look recently slain, and have not yet begun to"
      + " decay. Things must be terrible here indeed for such hasty"
      + " and crude treatment of the dead to be taking place.\n");
    add_item( ({ "stone", "stone of the floor", "ground", "down",
                 "floor", "earth", "grave", "graves", "mass grave" }),
        "The stone of the floor has been torn away and piled in a"
      + " corner to allow for the dead to be buried here in a mass"
      + " grave. It seems that many have already been buried, as the"
      + " earth has been recovered recently. However, there is more"
      + " work to be done. The pile of bodies in the corner is"
      + " beginning to foul, and will soon need tending.\n");

    add_indoor_items();

    add_exit("outpost02" , "northwest");
} /* create_outpost_inside_room */


/*
 * Function name:        do_dig
 * Description  :        allow mortals to *try* to dig here
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_dig(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [up] [the] [dead] 'ground' / 'earth' / 'grave'"
      + " / 'bodies' / 'elves' / 'elf'"))
    {
        return 0; /* can't parse player syntax */
    }

    write("It is not your place to disturb this situation. These"
      + " elves will find proper burial in time. Either that, or they"
      + " will be forgotten.\n");
    return 1;
} /* do_dig */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dig, "dig");
    add_action(do_dig, "bury");
} /* init */
