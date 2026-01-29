inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
 {
    set_short("Narrow Canyon");
    set_long("The canyon turns to the southeast here, winding its "
    	+"way deeper southward into the scorched earth which is the "
    	+"Athasian landsape.  The cliffs along side you seem to urge "
    	+"you forward, looming overhead forebodingly.  It is very "
    	+"quiet as you walk, the only sound coming from the wind "
    	+"whipping through the narrow canyon, and your footsteps "
    	+"echoing off the canyon walls.\n");
    add_exit(SOUTH + "p3","southeast");
   add_exit(SOUTH + "p5","west");
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


