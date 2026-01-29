inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
 {
    set_short("Narrow Canyon");
    set_long("The cliffs overhead seem be getting lower the further "
    	+"south you travel.  Currently they are only between 20 and "
    	+"25 feet tall.  Pale ribbons of colored earth line the walls, "
    	+"a grim reminder of the once thriving life here.  The floor "
    	+"of the canyon is smooth and running slightly downhill, as "
    	+"if a river had once run through here.\n");
    add_exit(SOUTH + "p2","east");
    add_exit(SOUTH + "p4","northwest");
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

