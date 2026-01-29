#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
                   
    set_name("In the chamber of planning");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("You are in an intersection in the central part of the " +
    "temple");
    set_long("You are in an intersection in the central part of the " +
    "temple. Footsteps are echoing throughout the rooms but you are unsure if they only " +
    "come from you. The flagstone walls are " +
    "lined with dried blood and scratches from occurances of ancient time.\n");
    
    add_item(({"wall", "walls"}),
     "The walls are made of greyish coloured flagstones which are cold to the touch.\n");

    add_item(({"scratches"}),
     "It would almost seem like someone were dragged through the " +
     "halls, fighting to avoid being dragged off by clawing into the " +
     "wall. You just wonder what sort of creature would have the " +
     "strength to dig that deep into the walls.\n");
     
    add_item(({"blood"}),
     "You can only imaging what has been going on in these halls " +
     "to strain the walls this extensively with blood.\n"); 

    add_exit(NOV_DIR + "temple/nliving",   "northwest");
    add_exit(NOV_DIR + "temple/ncorr3",   "north");
    add_exit(NOV_DIR + "temple/ecorr3",   "east");
    add_exit(NOV_DIR + "temple/wcorr3",   "west");
    add_exit(NOV_DIR + "temple/scorr3",   "south");

    
}