inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("above treeline on a dark mountainside");
    set_long(
        "You are high upon a dark mountainside, just above the treeline. "+
        "The air is getting thinner and a chilling wind carries a fine "+
        "icy mist that obscures visability. Powdery snow and frost "+
        "covers the ground in a thin layer. The zig-zag path is full "+
        "of loose shale that makes footing treacherous.\n"
    );

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "Far below are ancient oak trees.\n"
    );

    add_item("thicket", "It's an ordinary thicket.\n");

    add_item(({"path", "zig-zag path"}),
        "Strewn with loose rocks, it winds upwards toward the top "+
        "of the mountain, and down, into oak trees.\n");
    add_item("ground", 
	"The ground is hard with frost and covered in a thin layer "+
         "of powdery snow.\n");
    add_item(({"shale", "loose rocks"}), 
        "The shale has formed from pieces of the mountain that have "+
        "fallen off and down its side, deteriorating. It makes your "+
        "footing very difficult, and creates concerns about an "+
        "avalanche.\n");
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "forest02", "down");
    add_exit(TOMBDIR + "forest04", "up");

}


