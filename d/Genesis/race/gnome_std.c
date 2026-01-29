/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * /d/Genesis/race/gnome_std.c
 *
 * This is the object used for players of race Gnome.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/race/generic";

/*
 * Function name: query_race
 * Description  : Returns the "true" race name of this player.
 * Returns      : string "gnome" - always.
 */
nomask string
query_race()
{
    return "gnome";
}

