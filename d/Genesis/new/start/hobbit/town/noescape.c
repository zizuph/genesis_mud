/*
 * File         : /d/Genesis/start/hobbit/town/noescape.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/19/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * 
 * TODO         :
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
    set_short("An empty place");
    set_long(
      "This an empty place with no escapes. The bare ground looks dead, " +
      "the sky is blue and the sun burns hot above all. A lot of things " +
      "need to be fixed by the wizards to make this place exciting, but " +
      "they seems busy with other things right now.\n");
    add_item("ground", 
      "The ground seems very hard. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/19/99.\n");

    reset_room();
}

/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{    
}
