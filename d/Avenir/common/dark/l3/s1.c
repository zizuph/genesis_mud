
inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


create_room()   {

        set_short("Dark passage");
        set_long(
"The tunnel seems to level out here, opening up to the north into a "
+"crossing of passages. The way rises up to the south at a gentle "
+"slope into darkness. The floor is covered in a thin layer of "
+"dust, and the walls gleam and sparkle in the light. A warm breeze "
+"flows past you from the north and along the passage to the south.\n");

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


        add_exit("/d/Avenir/common/dark/l3/s2","south",0);
        add_exit("/d/Avenir/common/dark/l3/center","north",0);

        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

}

