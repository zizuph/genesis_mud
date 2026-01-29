/*
 *  /d/Sparkle/area/tutorial/castle/plateau.c
 *
 *  This is the plateau on which Krolock's castle has been built.
 *  From here, the player can enter the castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();
public void        describe(string arg);
public void        climb_down();
public void        init();
public int         do_climb(string arg);
public int         do_untie(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("atop a plateau before a dark castle");
    set_long(&describe("long"));

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "castle", "dark castle", "ominous castle",
                 "dark and ominous castle" }),
        "The castle to the west can only be the abode of Baron von"
      + " Krolock, the scourge of Silverdell himself. It is built of"
      + " dark stone, which rises like a shadow from the flat of the"
      + " plateau. A spirit of evil and malevolence emanates from the" 
      + " structure, reaching out to you with its influence.\n");
    add_item( ({ "plateau" }),
        "This plateau stretches for a long distance to the west, where"
      + " the castle of Baron von Krolock has been erected on its"
      + " surface.\n");
    add_item( ({ "mountain", "mountains" }),
        "This plateau is really a part of the foothills of the"
      + " mountains, whose first peaks are visible rising directly"
      + " to the west, behind the castle.\n");
    add_item( ({ "slope", "slopes", "peak", "peaks" }),
        "The mountain peaks are tall and forboding.\n");
    add_item( ({ "boulder", "boulders", "hook", "rope", "knot",
                 "grappling hook" }), &describe("rope"));

    add_exit("portcullis", "west");
    add_exit(CLIFFS_DIR + "cliffroad_6", "down", climb_down, 5, 1);

    //This room is instanced.
    instance_entrance = 0;
} /* create_silverdell */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant description of
 *                       something
 * Arguments    :        string arg - what we are describing
 * Returns      :        string - the description
 */
public string
describe(string arg)
{
    string  txt = "You stand before a dark and ominous castle atop this"
      + " plateau in the cliffs. Behind the castle, the mountains"
      + " continue to dominate the horizon to the west, their tall"
      + " slopes frowning down over the area. ";

    switch(arg)
    {
        case "long":
            if (CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
            {
                txt += "Your grappling hook dangles over the edge"
                  + " of the cliff.";
            }

            return txt + "\n";
            break;
        case "rope":
            if (CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
            {
                return "Your grappling hook remains tied to the boulder"
                  + " and hangs down over the cliff.\n";
            }
            break;
    }
} /* describe */


/*
 * Function name:        climb_down
 * Description  :        provide a bit of text when the player uses
 *                       the "down" exit.
 */
public void
climb_down()
{
    write("You work your way down the steep cliff face, finding it"
      + " vastly easier to manage than the climb up.\n");

    return;
} /* climb_down */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_untie, "untie");
    add_action(do_untie, "get");
    add_action(do_untie, "take");
    add_action(do_untie, "remove");
    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:        do_climb
 * Description  :        allow the player to climb down the slope
 * Arguments    :        what the player typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [from] [over] [the] 'cliff' / 'slope'"
      + " / 'cliffs' / 'plateau'") &&
        !parse_command(arg, ({}),
        "'down' [from] [the] [cliff] [cliffs] [slope] [plateau]"))
    {
        return 0; /* bad or unexpected syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player down here using"
          + " command. Since you are a wizard that won't work."
          + " Simply type <down> instead.\n");
        return 1;
    }

    this_player()->command("$d");
    return 1;
} /* do_climb */


/*
 * Function name:        do_untie
 * Description  :        allow players to try to untie the rope, but
 *                       don't let them do it
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
do_untie(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb() + " what?\n"));
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [grappling] 'hook' / 'rope' / 'knot' [from] [the]"
      + " [boulder]"))
    {
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
    {
        write("You did such a good job with the knot, that you can't"
          + " budge it!\n");
        return 1;
    }

    return 0;
} /* do_untie */
