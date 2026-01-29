#include "durin.h"

create_durins_way()
{
    road_distance = 500;
    set_short("Durin's Road");
    set_long("Durin's Road.\n" +
	     "You have entered a vast and wide corridor stretching as far as you " +
	     "can see. The walls are smooth and exceptional in its 'Band-pattern'. " +
	     "It is obvious that this road was the main road in the Mines, long time " +
	     "ago. You notice the portal in the west, indicating the proper end " +
	     "of the Road, but Durin's Road continues further into the darkness in the east.\n");
    WEST("entrhall23");
    EAST("durin-2");
}
