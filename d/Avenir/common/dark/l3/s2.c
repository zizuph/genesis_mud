inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


create_room()   {

        set_short("In the dark tunnel");
        set_long(
"The tunnel runs up to the south, and sloped downwards to the north, "
+"into darkness. There is a faint musty scent in the air, and a "
+"warm, gentle breeze flows up the passage from the south, "
+"disturbing the dust and making it float all about. The floor "
+"is covered in a layer of damp dust, and the walls are of a "
+"pristine white stone that seems to hold a shining glow.\n");

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
+"for some time. The dust is a little damp here, making it stick "
+"to everything it touches.\n");

        AI(({"dark","darkness"}),"The darkness seems to have a life "
+"of its own, stretching itself out in an attempt to engulf you "
+"within.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls, and is covered in a "
+"thick layer of wet stone dust.\n");

        add_exit("/d/Avenir/common/dark/l3/s3","south",0);
        add_exit("/d/Avenir/common/dark/l3/s1","north",0);

        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

}

