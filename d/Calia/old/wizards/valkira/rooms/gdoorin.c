/* CALIA: DOOR - Garden door into Valsroom (/d/Calia/valkira.gdoorout.c)
Date      Coder      Action	Note
-------- ----------- ---------  ----------------------
9/05/99  Valkira     Created    Based on Zima's belltower door
                                (/d/Calia/clubs/mclub/rooms/bdoorin.c) */

       
// INCLUSIONS AND DEFINITIONS

inherit "/std/door";

#include "/d/Calia/domain.h"           /* Default include file for Calia      */

#include <stdproperties.h>             /* ( /sys/stdproperties.h ) This file
                                          holds definition of all the standard
                                          properties that an object can have.
                                          The documentation for the properties
                                          can all be found in the directory
                                           /doc/man/properties              */
// #include "defs.h"

#define VALKIRA             "/d/Calia/valkira/"
#define ROOMS               "/d/Calia/valkira/rooms/"
#define GARDEN_DOOR_ID      "_valsroom_garden_door_id"
#define VKEY_NUM      830912
    
void create_door() {
    ::create_door();
    set_other_room(ROOMS+"valsroom");
    set_door_id(GARDEN_DOOR_ID);
    set_door_desc("It is a door from the garden into Valkira's room.\n");
    set_door_name("door");
    set_open(0);  /* closed initially */
    set_locked(1); /* locked initially */
    set_no_pick(); /* not pickable */
    set_open_desc("The front door is open leading to the garden.\n");
    set_open_desc("There is an opened door leading to the garden.\n");
    set_pass_command(({"front","door"}));
    set_fail_pass("The front door is closed.\n");
    set_open_mess(({"opens the front door.\n",
                    "The front door swings open to the garden.\n"}));
    set_fail_open(({"The front door is already opened.\n",
                    "The front door is locked.\n"}));
    set_close_mess(({"closes the garden door.\n",
                     "The front door swings shut to the garden.\n"}));
    set_fail_close("The front is already closed.\n");
    set_lock_command("lock");
    set_lock_name(({"lock","metal lock"}));
    set_lock_desc("It is an metal lock on the front door.\n");
    set_lock_mess(({"locks the front oak door with a copper key.\n",
                    "The metal lock on the heavy oak door clicks.\n"}));
    set_fail_lock(({"The front door is already locked.\n",
                    "The front door is not closed.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the front door with a copper key.\n",
                      "The metal lock on the front door clicks.\n"}));
    set_fail_unlock("The front door is not locked.");
    set_key(VKEY_NUM);

}

