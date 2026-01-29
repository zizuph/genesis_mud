/*
 * File         : /d/Genesis/start/hobbit/town/warehouse1.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        A filthy warehouse. The owner has moved out and it seems that he
 *        has forgotten to deliver the last barrels of fish still standing
 *        here.
 * 
 * TODO         :
 *        * - Add some sellable objects to be searched for, * - Add rodent
 *         NPC's running around on the floor
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
    set_short("A filthy warehouse");
    set_long(
      "A smell of rotten fish lies in the air in this warehouse. Just a " +
      "few barrels are stored here and they seems not to have been " +
      "moved for quite some time. The floor is a mess filled with " +
      "wrecked goods and empty crates.\n");
    add_item(({ "barrel", "barrels" }), 
      "A few half-wrecked barrels are still in this warehouse. \n");
    add_item("ceiling", 
      "The inside of a wrecked reed roof has not protected the goods " +
      "especially well. \n");
    add_item(({ "container", "containers" }), 
      "A few barrels is all what is left of the goods in this " +
      "warehouse. \n");
    add_item("floor", 
      "The plank floor is dusty and filled of remains of rodents. \n");
    add_item(({ "label", "labels" }), 
      "The barrels has a label which tells about originator and " +
      "destination as well as contents \n");
    add_item(({ "seal", "seals" }), 
      "The seal has been broken. \n");
    add_item("sign", 
      "The wax-seals are all broken so the sign can not be read. \n");
    add_item("smell", 
      "A dense smell of rotten fish fills the room. \n");
    add_item("walls", 
      "Sturdy timber walls keeps up what is left of the roof. \n");
    add_item(({ "wax-seal", "wax-seals" }), 
      "The wax-seals are all broken. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the warehouse.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("westpier5.c", "east");
    
    
    
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



