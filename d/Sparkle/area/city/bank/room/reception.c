/*
 * /d/Sparkle/area/city/bank/room/reception.c
 *
 * This is the reception room for the second floor of the main branch
 * of the Gnomes of Genesis in Sparkle.
 *
 * Created Feb 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard";

/* Prototypes */


/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    set_short("Office reception room");
    set_long("Office reception room of the Gnomes of Genesis.\n\n");

    /* Exits */
    add_exit(BANK_ROOM + "office_n", "north", 0);
    add_exit(BANK_ROOM + "guard_room", "northwest", 0);
    add_exit(BANK_ROOM + "office_w", "west", 0);
    add_exit(BANK_ROOM + "elevator", "southeast", 0);    

    
} /* create_bank_room */