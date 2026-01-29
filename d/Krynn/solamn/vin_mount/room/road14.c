/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE


void
create_vin_mount_room()
{

    set_short("In the Vale");
    set_long("You are standing in a lovely vale. A stream " +
             "gurgles and bubbles as it flows through the green " +
             "meadow. Even the road seems to melt into the landscape, " +
             "being grown over and barely visible.\n");

    OUTSIDE;

    add_exit(ROOM + "road13","northeast",0,2);
    add_exit(ROOM + "road15","southeast",0,2);
    
    add_item("vale",
	     "It is a lovely vale, no noise can be heard except " +
		"the singing of birds and the occasional rustle of " +
		"some small animal.\n");
    add_item(({"meadow","grass"}),
	     "The grass grows up to your knees and " +
		"has an intensive healthy green color.\n");
    add_item("stream",
	     "This small stream is barely visible beneath the grass, " +
		"but you can hear it bubbling and gurgling next to the " +
		"road.\n");
    add_item(({"ground","road"}),
	     "The road is covered with grass here, " +
		"making your footing soft.\n");
    add_item(({"bird","birds","animal","animals"}),
	     "You can hear sounds but you " +
		"cannot see anything.\n");

}
