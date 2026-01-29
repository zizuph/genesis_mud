/*
 *  /d/Emerald/blackwall/delrimmon/obj/rope.c
 *
 *  This coil of rope is your basic rope, but you can also
 *  tie it to things in Emerald.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 *
 *  USAGE:
 *
 *  This object is set up to respond to a function,
 *
 *      query_rope_tie();
 *
 *  which can be added to room code. If you want to make it
 *  so that this rope will recognize, and allow players to
 *  tie it to things in your rooms, I suggest doing something
 *  like this, either in the rooms, or in the inheriting
 *  files. If you want to have this rope used with special
 *  code in your room, have the room include the following
 *  line in the create function:
 *
 *      add_name("_emerald_rope_tie");
 *
 *  EXAMPLE:
 *
 *  inherit "/d/Emerald/std/room";
 *
 *  public mixed  *Rope_Ties;
 *
 *  public void    set_rope_tie(mixed m) { Rope_Ties = m; }
 *  public mixed   query_rope_tie() { return Rope_Ties; }
 *
 *  public void
 *  create_emerald_room()
 *  {
 *      set_short("some room");
 *      set_long("This is some room in Emerald. There is"
 *        + " a tree nearby, next to a boulder.\n");
 *
 *      add_item( ({ "tree" }),
 *          "There is a tree here.\n");
 *      add_item( ({ "boulder" }),
 *          "There is a boulder here.\n");
 *
 *      set_rope_tie( ({ "tree", "boulder" }) );
 *  }
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

/* prototypes */
public void        create_object;
public mixed       short_describe();
public mixed       long_describe();
public mixed       get_rope();
public int         do_tie(string arg);
public int         do_untie(string arg);
public int         do_pull(string arg);
public void        init();

/* global variables */
public mixed      Tied_To;  /* what is the rope tied to? */

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("rope");
    add_name("coil");
    add_adj( ({ "long", "coil", "of" }) );

    set_short(short_describe);
    set_long(long_describe);

    add_prop(OBJ_M_NO_GET, get_rope);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 200);

    setuid();
    seteuid(getuid());
}


/*
 * Function name:        short_describe
 * Description  :        determine the ropes short description
 * Returns      :        mixed - the short description
 */
public mixed
short_describe()
{
    if (!Tied_To)
    {
        return "coil of rope";
    }

    return "coil of rope, tied to a nearby " + Tied_To;
} /* short_describe */


/*
 * Function name:        long_describe
 * Description  :        determine the ropes long description
 * Returns      :        mixed - the long description
 */
public mixed
long_describe()
{
    string desc;

    desc = "This long coil of rope is finely woven from"
      + " amber threads by artisans of Telberin. Though thin,"
      + " it is incredibly strong and uncoils to a length of"
      + " about fifty feet.";

    if (!Tied_To)
    {
        return desc + "\n";
    }

    return desc + " It is tied to a nearby " + Tied_To + ".\n";
} /* long_describe */


/*
 * Function name:        get_rope
 * Description  :        if it is tied to something you need to
 *                       untie it first.
 * Returns      :        mixed, 0 - not tied, msg - if tied
 */
public mixed
get_rope()
{
    if (!Tied_To)
    {
        return 0; /* players can pick it up */
    }

    return "You would have to untie it from the " + Tied_To
         + " first.\n";
} /* get_rope */


/*
 * Function name:        do_tie
 * Description  :        allow the player to try to tie the rope
 *                       to things. Currently, lets just allow
 *                       trees.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - succes, 0 - otherwise
 */
public int
do_tie(string arg)
{
    mixed    rope_tied;

    if (!strlen(arg))
    {
        notify_fail("Tie what?\n");
        return 0;
    }

    if (arg == "rope")
    {
        notify_fail("What do you want to tie the rope to?\n");
        return 0;
    }

    if (environment(this_player())->id("_emerald_rope_tie"))
    {
        return 0; /* let the room take it from here */
    }

    rope_tied = environment(this_player())->query_rope_tie();

    if (parse_command(arg, ({}),
        "[the] [long] [coil] [of] 'rope' 'to' [the]"
      + " [large] [tall] %p", rope_tied))
    {
        Tied_To = rope_tied[0];

        write("You tie the rope to the " + Tied_To + ".\n");
        this_object()->move(environment(this_player()));

        return 1;
    }

    notify_fail("You aren't able to tie it to that.\n");
    return 0;
} /* do_tie */


/*
 * Function name:        do_untie
 * Description  :        allow players to untie the rope
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_untie(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Untie what?\n");
        return 0;
    }

    if (arg == "rope" ||
        parse_command(arg, ({}),
            "[coil] [of] 'rope' [from] [" + Tied_To + "]"))
    {
        write("You untie the rope from the " + Tied_To
          + ". It loops into a coil on the ground.\n");
        Tied_To = 0;

        return 1;
    }

    return 0; /* can't parse syntax */
} /* do_untie */


/*
 * Function name:        do_pull
 * Description  :        allow playeres to try to pull the
 *                       object the rope is tied to
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_pull(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[the] [coil] [of] 'rope'") ||
        parse_command(arg, ({}),
        "[the] '" + Tied_To + "'"))
    {
        if (!Tied_To)
        {
            notify_fail("The rope isn't tied to anything, so"
              + " that seems a bit pointless.\n");
            return 0;
        }

        write("You heave with all your might on the rope, but"
          + " the " + Tied_To + " doesn't budge.\n");

        return 1;
    }

    return 0; /* can't parse syntax */
} /* do_pull */


/*
 * Function name:        init()
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_tie, "tie");
    add_action(do_untie, "untie");
    add_action(do_pull, "pull");
    add_action(do_pull, "drag");
} /* init */
