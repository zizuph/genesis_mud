/*
 * File         : /d/Genesis/start/hobbit/town/livinghouse3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Wealthy house
 * 
 * TODO         :
 *        Add items of this house Make some stealable objects Add mamsell
 *         NPC's complaining agout thieves
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";



/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();

/* globals */


/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("");
    set_long(
      "\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the living house.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("villageroad4.c", "north");
    
    
    
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    
}



