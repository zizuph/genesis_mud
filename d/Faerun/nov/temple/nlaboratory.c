#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
    
        set_short("In the laboratory");
        set_long("You are in the laboratory.  Smoking braziers stand at each corner "+
        "of the room, emitting a harsh-smelling "+
        "incence and an eerie, green light.\n");
        
        add_item(({"brazier", "braziers"}),
        "Meter-high twisted-brass braziers hold burning chunks of oil-soaked "+
        "coals, giving off light and a harsh-smelling frangrance.\n");
       
        //clone_object(BANEDEAD_DIR +"obj/tome")->move(this_object());
        
        add_exit(NOV_DIR +"temple/nmagic", "south");
        
        setuid();
        seteuid(getuid());       
}
        
