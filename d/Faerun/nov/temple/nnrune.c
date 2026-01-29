#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";


void
create_nov_room()
{
                   
    set_name("In the northern secion of the runecrafter's area");
    add_name( ({ "room", "hall", "corridor", }) );

    set_short("In the northern section of the runecrafter's area");
    set_long("In the northern section of the runecrafter's area.\n");
    
       
        
        add_item(({"brazier", "braziers"}),
        "Meter-high twisted-brass braziers hold burning chunks of oil-soaked "+
        "coals, giving off light and a harsh-smelling frangrance.\n");
        
        

    add_exit(NOV_DIR + "temple/ncrune",   "south");
    
    
    setuid();
    seteuid(getuid());  
    
    clone_object(NOV_DIR +"obj/stonecutter")->move(this_object());


}

