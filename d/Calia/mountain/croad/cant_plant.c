// INCLUDE FILE:  a function to prevent the planting of seeds.

    /*  Calia Domain

    HISTORY

    [96-02-16] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\CANT_PLA.DOC].

    PURPOSE

    Only one room in the palace gardens is available to mortals for the
    planting-seed portion of the garden quest.  This file contains a function
    to prevent planting seeds in other rooms.  */

// FUNCTIONS

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
