#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";


void
create_nov_room()
{
                   
    set_name("In the central secion of the runecrafter's area");
    add_name( ({ "room", "hall", "corridor", }) );

    set_short("In the central section of the runecrafter's area");
    set_long("In the central section of the runecrafter's area.\n");
    
       
        
        add_item(({"brazier", "braziers"}),
        "Meter-high twisted-brass braziers hold burning chunks of oil-soaked "+
        "coals, giving off light and a harsh-smelling frangrance.\n");
        
        

    add_exit(NOV_DIR + "temple/nnrune",   "north");
    add_exit(NOV_DIR + "temple/nnerune",   "northeast");
    add_exit(NOV_DIR + "temple/nerune",   "east");
    add_exit(NOV_DIR + "temple/nserune",   "southeast");
    add_exit(NOV_DIR + "temple/nsrune",   "south");
    add_exit(NOV_DIR + "temple/ecorr1",   "west");
    
    setuid();
    seteuid(getuid());  
    
    //clone_object(NOV_DIR +"obj/labbench")->move(this_object());


}

