/*
 * File         : /d/Genesis/start/hobbit/town/canal2.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/4/1998
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

inherit "/std/room";


#include <stdproperties.h> 
#include <macros.h> 
#include "../hobbit.h"
/* prototypes */
void    create_room();
void    reset_room();



/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("At the canal.");
    set_long(
      "You are standing by the canal looking out over the water. The " +
      "canal is natural and almost overgrown by reed but the heavy boat " +
      "traffic here keeps a narrow path in the reed open and right here " +
      "it passes quite close to land. The grass here look comfortable " +
      "to sit at and you figure this could be a good place for fishing.\n");
    
    add_exit("canal1.c", "north",0);
    add_exit("canal3.c", "south",0);
    
    
    
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



