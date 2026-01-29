inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
 {
    set_short("Narrow Canyon");
    set_long("The rocky canyon twists and turns southward as you "
    	+"walk further into its mazelike interior.  On your sides, "
    	+"nearly sheer cliff walls loom.  Sand and dust swirls "
    	+"through the canyon, twisting and spiraling wherever "
    	+"the harsh, dry wind takes it.\n");
     add_exit(SOUTH + "p4","east");
    add_exit("/d/Cirath/ridge/valley/v20.c","northwest");
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

