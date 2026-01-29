inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>;
#include "/d/Rhovanion/defs.h";

void create_room()
{
    set_short("West part of the hallway.");
    set_long("The hallway stretches out to the west and east, and "+
            " to the east you see light coming through the doors. Several small "+ 
            " rooms line the hallway's south side. Some light filters in through"+
            " small holes high up on the northern wall, sending beams of light down"+
            " through the dust-filled air that stirs with your passing.\n");

    add_exit(RHUN_DIR + "newruins/hall","east");
    add_exit(RHUN_DIR + "newruins/wtower","west");
    add_exit(RHUN_DIR + "newruins/smroom","south");
 
    add_item(({"halls","hallway"}),"The halls are wide and paved with"+
            " stone. The walls are like the outside walls of the fort,"+
            " rough and and damp with moisture.  Dust covers everything,"+
            " heavy layers of dust have settled on everything during the"+
            " centuries.\n");

    add_item("floor","The floor is made of stone and covered with centuries"+
            " of dust and debris. Clouds of dust rise as you walk across floor.\n");

    add_item("holes","Small holes high upon the north wall lets some light into the hall, not much "+
            "but at least you can see what you are doing.\n");

    add_prop(ROOM_I_INSIDE,1);
}