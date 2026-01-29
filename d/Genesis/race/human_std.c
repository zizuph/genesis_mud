/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * /d/Genesis/race/human_std.c
 *
 * This is the race object used for players of race Human.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/race/generic";

/*
 * Function name: query_race
 * Description  : Returns the "true" race of this player.
 * Returns      : string "human" - always.
 */
nomask string
query_race()
{
    return "human";
}
