 /* Maniac 27/3/95, 
    Modified to include Amelia's tree 12/5/95 

    Slip code by Overlord 
    Modified, Maniac 19/9/95 
    
    Changed to offer protection to injured Calians, Maniac, 9/7/2000
*/

inherit "/d/Calia/std/std_plateau";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;
#include "/d/Calia/mountain/special/enter_east.c"

void
create_room()
{
    make_the_room("On the side of the cliff, you see a huge gnarled tree, " +
                  "that is apparently coated with crystal.\n", 1);

    add_item("tree", "@@tree_desc");
    add_exit(CROAD+"croad25","north","@@slip");
    add_exit(CROAD+"croad23","east", "@@slip");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    enter_calian_protection_room(ob, from); 
}

void
init()
{
    ::init();
    add_action("enter_door", "knock");
}
