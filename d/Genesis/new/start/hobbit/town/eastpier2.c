/*
 * File         : /d/Genesis/start/hobbit/town/eastpier2.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/28/99
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
object Seagull;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("the east pier");
    set_long(
      "The plankpier rests on sturdy poles a bit out in the water. The " +
      "pond is calm and the surface only breaks when ships passes with " +
      "cargo and passangers to and from foreign lands. A small shed " +
      "north of here has been made looking official with a sign in the " +
      "roof.\n");
    add_item("shed", 
      "The shed is almost falling apart but seems used for an " +
      "official purpose. It has a sign on the roof. \n");
    add_item("sign", 
      "The sign on the roof of the shed reads: \"Shipping office\" \n");
    add_item(({ "smell", "fish", "saltwater", "tar" }), 
      "The smell here is a mix of fish, saltwater and tar. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/28/99.\n");
    
    add_exit("shippingoffice.c", "north");
    add_exit("eastpier3.c", "southeast");
    add_exit("eastpier1.c", "west");
    
    
    add_prop(HOBBIT_SL_S_SEAGULL_LP,({"on top of a pole", 
                                      "on the water", 
                                      "on the pier"}));
    
    
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
    if (!objectp(Seagull) && (random(3) == 0))
    {
        Seagull = clone_object(EX_MON + "seagull");
        Seagull->move(this_object(), 1);
        
        // Set up flying
        Seagull->grid_set_size(7, 4);  // How big is the grided are?
        Seagull->grid_set_pos(6, 4);   // Where are we in it?
        tell_room(TO, QCTNAME(Seagull) + 
            " takes off from the surface of the water.\n");
    }
    
}



