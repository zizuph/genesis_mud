/*
 *	/d/Gondor/ithilien/road/nr5.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("Here the road crosses a stream running down from the Ephel " +
        "Duath on a bridge made of enduring masonry. Large " +
        "thickets and a tumbled land of rocky ghylls and crags lie to the east. " +
        "Behind them the long grim slopes of the Ephel Duath clamber up. To the " +
        "west, the forests of central Ithilien accompany the road. Sometimes the " +
        "Anduin can be seen through the tops of the trees.\n");
    add_mountains(1, "only about a mile");
    add_road(2);
    add_forest(2);
    add_item( ({ "bridge", "masonry", "stones", }), 
  	"The bridge is made of enduring masonry. Large boulders have expertly " +
  	"been joined to make a wide shapely arch. But weeds and moss are growing " +
  	"all over the bridge, and the paving-stones over which the road runs seem " +
        "to have seen little traffic in recent years.\n");  	
   add_exit(ITH_DIR + "road/nr6", "north", test_exit, 4); 
   add_exit(ITH_DIR + "road/nr4", "south", test_exit, 4);
}

