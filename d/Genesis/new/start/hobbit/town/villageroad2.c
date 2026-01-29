/*
 * File         : /d/Genesis/start/hobbit/town/villageroad2.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/21/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        There is a village road connecting all buildings in the village.
 *        It is made of packed dirt except for some flat stones
 *        surrounding the village hall. When it is raining the road gets
 *        really slippry but they are well packed so the water dries up
 *        pretty quickly afterwords.
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
object Guard;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("A village dirt road");
    set_long(
      "A village dirt road runs around the village hall passing here " +
      "from west to south. Northeast of here you see a stone building " +
      "with iron bars in the windows next to a nice little house of " +
      "ordinary design south of it.\n");
    add_item("bars", 
      "The iron bars resides in the windows of the stone building. \n");
    add_item(({ "bell", "bronze bell" }), 
      "The small bronze bell is used to gather the village garde when " +
      "someone is endangered. \n");
    add_item(({ "bird", "birds", "water" }), 
      "This is a very nice little village filled with rippling water " +
      "and chirping birds. \n");
    add_item("house", 
      "A nice little living house with a reed roof like most " +
      "buildings in the village. \n");
    add_item("stone building", 
      "The stone building seems to be a bank. \n");
    add_item(({ "village hall", "hall", "building" }), 
      "A small copper tower with a bell adorns the white painted " +
      "village hall. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/21/99.\n");
    
    add_exit("livinghouse1.c", "east");
    add_exit("bank.c", "northeast");
    add_exit("villageroad3.c", "south");
    add_exit("villageroad1.c", "west");
    
    
    
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
    if (!objectp(Guard))
    {
        Guard = clone_object(EX_MON + "guard");
        Guard->configure_me(85);  // Make Mungar II the middle son
        Guard->grid_set_size(4,3); // Set patrol area
        Guard->grid_set_pos(4,3);  // Set position of this room in area
        Guard->move(this_object(), 1);
        tell_room(TO, QCTNAME(Guard) + " walks in.\n");
    }
    
}



