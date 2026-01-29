/*
 * File         : /d/Genesis/start/hobbit/town/shippingoffice.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        In the shipping office a young and ambitious hobbit will assist
 *        you finding the right peer for your journey. He might even
 *        invite you to follow him to the right ship and is very polite.
 *        He will also handle package deliveries as well as some small
 *        tips for the travler. He could also manage delivery tours for
 *        the adventures newbie.
 * 
 * TODO         :
 *        Let NPC answer a few questions, Let NPC show player the way to
 *         the right boat Let NPC give player a pier-map Add delivery tour.
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
object Officer;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The shipping information office");
    set_long(
      "This small and worn down shelter has been furnitured to house a " +
      "small desk and a chair. Despite the poor outlook of the place it " +
      "is the central for the cargo traffic in this harbour as beeing " +
      "the shipping office.\n");
    add_item("ceiling", 
      "A lot of holes in the ceiling has been fixed with nailed " +
      "leather patches and tar. It doesn't look very professional. \n");
    add_item("chair", 
      "It is an arm less wooden chair with a stained leather seat \n");
    add_item("desk", 
      "It is an old worn down desk. \n");
    add_item("walls", 
      "The walls are made of planks almost falling apart \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the shipping office.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    add_exit("eastpier2.c", "south");
    
    
    
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
    if (!objectp(Officer))
    {
        Officer = clone_object(EX_MON + "officer");
        Officer->move(this_object(), 1);
        tell_room(TO, QCTNAME(Officer) + " arrives through the door.\n");
    }
    
}

void
init()
{
    ::init();
    
    // Check if the NPC is here and let him check the player
    if (Officer && present(Officer))
    {
        Officer->set_visitor(this_player());
    }
}


