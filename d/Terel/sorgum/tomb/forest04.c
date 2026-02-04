inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("ridgetop");
    set_long(
        "You are atop a ridge, overlooking the mountainside.  Far below, "+
        "you can see a forest, and beyond it, a swamp. A vicious wind "+
        "blows, robbing you of your breath and the rocks of their snow. "+
        "A thin layer of ice sparkles in the muted light. A ravine lies "+
        "north, an ominous jagged gash in the dark stone of the "+
        "mountain.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "Far below are ancient oak trees.\n");


    add_item(({"path", "zig-zag path"}),
        "Strewn with loose rocks, it winds down the side of the "+
        "mountain, and into a forest of oaks.\n");
    add_item("ground", 
	"The ground is hard with frost.\n");
    add_item(({"shale", "loose rocks"}), 
        "The shale has formed from pieces of the mountain that have "+
        "fallen off and down its side, deteriorating. It makes your "+
        "footing very difficult, and creates concerns about "+
        "avalanche.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads north "+
        "into the mountain.\n");
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "forest03", "down");
    add_exit(TOMBDIR + "ravine", "north", 0, 0, 1);

}


