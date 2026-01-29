#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

int number;
 
 
int
add_portal()
{
	
	if (number == 1)
	{
		clone_object(NOV_DIR +"obj/p1")->move(this_object(), 1);
		tell_room(this_object(), "A huge black " +
		"portal materializes in the circle of skulls!\n");
		number = 2;
		return 1;
	}
	
	if (number == 2)
	{
		clone_object(NOV_DIR +"obj/p2")->move(this_object(), 1);
		tell_room(this_object(), "A huge green " +
		"portal materializes in the circle of skulls!\n");
		number = 3;
		return 1;
	}
	
	if (number == 3)
	{
		clone_object(NOV_DIR +"obj/p3")->move(this_object(), 1);
		tell_room(this_object(), "A huge blue " +
		"portal materializes in the circle of skulls!\n");
		number = 4;
		return 1;
	}
	
	if (number == 4)
	{
		clone_object(NOV_DIR +"obj/p4")->move(this_object(), 1);
		tell_room(this_object(), "A huge yellow " +
		"portal materializes in the circle of skulls!\n");
		number = 1;
		return 1;
	}
	
	return 1;
}

	
	 
 
 
void
create_nov_room()
{
                   
    set_name("In the chamber of portals");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("In the chamber of portals");
    set_long("This is the room of teleportation where portals to foreign " +
    "lands arrive periodicly. Faint light of shifting colours can be " +
    "seen through a small hole in the ceiling, illuminating the the " +
    "room just enough to see a large relief, mural, tapestry and an engraving " +
    "covering the walls. In the middle of the room is a large circle of skulls.\n");

    add_item(({"brazier", "braziers"}),
        "Meter-high twisted-brass braziers hold burning chunks of oil-soaked "+
        "coals, giving off light and a harsh-smelling frangrance.\n");
        
    add_item(({"skulls", "circle"}),
        "A large circle of humanoid skulls are placed in the middle " +
        "of the room. Within the circle, you can see a weak engraving " +
        "of an hexagon.\n");
        
    add_item(({"hexagon"}),
        "Fine straight lines are cut into the ground with great " +
        "precision, forming a hexagon symbol.\n");    
        
 
    add_item(({"relief"}),
        "The relief depicts a large city where its northern gates leads "  +
        "out to a desert. It is painted with a fainth yellow colour.\n"); 
           
    add_item(({"mural"}),
        "This mural depicts a dark forest filled with spiders and a road " +
        "leading south towards a dark tower. Black is the most dominant " +
        "colour of this mural.\n");  
          
    add_item(({"tapestry"}),
        "This tapestry depicts a flourishing forest filled with " +
        "mushrooms. It was weaved using mainly green yarn.\n");  
          
    add_item(({"engraving"}),
        "This area depitcs a town within a huge cave complex. It is painted with a " +
        "blue colour.\n");                               



    add_exit(NOV_DIR + "temple/njoin",   "up");
    
    number = 1;
    
    
    // Portals closed off until the guild opens. Tilorop 31/7-04.
    
    set_alarm(120.0,120.0, &add_portal());
    
    setuid();
    seteuid(getuid());
        
    
}

      
