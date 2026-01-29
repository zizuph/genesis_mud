 /* 
    The road to the Docks of Gelan. 

    Digit 02 FEB 95 
    Modified, Maniac, 25/5/95 
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

#define NORTHEAST_CONNECT "/d/Calia/gelan/rooms/entrance_road"

void
create_room()
{
    set_short("Road to docks centre");
    set_long("The sun shines down on you from a rich blue sky as you " +
             "head along a main road that leads west to the docks of Calia " +
             "and east to an important roundabout. There is much trading " +
             "traffic passing in both directions along this road. Just to " +
             "your " +
             "north you see a Calian flag mounted at the top of " +
             "a very tall flagpole, fluttering proudly in the sea breeze. " +
             "On either side of it are the battle standards of Calia.\n");

    add_item("road", "A wide, well built road along which travel large " +
             "numbers of trading and travelling folk.\n");
    
    add_item(({"flag", "calian flag"}), "The flag of the free land of Calia " +
             "is a depiction of the Crystalline Palace, that which is a " +
             "monument to the rise and defence of free civilisation over " +
             "barbarism and tyranny.\n");

    add_item(({"standards", "standard", "battle standard", "battle standards"}),
             "You see two tall battle standards. One depicts a noble grey " +
             "wolf, the other a swarm of bees.\n");
 
    add_exit(NORTHEAST_CONNECT, "northeast"); 
    add_exit(ROAD+"road18","southeast"); 
    add_exit(ROAD+"road19","east");
    add_exit(ROAD+"road21","west");
}
