/*
 * File         : /d/Genesis/start/hobbit/town/gateroad1.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/21/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is the innerpart of the gate area were the village defence
 *        prepared themselves for battle. The creek passes by and there
 *        are some remains of old shelters/barracks for the soldiers here.
 *        The area is filled with grass, flowers and chirping birds and is
 *        commonly used as playground for the village citizens.
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
object Herbalist;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("Inside village gate");
    set_long(
      "The dirtroad is surrounded by well-kept lawns and flower patches " +
      "as well as some small trees planted just recently. A small creek " +
      "flows from the gate, north of here, to the south.\n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/21/99.\n");
    
    add_exit("gate.c", "north");
    add_exit("villageroad1.c", "south");
    
    
    
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
    if (!objectp(Herbalist))
    {
        Herbalist = clone_object(EX_MON + "herbalist");
        Herbalist->move(this_object(), 1);
        tell_room(TO, QCTNAME(Herbalist) + " arrives.\n");
        Herbalist->equip_me();
    }
    
}



