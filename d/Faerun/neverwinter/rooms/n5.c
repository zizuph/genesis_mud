/*  /d/Faerun/neverwinter/rooms/n3.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_NEWERW_OUTDOOR;


public int
block_check()
{      
    write("A multitude of caravans have blocked off access to the "
       +"western part of Protector's Enclave. You have no idea when the "
       +"traffic will clear.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" tries to go west, but realizes that the direction "
    +"is blocked.\n", this_player());
        
    return 1;
}


void
create_neverw_outdoor()
{
    extraline = "You are at an intersection in the southeastern "
       +"quadrant of Protector's "
       +"Enclave. The road's before you, wide enough for five "
	   +"wagons to ride abreast with room to spare, is dotted "
	   +"with signs pointing travelers to their destinations "
	   +"for miles around. Filled with beautiful tapestries of "
	   +"greenery and floral groves, the Main Street of Neverwinter "
	   +"is not quite as busy as the gate before it; however, you must "
	   +"keep your wits about you amidst the traffic of the busy "
	   +"crossing.";
    
    set_short("Main Street of Neverwinter");
    
    //If we want herbs here.
    //add_std_herbs("mere");
    
	   
    add_item(({"road"}),
       "The road here is made of the same cobble as the road leading "
       +"to Neverwinter. It has; however, widened for even more "
       +"additional foot traffic. Wagons swerve throughout the "
       +"pedestrians, in a hurry to get to where they are going. "
       +"dotted along the sides of the road are various types of "
       +"trees and bushes. Street lamps, alight with an alchemical fire, "
       +"weave inbetween the fauna. Every so often, you can spot the "
       +"occasional flower bed.\n");
	   
    add_item(({"trees"}),
       "The trees are brought from Neverwinter Wood, a forest just east "
       +"of Neverwinter. They have all been carefully selected to be the "
       +"same size. A few men are clipping the trees, making them look "
       +"as formal as can be.\n");
    
    add_item(({"men"}),
       "A fe men walk the sides of the street, carefully clipping away "
       +"at the Neverwinter trees and bushes.\n");

    add_item(({"bushes", "fauna", "greenery"}),
       "The various bushes that line the side of Neverwinter's streets "
       +"have been given exceptional care. Some even sprout flowers, "
       +"giving yet another splash of color to the already vibrant "
       +"city.\n");
	   
    add_item(({"flower bed", "floral groves"}),
       "The flower bed is watered regularly, and the flowers "
       +"within shine brightly whether rain or shine.\n");
	   
	add_item(({"flowers"}),
       "The flowers range in all sorts of colors, capturing "
       +"even the darkest hearts in their beauty.\n");

    add_item(({"lamps"}),
       "The lamps have been lit with a special magical flame, "
	   +"allowing for the fire to burn forever, illuminating the "
       +"streets at night, and casting a wild shadow in the day.\n");

    reset_faerun_room();

    add_exit(ROOM_DIR + "n4.c", "south");
    add_exit(ROOM_DIR + "n6.c", "east");
    add_exit(ROOM_DIR + "w1.c", "west", block_check);
}


void
reset_faerun_room()
{
    set_searched(0);
}