/* 
 * The base indoor room for the Tower of Arms in Palanthas.
 * Mortis 09.2014
 */
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include CLOCKH

/* Inherit the Ansalon room */
inherit R_FILE
inherit TDIR + "smell_world";

#define CREATE "create_palan_room"
#define RESET  "reset_palan_room"

public void init();
public int do_smell(string arg);

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
    { return 1; }
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
    ITEM(({"marble", "rock", "stone"}), "The marble used for building in "
    + "Palanthas is translucent appearing almost white in the sun.\n");

    ITEM(({"floor", "floors", "ceiling", "wall", "walls"}), "The walls, "
    + "floor, and ceiling are covered in smooth, polished marble. "
    + "The surface is occasionally marred by chips and cracks.\n");

    ITEM(({"chip", "chips", "crack", "cracks", "damage", "granite"}), "Where "
    + "you find chips or cracks, you can see a hint of dark granite beneath. "
    + "Although beautiful, this appears to be a solidly built tower. You also "
    + "wonder what caused the damage.\n");
    
    /* CMD("area", "smell", "@@smell_world"); */
    
}

public void
init()
{
    ::init();  /* vitally important! never forget this line! */

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/
} /* init */


/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with */
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
     *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


    smell_world(this_player());
    return 1;
} /* do_smell */

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

