//removed link-room cloning - Lilith Jul 2008
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("valley of the shadow of death");
    set_long(
        "You are walking along a path that slowly widens "+
        "into a road. This small valley, which is deathly silent, "+
        "seems to hold some ancient and terrible secret. "+
        "Dark mountain peaks cast shadows on the valley and its "+
        "contents, which consist mainly of a ruined old "+
        "house and the twisted remains of a once-great "+
        "vineyard. Water slowly encroaches upon this place, "+
        "concealing in its depths a host of mysteries. "+
        "A blanket of snow covers the ground like a shroud.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item("ground", 
	"The ground is hard with frost and covered in snow.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads south "+
        "into the mountain.\n");
    add_item(({"house", "ruins", "mansion", "building"}),
        "These are the remains of a once-great house, long ago "+
        "abandoned and now crumbling to ruins.\n");    
    add_item(({"vineyard", "vines"}),
        "The vines were long ago petrified into the grotesquely "+
        "tortured shapes you see now.\n");
    add_item(({"north", "cliff", "landslide", "avalanche", "debris"}),
        "The north edge of the valley is marked by a sheer cliff "+
        "and a huge landslide at its base, which has nearly "+
        "buried an old house, and formed a dam.\n");
   add_item(({"mountain", "mountains", "valley"}), 
       "These mountains are dark and forbidding. They cast "+
       "shadows over most of the valley and the water that "+
       "is slowly encroaching upon it.\n");
   add_item(({"water", "dam"}),
       "Rocks and shale fallen from the mountainside have "+
       "dammed the flow of water, forming a large body "+
       "of icy water that is slowly drowning the valley.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "forest05", "up");
    add_exit(TOMBDIR + "forest07", "north");
}


