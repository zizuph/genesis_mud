#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
    
        set_short("In the council chamber");
        set_long("You are in the council chamber.  Smoking braziers stand at each corner "+
        "of the room, emitting a harsh-smelling "+
        "incence and an eerie, green light.\n");
        
        add_item(({"brazier", "braziers"}),
        "Meter-high twisted-brass braziers hold burning chunks of oil-soaked "+
        "coals, giving off light and a harsh-smelling frangrance.\n");
       
        clone_object(NOV_DIR + "obj/ncboard")->move(this_object());

        add_exit(NOV_DIR +"temple/ncentral", "down");
        
        setuid();
        seteuid(getuid());       
}
