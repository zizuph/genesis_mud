#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In the meeting room");
    set_long("\n    You are within a square sized room of black "+
    "stone. The walls and ceiling are smooth to the touch, and "+
    "the floor is made of polished black marble. On the floor "+
    "you also notice a huge mosaic of a green grim-looking "+
    "skull. The air here is still and cold.\n"+
    "   There are many wooden chairs scattered around the room, "+
    "most facing the center of the room. Floating in the "+
    "air above you, is a glowing orb that casts an eerie "+
    "blood-red light.\n\n");
    add_item("orb","The orb is small, but it glows brightly, "+
    "casting an eerie red glow in the room.\n");
    add_item("chairs","The chairs are made of black oak, from "+
    "the forest of shadows most likely. On the backs of them, "+
    "you see a carving of a grim skull.\n");
    add_item("ceiling","The ceiling is made of black stone and "+
    "is slightly vaulted. A glowing orb floats near the "+
    "center top.\n");
    add_item("walls","The walls are made of smoothly carved "+
    "stone, and are cool to the touch.\n");
    add_item("floor","The floor is made of solid, polished "+
    "black marble. On it, you see a huge mosaic of a green "+
    "grim-looking skull.\n");
    add_item(({"skull","mosaic"}),"The mosaic is made of "+
    "green slabs of marble worked in with the black floor. "+
    "It depicts a giant grim-looking skull with red eyes.\n");

    INSIDE;
    clone_object(KHIRAA_DIR(temple/doors/meetdoor2))->move(TO);
     add_prop(ROOM_I_LIGHT,1);
}
