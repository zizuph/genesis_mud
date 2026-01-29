inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
 {
    set_short("Narrow Canyon");
    set_long("The gorge continues in a northwest, southeast direction "
    	+"here.  The craggy, windblown cliffs to your sides seem to "
    	+"be getting lower, but at the same time they are no less "
    	+"imposing.  Gusts of wind scream through the canyon, showering "
    	+"you with dirt and small rocks from both the ground above the "
    	+"canyon, and the walls around you.\n");
    add_exit(SOUTH + "p1","east");
    add_exit(SOUTH + "p3","west");
    add_item(({"cliff","walls","cliff walls"}),"They stand to your sides, "
    	+"blocking any attempt to move out of the narrow canyon.\n");
    add_item(({"rocks","rock"}),"They lie scattered about randomly. Sharp, "
        +"wind eroded edges biting at your feet.\n");
    add_item("dust","The ever present dust of "
        +"Athas is everywhere.  When it is not being kicked up "
        +"by your footsteps, it is blowing around on the dry "
        +"winds that swirl constantly.\n");
    add_item("sand","Sand is everywhere here, from the salt flats "
        +"to towering sand dunes.  It is almost as prevalent as "
        +"as the dust that seems to end up in or on everything.  "
        +"Sometimes the sand is coarse and rough, sometimes it is "
        +"so fine it is like silk.  Whatever form its in, its "
        +"always here.\n");

}

