/*  /d/Faerun/phlan/rooms/church4.c
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
    set_long("Church of Tyr bishop's office.\n"
        +"This is Bishop Tulloch's office. It befits the leader of the local"
        +" church. A door to the west leads back to the upper foyer. The walls are"
        +" covered in a tasteful veneer of white birch with several paintings"
        +" spaced about the room. A large desk and chair dominate the room with"
        +" a smaller chair off to the side. A large silver chandelier holding"
        +" dozens of candles is suspended from the ceiling. A thick carpet covers"
        +" the floor completely.\n");
    
    set_short("Bishop's office");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are covered in a veneer of white birch. Not as brilliant as the,"
        +" alabaster in other areas of the church, this is a more warm and soft"
        +" color. They reflect the flickering light of the chandelier.\n");

    add_item(({"birch", "veneer"}),
        "The birch veneer is a thin layer of wood over top of the wall material. It"
        +" has light, creamy grain that compliments the warm white wood itself.\n");

    add_item(({"floor", "ground"}),
        "The floor is covered in a thick white carpet that stretches"
        +" from wall to wall.\n");

    add_item(({"carpet"}),
        "This carpet extends from wall to wall. It is soft enough to muffle"
        +" footsteps. It is a composition of royal purple and turquoise blue.\n");

    add_item(({"ceiling"}),
        "The ceiling, like the walls, is made of white birch veneer. It"
        +" reflects the light of the chandelier.\n");

    add_item(({"chandelier"}),
        "A large, complex chandelier of wrought silver. The graceful twists"
        +" and curves of the metal expertly play the light of the candles across"
        +" the room.\n");

    add_item(({"candles"}),
        "Beeswax candles of purple and blue in even numbers fill the holders"
        +" of the chandelier, shedding both a subtle fragrance and warm light.\n");
        
    add_item(({"chair", "chairs"}),
        "There are two chairs, do you wish to examine the larger or smaller"
        +" chair?\n");

    add_item(({"larger chair", "large chair"}),
        "The large chair behind the desk looks like something you would see in"
        +" a barrister's office. It is high-backed and looks very official.\n");
        
    add_item(({"smaller chair", "small chair"}),
        "The smaller chair is of plain wood. It looks utilitarian and uncomf"
        +"ortable.\n"); 
        
    add_item(({"door", "doors"}),
        "The door is ebony black. Hammered brass hinges hold it in place.\n");

    add_item(({"hinge", "hinges"}),
        "The hinges are of brass and show the marks of the smith's hammer."
        +" instead of detracting, they make the appearance more robust.\n");

    add_item(({"desk"}),
        "This desk looks like a barrister's bench. The only thing missing is."
        +" a gavel. It is of the same ebony black wood as the door. There must"
        +" be some significance to the color.\n");           

    add_item(({"painting", "paintings"}),
        "Do you want to look at the first, second or third painting?\n");
        
    add_item(({"first painting"}),
        "The first painting shows the god Tyr losing his right hand to"
        +" Kesef the Chaos Hound in a test of honor. Tyr himself is a burly"
        +" noble warrior with a powerful build and bearded face.\n");   
        
    add_item(({"second painting"}),
        "The second painting shows the forces of good overthrowing the temple"
        +" of Bane in the old section of Phlan a century ago.\n");

    add_item(({"third painting"}),
        "The third painting is of Bishop Tulloch himself. He is a tall"
        +" man with broad shoulders and a coppery-red beard.\n");        

/*   
*    The bishop will initiate a quest pertaining to the undead in Valhingen
*    graveyard. It will include research at the library and vanquishing a 
*    reborn vampire from the Pools of Radiance era.  
*
*    A newbie quest will be going to the bishop's office in city hall and 
*    getting his book of scriptures.
*/     

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "church3", "west");   
}


void
reset_faerun_room()
{
    set_searched(0);
}