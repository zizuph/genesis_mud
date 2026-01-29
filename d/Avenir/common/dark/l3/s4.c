inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

static object gavriel;

// Removed Gavriel, because he is no longer
// applicable.
//   -Cirion, Jan 28, 1996

void
create_room()   {

        set_short("In a long and dark tunnel");
        set_long(
"The tunnel slopes gently down to the north, into the thick darkness. "
+"The silence of this area presses down on you like a weight, slowing "
+"your movements. The dust that covers the floor of the passage seems "
+"to have been disturbed recently.\n");

        add_exit("/d/Avenir/common/dark/l3/s5_l2","south",0);
        add_exit("/d/Avenir/common/dark/l3/s3","north",0);

        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

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
+"for some time. The dust here has been disturbed quite recently "
+"with some strange footprints, and beneath the dust you can see "
+"deep marks that have been carved into the floor.\n");

        AI(({"dark","darkness"}),"The darkness seems to have a life "
+"of its own, stretching itself out in an attempt to engulf you "
+"within.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls. The floor is covered in a "
+"thick layer of stone dust, beneath which you can make out some "
+"strange marks.\n");

        AI(({"marks","mark"}),
"Long, deep marks have been gouged into the floor. They almost seem "
+"to be claw marks, made by some beast with extraodinary strength.\n");

}

