/*
 * File:    
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("");
    set_long("");


    WIZINFO("This is wizard info for the monks room.\n");

    // where, command
    add_exit("WHERE", "command");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("DIRECTION", "MESSAGE.\n");
}

