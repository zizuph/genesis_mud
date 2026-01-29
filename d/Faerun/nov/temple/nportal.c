#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
                   
    set_name("In the chamber of the planes");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("In the chamber of the planes");
    set_long("In the chamber of the planes.\n");

    add_exit(NOV_DIR + "temple/ncentral",   "north");
    
    //clone_object(NOV_DIR +"obj/nportal1")->move(this_object(), 1);  
  
        
    
}