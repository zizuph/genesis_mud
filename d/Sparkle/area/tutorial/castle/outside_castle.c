/*
 *  /d/Sparkle/area/tutorial/castle/outside_castle.c
 *
 *  This is the plateau on which Krolock's castle has been built.
 *  This is the room the player can access if the castle is
 *  destroyed.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();
public void        climb_down();
public void        init();
public int         do_climb(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("atop a plateau before the ruins of a castle");
    set_long("You stand before the ruins of what was once a dark"
      + " and ominous castle. Baron von Krolock is no more, and"
      + " these crumbled ruins are a final testament to your victory"
      + " over his evil influence. The plateau stretches out toward"
      + " the mountains to the west.\n\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "castle", "dark castle", "ominous castle",
                 "dark and ominous castle", "ruin", "ruins",
                 "crumbled ruin", "crumbled ruins", "rubble" }),
        "The once great castle now lies in ruins. The archway and"
      + " portcullis have been smashed and lie as nothing more than"
      + " rubble.\n");
    add_item( ({ "plateau" }),
        "This plateau stretches for a long distance to the west, where"
      + " the ruins of the castle are visible.\n");
    add_item( ({ "mountain", "mountains" }),
        "This plateau is really a part of the foothills of the"
      + " mountains, whose first peaks are visible rising directly"
      + " to the west, behind the ruins.\n");
    add_item( ({ "slope", "slopes", "peak", "peaks" }),
        "The mountain peaks are tall and majestic.\n");

    add_exit("portcullis_ash", "west");
    add_exit(CLIFFS_DIR + "cliffroad_6", "down", climb_down, 5, 1);

} /* create_silverdell */


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
