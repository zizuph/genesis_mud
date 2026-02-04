//removed link-room cloning - Lilith Jul 2008
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
void
create_room()
{
    set_short("dark ravine");
    set_long("A vicious wind blows through the ravine, robbing "+
        "you of your breath and kicking up fine snow crystals "+
        "that blind your eyes with tears.\n");

    add_item("ground", 
	"The ground is hard with frost.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads north "+
        "into the mountain.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, -1);

    add_exit("forest04", "south");
    add_exit("forest05", "north");

}


