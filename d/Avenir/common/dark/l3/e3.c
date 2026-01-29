inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
create_room()   {

	set_short("Dark tunnel");
	set_long(
"A dark and dank tunnel leading into darkness. The rough-hewn walls\n"+
"slope down to the dusty floor. The air is musty and hints of mold.\n"+
"Darkness and fear pervade in this gloomy place. The tunnel continues\n"+
"east, connecting to a small alcove.\n");


        add_exit("/d/Avenir/common/dark/l3/e2","north",0);
        add_exit("/d/Avenir/common/dark/l3/ec2","east",0); 


   BLACK
   IN

}
