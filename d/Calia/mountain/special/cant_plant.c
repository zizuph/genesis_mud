// INHERIT FILE:  Prevents planting of seeds in most palace garden rooms.

    /*  Calia Domain

    HISTORY

    [96-01-22] Created by Uhclem from [C:\CALIA\MOUNTAIN\SPECIAL\CANT_PLA.DOC].

    PURPOSE

    Only one room in the palace gardens is available to mortals for the
    planting-seed portion of the garden quest.  This file contains a function
    to prevent planting seeds in other rooms and is inherited from <crdefs.h>
    as CANT-PLANT-HERE.  */

// FUNCTIONS

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    add_action("plant_seed", "plant");
    return;
    }

// plant_seed

/*

Purpose:  Prevent player from planting a seed.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
plant_seed(string str)

    {

    object tp = this_player();
    object seed = present("seed", tp);

    /*  Next statement ensures that variable str contains string data to avoid
        type mismatch if player enters "break" with no argument.  */

    if(!stringp(str)) str = " ";

    if(!wildmatch("*seed", str))

        {

        write("Plant what?\n");
        return 1;

        }

    if(!objectp(seed))

        {

        write("You don't seem to have any seeds to plant.\n");
        return 1;

        }

    else

        {

        write("You look around carefully, but you can't find " +
            "any good places in this area to plant the seed.\n");

        return 1;

        }

    }
