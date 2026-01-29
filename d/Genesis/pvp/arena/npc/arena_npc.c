/*
 *  /d/Genesis/pvp/arena/npc/arena_npc.c
 *
 *  The base file for all npcs in the Pvp Arena.
 *
 *  Created May 2014, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include "../../defs.h"


/* Global Variables */
public int         Monster_Number;

/* Prototypes */
public void        create_monster();
public void        create_arena_monster();

public int         query_monster_number() { return Monster_Number; }


/*
 * Function name:        create_monster
 * Description  :        the constructor
 */
public void
create_monster()
{
    setuid();
    seteuid(getuid());

    create_arena_monster();

    Monster_Number = CONTROL_ROOM->get_monster_number();

    set_short("monster " + Monster_Number);
    set_long("This is " + short() + ".\n");
} /* create_monster */


/*
 * Function name:        create_arena_monster
 * Description  :        dummy routine to be redefined as needed
 */
public void
create_arena_monster()
{
} /* create_arena_monster */


/*
 * Function name:        do_travel
 * Description  :        have this monster move toward the Keep
 */
public void
do_travel()
{
    string  action = environment(this_object())->query_assault_move();
    string  loc = environment(this_object())->query_room_position();

    if (!strlen(action))
    {
        TELL_G("action = " + action);
        action = "say Looks like a good place to stop.";
        CONTROL_ROOM->arena_alert("moves", Monster_Number + " stops in "
          + loc);
    }
    else
    {
        CONTROL_ROOM->arena_alert("moves",
            Monster_Number + " moves from " + loc + " " + action);
    }

    command(action);
} /* do_travel */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    set_alarm(3.0, 0.0, do_travel);

    ::enter_env(dest, old);
} /* enter_env */
