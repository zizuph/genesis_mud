inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On Gateway Street");
    set_long("You now travel along the northern most street of Kabal: "+
    "Gateway street. This street heads east all the way into the "+
    "Caravan district, crossing the two gates to outside of the city; "+
    "High gate and Caravan gate. The street here in the noble district "+
    "is very well kept and clean. A small shop is to your south, and "+
    "you see a gold sign over it.\n");
    add_item(({"gold sign","sign"}),"It has words on it.\n");
    add_cmd_item("sign","read","It reads: Jewel Emporium.\n");
    add_item("shop","It is a small building made of fine white stone.\n");
    add_exit(NOBLE(gateway/s1),"west",0,0,-1);
    add_exit(NOBLE(gateway/s3),"east",0,0,-1);
    add_exit(NOBLE(jewel_shop),"south",0,-1,-1);
}

