/*
 * File         : /d/Genesis/start/hobbit/town/gate.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/4/1998
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The gate was an important point of defence during the troll war
 *        but has since then beeing reduced to an inconvinience for the
 *        travellers so the city council decided to let it be open. The
 *        old gate keeper insisted however to have it shut during nights.
 *        The gate is now so worn down that could hardly stand up against
 *        a serious attack from outside.
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
    set_short("Outside village gate");
    set_long(
      "The worn down gate is open allowing entrance to the village to " +
      "the south. A small creek ripples by pretty fast in a narrow " +
      "opening just beneth the gate. Sandwalls for defence of the " +
      "village starts off on both sides of the gate running southeast " +
      "and southwest from here.\n");
    
    add_exit("woodpath5.c", "north",0);
    add_exit("gateroad1.c", "south",0);
    
    
    
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



