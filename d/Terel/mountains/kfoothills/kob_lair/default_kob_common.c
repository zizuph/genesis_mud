/*
 *  default_kob_common.c
 *
 *  Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "include/cave_defs.h"

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    start_room_tells();
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Kobold common room");
    
    set_long("The large natural cave has tattered furs lying all around. " + 
        "A few small glowing piles of coals dot the cave and appear to be " + 
        "for cooking meat that has gone too rancid to eat raw. The walls " +
        "rise steeply to a high vaulted ceiling.  Small smooth rocks " + 
        "litter the floor of the cave.\n");
        
    add_item(({"wall","walls"}),
        "The uneven wall rise to the high vaulted ceiling.  They contains " + 
        "many cracks and ledges worn smooth by passage of time.\n");
        
    add_item(({"crack","cracks", "ledge", "ledges"}),
        "The cave walls contains many cracks and ledges.\n");
        
    add_item(({"rock", "rocks", "small rocks"}), "Small rocks litter the " +
        "floor of the cave.\n");

    add_item(({"fires", "cooking fires", "coals"}), "In the cave to the " + 
      "west The glow of small piles of red coals is faintly reflected off " + 
      "mounds of dirty oily furs.\n");

    add_item(({"furs", "oily furs", "mounds"}), "The mounds of furs " + 
      "furs appear to be used for sleeping.\n");
        
    set_tell_time(100 + random(200));
     
    add_tell("You hear the pop from a nearby cooking fire.\n");
    add_tell("The vile stench is overwhelming.\n");
    add_tell("A yipping sound echoes through the large cave.\n");
}
