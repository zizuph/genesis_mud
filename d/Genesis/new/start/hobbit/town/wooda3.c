/*
 * File         : /d/Genesis/start/hobbit/town/wooda3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/27/99
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
string local_m_in_message();


/* globals */


/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("a dark wood");
    set_long(
      "Dark trees surrounds this place in all directions with straggling " +
      "branches covered by needles all the way from the ground up to " +
      "the top. The soft moisty black soil feeds only a few shrubs and " +
      "vegetables not needing too much light. A windling path can be " +
      "seen westwards.\n");
    
    add_prop(ROOM_S_EXIT_FROM_DESC, local_m_in_message);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("wooda4.c", "east");
    add_exit("woodb3.c", "south");
    add_exit("woodb4.c", "southeast");
    add_exit("woodpath4.c", "southwest");
    add_exit("woodpath3.c", "west");
    
    
    
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

/*
 * Function name:       local_m_in_message
 * Description  :       special message leaving this area
 * Comment      :       This piece of code is a donation from Mercade.
 */
string
local_m_in_message()
{
    return ((query_verb() == "west") ? "from the forest." : 0);
}


