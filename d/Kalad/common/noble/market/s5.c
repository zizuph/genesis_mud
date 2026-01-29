inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On Market Street");
    set_long("You are now on the Market Street in the Noble district "+
        "of Kabal. This street is a little noisier than the rest in the "+
        "Noble district because of the various merchants travelling along "+
        "here from the Market district. However, the road is clean and "+
        "well kept. Wayfarer's Boulevard branches off here to the east, "+
        "while Market street goes on southeast into the heart of the "+
        "Noble district.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("merchants","They wander about tending to their wares.\n");
    add_item("estates","Grand houses and gardens of such "+
        "beauty that you are amazed.\n");
    add_exit(NOBLE(gateway-end),"northwest",0,0,-1);
    add_exit(NOBLE(wayfarer/s1),"east",0,0,-1);
    add_exit(NOBLE(market/s4),"southeast",0,0,-1);
}

