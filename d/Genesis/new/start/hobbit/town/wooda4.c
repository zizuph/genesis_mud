/*
 * File         : /d/Genesis/start/hobbit/town/wooda4.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/11/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * 
 * TODO         :

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
    set_short("a dense wood");
    set_long(
      "Dark trees surrounds this place in all directions with thick " +
      "branches covered by needles all the way from the ground up to " +
      "the top. The soft moisty black soil feeds only a few shrubs and " +
      "vegetables not needing too much light.\n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/11/99.\n");
    
    add_exit("woodb4.c", "south");
    add_exit("woodb3.c", "southwest");
    add_exit("wooda3.c", "west");
    
    
    
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



