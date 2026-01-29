/*  /d/Faerun/phlan/rooms/church5.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;

/*
*   Making the basic room
*/

void
create_phlan_room()
{
    set_long("Church of Tyr confessional.\n"
        +"This is the confessional. It is spartan and functional. The walls are of "
        +" dull black wood, as are the ceiling and floor. A single white candle"
        +" burns in a black iron holder mounted to the wall. A small kneeling rug"
        +" sits in the middle of the ten foot square floor in front of a silver"
        +" balance. The door to the upper foyer is to the east.\n");
    
    set_short("Church confessional");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are of a dull black wood that does not reflect the light,"
        +" even right behind the candle.\n");

    add_item(({"wood"}),
        "You can't identify this wood. It is dull black and reflects no light.\n");

    add_item(({"floor", "ground"}),
        "The floor is of the same dull black wood as the walls and ceiling."
        +" A small kneeling rug and silver balance sit on it.\n");

    add_item(({"rug", "kneeling rug"}),
        "A small kneeling rug of purple and blue. It is not very thick and does"
        +" not look as if it would be comfortable to kneel on for very long.\n");

    add_item(({"ceiling"}),
        "The ceiling, is made of the same dull black wood as the walls and floor."
        +" It does not reflect the light of the white candle.\n");

    add_item(({"candle"}),
        "A simple white candle in a black iron holder. It does not seem to be"
        +" consumed as it burns.\n");

    add_item(({"holder", "candle holder", "iron holder"}),
        "The black iron candle holder is simple and non-reflective.\n");
        
    add_item(({"balance"}),
        "The silver balance looks tangible, but no interaction will affect it."
        +" It consists of an eighteen inch high fulcrum with a twelve inch cross"
        +"bar. From each end of the bar, suspended by three small silver chains, is"
        +" a silver plate approcimately three inches in diameter. Next to the balance"
        +" are half a doze each of black and white weights, all the same size.\n");

    add_item(({"fulcrum"}),
        "The central post on which the bar balances. It is made of silver.\n");
        
    add_item(({"bar", "cross bar"}),
        "The balance bar which sits on the fulcrum. It is made of silver.\n");   

    add_item(({"chain", "chains"}),
        "Fine chains that suspend the plates from the end of the cross bar. They"
        +" are made of silver.\n");    

    add_item(({"plate", "plates"}),
        "The plates are approximately three inches in diameter and are suspended"
        +" from the cross bar by fine silver chains. Weights would be placed on"
        +" the plates to measure weight.\n");        
        
    add_item(({"weight", "weights"}),
        "The small weights are painted black or white. There are an even number"
        +" of each.\n"); 
        
    add_item(({"door", "doors"}),
        "The door is dull black on the inside, matching the room. Black iron"
        +" hinges support the door.\n");

    add_item(({"hinge", "hinges"}),
        "The hinges are of simple black iron.\n");
     
/*   
*    When kneeling on the rug, the balance will load with black and white weights
*    based on alignment. At the phrase "confess" the scale will flash and a tag
*    will be added to the character allowing them to do the vampire quest for the bishop.
*    It will not affect alignment and alignment will not restrict the quest.  
*
*/     

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "church3", "east");   
}


void
reset_faerun_room()
{
    set_searched(0);
}