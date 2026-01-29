/*
 * File         : /d/Genesis/start/hobbit/town/warehouse3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Full warehouse which makes it difficult to see. Boxes with labels
 *        from all parts of Genesis. Maybe a poisonous spider from foreign
 *        countries that could make a newbie sick and puke for a few
 *        minutes if beaten.
 * 
 * TODO         :
 *         * - add items (box labels etc) of this warehouse
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
    set_short("A full warehouse");
    set_long(
      "The crowd of barrels and other containers awaiting delivery makes " +
      "it hard to enter this warehouse. In the sunlight from the window " +
      "you see a lot of dust in the air and cobwebs in the corners but " +
      "the containers seems to have been placed here quite recently.\n");
    add_item(({ "barrel", "barrels" }), 
      "A lot of heavy sealed barrels are piled in this warehouse. \n");
    add_item(({ "basket", "baskets" }), 
      "Gray weaven baskets fills one corner of the warehouse. \n");
    add_item("ceiling", 
      "The inside of the reed roof is tigthly put onto the wall to " +
      "keep the temprature. \n");
    add_item(({ "container", "containers" }), 
      "Many barrels, crates and baskets, fills this warehouse. \n");
    add_item(({ "crate", "crates" }), 
      "There are some crates here filled with \n");
    add_item("floor", 
      "The plank floor is pretty worn due to the heavy traffic of " +
      "goods here. \n");
    add_item(({ "label", "labels" }), 
      "Most goods has a label which tells about originator and " +
      "destination as well as contents \n");
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
    
    add_exit("eastpier4.c", "west");
    
    
    
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
    if (!present("spider", this_object()))
    {
        room_add_object(EX_MON + "spider");
    }
    
}



