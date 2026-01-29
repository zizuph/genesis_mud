/*
 * File         : /d/Genesis/start/hobbit/town/store.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/17/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is the store room of the village shop. No mortals are
 *        allowed in this room. NOTE this code is based on the example
 *        /doc/examples/trade/store.c
 * 
 * TODO         :
 *         
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit "/lib/store_support";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */
#define BAG   "/d/Genesis/doc/examples/obj/bag"
#define TORCH "/d/Genesis/doc/examples/obj/torch"



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
    set_short("Store room of the village shop.");
    set_long(
      "This is the storage room of the shop in the hobbit start location " +
      "village.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the store.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/17/99.\n");
    
    add_exit("shop.c", "out");
    
    
     set_default_stock( ({ BAG, 1, TORCH, 4 }) );
    
     reset_store();
    
    
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
    reset_store();
    
}

/*
* You should always call store_update() if an object enters the store-
* room to update it and let it be added to the stock.
*/
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}


