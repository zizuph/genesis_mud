inherit "/d/Avenir/inherit/room";
#include "/d/Avenir/common/dark/dark.h"
create_domain_room()   {

        set_short("Dark bend in the tunnel");
        set_long(
 "You are at a bend in the tunnel, turning from west to north. The "
+"tunnel stretches ahead of you to the north, into an impenetrable "
+"darkness that has an ancient, heavy feeling to it. The tunnel walls "
+"are worn stone, and the floor is covered in a layer of dust that "
+"has accumulated over the ages.\n");

        AI(({"wall","walls"}),"The walls, constructed ages ago, are "
+"of a smooth stone that does not seem to be indiginous to the caverns. "
+"It is a white rock with swirling, light blue patterns running through "
+"it. The walls have been worn with the passage of time, and cracks have "
+"appeared in the once perfectly smooth surface.\n");

        AI(({"crack","cracks"}),"The beautiful white walls are covered "
+"with tiny webs of cracks all through them, possibly due to some "
+"movement of the land ages ago.\n");

        AI(("dust"),"A thick layer of stone dust rests on the floor "
+"here, a reminder that this area of the tunnels has been abandoned "
+"for some time. The dust seems to have been disturbed in places, but "
+"whether that is from the warm, gentle breeze that blows though the "
+"area, or from someone's passage, you cannot tell.\n");

        AI(({"dark","darkness"}),"The darkness seems to have a life "
+"of its own, stretching itself out in an attempt to engulf you "
+"within.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls. The floor is covered in a "
+"thick layer of stone dust that flys into the air around you as you "
+"tread on it.\n");

        add_exit("/d/Avenir/common/dark/l2/n10","up",0);
        add_exit("/d/Avenir/common/dark/l3/s4","north",0);

        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

}

