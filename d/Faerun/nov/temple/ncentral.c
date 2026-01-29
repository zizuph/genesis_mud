#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
public int 
blockmembers()
{
      
    if (this_player()->query_skill(COUNCIL))
    {
        
        write("Welcome, "+this_player()->query_name()+"!\n");
        return 0;
    }

    write("Only High Maguses may go further up!\n");
        return 1;
}

void
create_nov_room()
{
                   
    set_name("In the chamber of planning");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("You are in an intersection in the western part of the " +
    "temple");
    set_long("You are in an intersection in the western part of the " +
    "temple. Footsteps are echoing throughout the rooms but you are unsure if they only " +
    "come from you. The flagstone walls are " +
    "lined with dried blood and scratches from occurances of ancient time. In " +
    "the left corner of the room you see a small winding stairs that leads " +
    "up and down.\n");
    
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

    add_exit(NOV_DIR + "temple/nstorage",   "north");
 
    add_exit(NOV_DIR + "temple/wcorr1",   "east");
    add_exit(NOV_DIR + "temple/nmeditate",   "west");
    add_exit(NOV_DIR + "temple/npost",   "southwest");
    add_exit(NOV_DIR + "temple/nstart",   "south");
    add_exit(NOV_DIR + "temple/ntrain",   "northwest");
    add_exit(NOV_DIR + "temple/njoin",   "down");
    add_exit(NOV_DIR + "temple/ncouncil",   "up", blockmembers);
    
  

    
}