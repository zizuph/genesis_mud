/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * /d/Genesis/race/elf_std.c
 *
 * This is the race object used for players of race Elf.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/race/generic";

/*
 * Function name: query_race
 * Description  : Returns the *true* race of this player. 
 * Returns      : string "elf" - always.
 */
nomask string
query_race()
{
    return "elf";
}

