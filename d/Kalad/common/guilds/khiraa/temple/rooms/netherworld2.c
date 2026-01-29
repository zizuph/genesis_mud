inherit "/d/Kalad/room_std.c";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
create_room()
{
    set_short("Within the Netherworld");
    set_long("\n"+
    "   You are within a short dark hallway that bends sharply "+
    "to the east, from which you can tell is the source of the "+
    "eerie red light. To the south, you can see the entrance to "+
    "this tower. The black stone walls are unadorned, and the "+
    "ceiling hangs low. Your footsteps echo along the cold floor.\n\n");
    add_item("walls","The walls are made of cold black stone.\n");
    add_item("ceiling","The ceiling is made of cold black stone.\n");
    add_item("floor","The floor is made of smooth black marble.\n");
    INSIDE;
    add_exit(KHIRAA_DIR(temple/rooms/netherworld3),"east",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/netherworld1),"south",0,-1);
}
