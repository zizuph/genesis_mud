inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
 {
    set_short("Narrow Canyon");
    set_long("The canyon takes a hard turn east here, and ahead you can "
    	+"see the canyon opening up onto a plain of some sort.  You are "
    	+"too far away to see any details, though.  The walls of the cliffs "
    	+"around you are now around 15 feet high, and look to level off at "
    	+"that height as they run to the end of the canyon.  The wind whips "
    	+"wildly through here, somehow sensing the end of the gorge ahead.\n");
    add_exit(SOUTH + "d27","east");
    add_exit(SOUTH + "p2","west");
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

