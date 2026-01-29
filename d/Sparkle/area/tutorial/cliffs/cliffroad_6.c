/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_6.c
 *
 *  The end of the climb along the path to Krolock's castle. Here,
 *  a player must have the grappling hook and be sufficiently
 *  skilled in climbing in order to progress to the top.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>    /* for QCTNAME */
#include <ss_types.h>  /* for SS_CLIMB */

/* definitions */
#define  NEEDED_SKILL        17  /* the necessary climbing skill */

/* prototypes */
public void        create_silverdell();
public string      describe(string arg);
public int         check_exit();
public void        init();
public int         do_climb(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("before a sheer cliff face");
    set_long(&describe("long"));

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "cliff", "sheer cliff", "face", "cliff face",
                 "sheer cliff face", "cliffs" }),
        "The cliff face which rises before you is almost vertical,"
      + " and looks as if it would be extremely difficult to"
      + " <climb> without a great deal of skill and perhaps even"
      + " equipment.\n");
    add_item( ({ "plateau", "castle" }),
        "The plateau is not visible from here, but you can see the"
      + " outline of its border along the top of the cliff face"
      + " which rises here.\n");
    add_item( ({ "rope", "hook", "grappling hook", "end",
                 "my rope", "end of my rope" }), &describe("rope"));

    add_exit("cliffroad_5", "southeast");
    add_exit(CASTLE_DIR + "outside_castle", "up", check_exit, 1, 1);

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
    string  txt = "The path comes to a halt at a sheer cliff face which"
      + " rises many hundreds of feet toward a plateau atop these"
      + " slopes. A path leads southeast, heading back down toward"
      + " lower ground. ";

    switch(arg)
    {
        case "long":
            if (CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
            {
                txt += "The end of your grappling hook is dangling"
                  + " down the cliff here.";
            }

            return txt + "\n";
            break;
        case "rope":
            if (CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
            {
                return "Your grappling hook is still hanging from"
                  + " above, making it quite easy for you to climb"
                  + " back up the cliff.\n";
            }
            break;
    }
} /* describe */


/*
 * Function name:        check_exit
 * Description  :        see if the player is allowed to travel this
 *                       direction
 * Returns      :        1 - don't allow, 0 - allow
 */
public int
check_exit()
{
    write("There is no obvious exit up. You might be able to try to"
      + " <climb> that direction, however.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
    add_action(do_climb, "scale");
} /* init */


/*
 * Function name:        do_climb
 * Description  :        allow the player to try to climb over the rocks
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    object  hook;
    string  destination = CASTLE_DIR + "plateau";

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [sheer] 'cliff' / 'cliffs' / 'up'") &&
        !parse_command(arg, ({}),
        "'up' [the] [sheer] [cliff] [face]"))
    {
        return 0; /* bad or unexpected syntax */
    }

    if (!CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
    {
        if (this_player()->query_skill(SS_CLIMB) < NEEDED_SKILL)
        {
            write("After a few vain attempts to gain a handhold, you"
              + " decide that you would need to train more in climbing"
              + " skill to attempt such a feat.\n");
            return 1;
        }

        if (!objectp(hook = present("_tutorial_hook", this_player())))
        {
            write("Even with your skill in climbing, you would need some"
              + " kind of equipment to scale this sheer cliff.\n");
            return 1;
        }

        if (hook->query_wielded() != this_player())
        {
            write("You'll need to wield the grappling hook to even"
              + " have a chance at scaling this cliff.\n");
            return 1;
        }
    }

    write("Using your grappling hook, you slowly work your way"
      + " up the sheer cliff face, and reach the plateau above.\n");

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        destination = CASTLE_DIR + "outside_castle";
    }

    //this_player()->move_living("M", destination, 1, 0);
    moveto("M", destination, 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " slings a grappling hook into some high rocks, and works "
      + this_player()->query_possessive() + " way up the cliff.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " scrambles over the lip of the plateau from below.\n",
        this_player());

    if (!CHECK_TUTORIAL_BIT(GRAPPLE_BIT))
    {
        write("\nYou tie your grappling hook around a nearby boulder,"
          + " and allow the end to drop down over the cliff.\n");
        SET_TUTORIAL_BIT(GRAPPLE_BIT);
        hook->remove_object();
    }

    this_player()->add_fatigue(-50);

    return 1;
} /* do_climb */

