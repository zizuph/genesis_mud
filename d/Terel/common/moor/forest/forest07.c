//removed link-room cloning - Lilith Jul 2008
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#define VAMP_CONNECT   "/d/Terel/guilds/vamp/room/gate_outside"

void
create_room()
{
    set_short("valley of the shadow of death");
    set_long(
        "The icy Dragon Mountains loom high above, darkening the sky and "+
        "casting a palpable shadow over the valley. Silence reigns here, "+
        "a desolate silence unbroken by the sounds of bird or insect. "+
        "An ancient mansion lies a short distance north, "+
        "encircled by a high stone fence and protected by a rusted "+
        "gate. The road leads south through the tortured "+
        "remains of a grand vineyard and up out of the "+
        "valley. The land on the west side of the road is "+
        "smothered by dank and icy water. "+
        "A foul wind kicks up puffs of frost from "+
        "the blanket of snow which covers the ground "+
        "like a shroud.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item(({"ground", "snow"}),
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
        "buried an old house.\n");
    add_item(({"mountain", "mountains", "valley"}), 
       "These mountains are dark and forbidding. They cast "+
       "shadows over most of the valley.\n");
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
	add_prop(OBJ_I_CONTAIN_WATER,1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);	
    add_prop("_live_i_can_fish", ({"freshwater"}));

    add_exit("forest06", "south");
    add_exit(VAMP_CONNECT, "north");

}


