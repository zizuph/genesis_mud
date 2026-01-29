#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

#include <macros.h>
#include <language.h>
#include <ss_types.h>

create_shawrom()
{

    set_short("Southwest in the Trollshaw");
    set_extraline(
          "You are in the southwestern part of the Trollshaws. Standing on this ridge "
         +"looking north and east you see this ridge continue, overgrown as it is, with "
         +"bushes. To the southwest you see a narrow slope leading down to "
         +"the Great Eastroad. While looking around this place you get a feeling "
         +"that you should not be here if you are seeking peace and tranquility. But "
         +"brave and sturdy as you are, you decide to continue. ");
         
    add_item("slope","The slope winds its way down southwest toward the Eastroad.\n");
    
//    add_call("climb", "[down] [the] 'hill' / 'southwest'", "do_climb");
    
    add_exit(TROLLSH_DIR + "shaws2", "north", 0, 2);
    add_exit(TROLLSH_DIR + "shaws4", "east", 0);
    add_exit(TROLLSH_DIR + "rivend3", "southwest", 0, 2);

}
/*
int
do_climb(string str)
{
    if(str)
    {
        if(TP->query_skill(SS_CLIMB)>30)
        {
            write("You skillfully climb down from the hill.\n");
            TP->move_living("M", TROLLSH_DIR + "rivend3");
            say(QCTNAME(TP)+" climbs down from the hill.\n");
            return 1;
        }
        else 
        {
            write("As you try to climb down the hill, you stumble and fall down.\n");
	    say(QCTNAME(TP) +" stumbles as "+HE_SHE(TP)+" tries to climb down, and falls down the hill.\n");
	    tell_room(TROLLSH_DIR + "rivend3",
	    QCNAME(TP) +" comes roling down from the hill!\n");
	    TP->move_living("M", TROLLSH_DIR + "rivend3");
	    return 1;
	}

    }
}
*/
