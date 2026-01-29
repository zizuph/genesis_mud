/*
 * File         : /d/Genesis/start/hobbit/town/warehouse2.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Almost empty warehouse with only some sack of grains standing in
 *        a corner.
 * 
 * TODO         :
 *        * - Add items of this warehouse, * - Add rodent NPC's and
 *         spiders running around on the floor
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
    set_short("A warehouse");
    set_long(
      "A dense cloud of flour dust hangs in the air showing shafts of " +
      "sunshine running through the air. A pile of sacks with grain has " +
      "been stacked in the middle of the warehouse\n");
    add_item("ceiling", 
      "The inside of the reed roof is tigthly put onto the wall to " +
      "keep the temprature. \n");
    add_item("floor", 
      "The plank floor is pretty worn due to the heavy traffic of " +
      "goods here. \n");
    add_item(({ "label", "labels" }), 
      "Most goods has a label which tells about originator and " +
      "destination as well as contents \n");
    add_item(({ "sack", "sacks" }), 
      "Many sacks of hemp filled with grains fills this warehouse. \n");
    add_item(({ "seal", "seals" }), 
      "Almost all containers are tightly closed and a wearing a " +
      "wax-seal to detect unauthorized access to the goods. \n");
    add_item("sign", 
      "A sign-ring pressed into hot seal-wax signs a container with a " +
      "wax-seal before delivery. \n");
    add_item("smell", 
      "A mix of wool, oak barrels and dried meat makes up an exciting " +
      "smell in this warehouse. \n");
    add_item("walls", 
      "Sturdy timber walls protects the goods from thiefs and there " +
      "is only a small window at the back wall. \n");
    add_item(({ "wax-seal", "wax-seals" }), 
      "A signed wax-seal confirms who wrote the label and that the " +
      "goods are untouched and that the label has not been altered. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the warehouse.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("westpier3.c", "east");
    
    
    
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



