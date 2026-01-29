/*******************************************************************************
 * Outside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/
#include "defs.h"
inherit OUTPOST_OUTSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("In the northwestern tower.");
    set_long("You are inside the northwestern tower of the elven outpost. " +
      "The tower provides you with a excellent view of the area to " +
       "south. From this height, you can see the long road that leads " +
       "up to this outpost. Below you, the top of the gates. There is a " +
       "small wall around the outside of the tower with a three " +
       "foot gap between the wall and the roof to protect you from incoming " +
       "attacks. The roof of the tower provides you with protection against " +
       "the rain and other elements. The only exit you see is down the "+
       "through access hatch and into the yard bellow.\n");

    add_item( ({"wall"}),
        "The small wall around the outside of the tower, that leaves a three " +
        "foot gap between the wall and the roof to protect you from incoming " +
        "attacks.\n");

    add_item( ({"road" , "long road"}),
        "the long road is winding and somewhat dusty. It's the same road that " +
        "lead up to the outpost.\n");

    add_item( ({"gate" , "gates"}),
        "The gates are about eight feet tall and made of thick wooden logs " +
        "that are held together with iron bands.\n");
    

    add_exit("nwtower01","down");
}
