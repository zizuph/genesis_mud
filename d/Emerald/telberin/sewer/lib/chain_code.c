/*
 *  /d/Emerald/telberin/sewer/lib/chain_code.c
 * 
 *  This module contains code to include in rooms which have
 *  the sewer alcoves.
 * 
 *  Copyright (c) October 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types 

#include <macros.h>
#include <ss_types.h>


/* prototypes */
public int        pull_chain(string arg);
public int        check_chain();
public int        release_chain(string arg);
public string     search_chain();
public void       add_chain_actions();

/* global variables */
public mixed      Holding_Chain = 0;   /* who is holding the chain? */

/* definitions */
#define           NEEDED_STR      30     /* str needed to pull chain */

/*
 * Function name:        pull_chain
 * Description  :        allow players to try to pull the grate open
 *                       to allow passage into the sewer alcoves
 * Argunents    :        string arg - what the player typed
 * Returns      :        int: 1 - success, 0 - failure
 */
public int
pull_chain(string arg)
{
    int     chain_str = NEEDED_STR + random(20);

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [heavy] [iron] 'chain'"))
    {
        return 0; /* can't parse player syntax */
    }

    if (Holding_Chain)
    {
        write(QCTNAME(Holding_Chain) + " has already pulled the"
          + " chain from the slot, and is straining to hold it"
          + " in place.\n");
        return 1;
    }

    if (this_player()->query_stat(SS_STR) < chain_str)
    {
        write("You lift the heavy iron chain and struggle to pull"
          + " it from the slot. Your muscles burn and sweat"
          + " drenches your body, and you soon give up.\n");
        return 1;
    }

    write("You lift the heavy iron chain, and pull. Your muscles"
      + " tense as you ply against resistance offered from something"
      + " beyond the slot which is housing the chain. You hear a"
      + " grinding of gears as extra links of the chain slowly"
      + " begin to emerge from the wall. As you pull, you see"
      + " the grating which is covering the culvert in the wall"
      + " rise and disappear behind the bricks.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " lifts the"
      + " heavy chain and pulls on it. As additional length of its"
      + " bulk emerge from a slot in the wall, you see the grating"
      + " which is covering the culvert in the wall rise and"
      + " disappear behind the bricks.\n", this_player());

    Holding_Chain = this_player();
    return 1;
} /* pull_chain */


/*
 * Function name:        check_chain
 * Description  :        a check to perform in rooms which have the
 *                       culvert as players use exits. If they are
 *                       holding the chain, prevent them from leaving
 *                       until they let go.
 * Returns      :        int: 1 - cannot use exit, 0 - may use exit
 */
public int
check_chain()
{
    if (Holding_Chain == this_player())
    {
        write("You must release the chain before travelling onward.\n");
        return 1;
    }

    return 0;
} /* check_chain */


/*
 * Function name:        release_chain
 * Description  :        allow players to release the chain
 * Arguments    :        string arg - what the player typed
 * Returns      :        int: 1 - success, 0 - failure
 */
public int
release_chain(string arg)
{
    if (!Holding_Chain || Holding_Chain != this_player())
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "'[go] [of] [the] [heavy] [iron] 'chain'"))
    {
        write("As you release your grip, the iron chain is pulled from"
          + " your hands and much of its length recedes back into"
          + " the slot in the wall. The iron grating falls shut, once"
          + " again barring access to the culvert.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " releases"
          + " the iron chain, which recedes back into the slot in"
          + " the wall. The iron grating falls shut, once again"
          + " barring access to the culvert.\n", this_player());

        Holding_Chain = 0;
        return 1;
    }

    return 0; /* can't parse syntax */
} /* release_chain */


/*
 * Function name:        search_chain
 * Description  :        allow players to search the chain
 * Returns      :        a description for players who search the chain
 */
public string
search_chain()
{
    return "You fiddle around with the chain a bit, and discover that"
      + " it appears to be connected to some sort of mechanism within"
      + " the wall. It hangs somewhat loosely in its slot, as if it"
      + " were meant to be manipulated.\n";
} /* search_chain */


/*
 * Function name:        add_chain_actions
 * Description  :        some actions to put into the init() function
 *                       of rooms with the chain in them.
 */
public void
add_chain_actions()
{
    add_action(pull_chain, "pull");
    add_action(pull_chain, "manipulate");
    add_action(release_chain, "let");
    add_action(release_chain, "drop");
    add_action(release_chain, "release");
} /* add_chain_commands */

