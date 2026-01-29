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
    "Noble district becuase of the various merchants travelling along "+
    "here from the Market district. However, the road is clean and "+
    "well kept. A rather large and expensive looking building is "+
    "off to your west. There is a sign over the doorway. A smaller "+
    "building is off to the east.\n");
    add_item("sign","It is small but readable.\n");
    add_cmd_item("sign","read","The Gentlemen's exotic club.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("merchants","They wander about tending to their wares.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(market/s5),"northwest",0,0,-1);
    /* add_exit(NOBLE(club/room1),"west",0,0,-1); */
    add_exit(NOBLE(market/s3),"southeast",0,0,-1);
/*
    add_exit(NOBLE(giftwrap/giftshop),"east",0,0,-1);
*/
}

