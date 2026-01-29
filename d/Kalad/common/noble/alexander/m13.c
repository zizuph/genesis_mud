inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("A small bedroom");
    set_long("You stand in a small, nicely furnished bedroom. The "+
        "carpet beneath you is made out of warm, white bear fur, which "+
        "contrasts the black, oak walls. A few paintings hang from the "+
        "walls, over the round bed which sits in the center of the room. "+
        "A dresser is shoved to one side, while a little nightstand lays "+
        "next to the bed.\n");
    add_item("carpet","The fur feels warm to your feet.\n");
    add_item("walls","The walls are smooth and polished.\n");
    add_item("paintings","More than a few display beautiful, nude "+
        "women whos skin is the purest of ivory, and hair is the blackest "+
        "of night.\n");
    add_item("bed","The bed is round, and covered with white fluffy "+
        "pillows and covers.\n");
    add_item("dresser","A brown, oak dresser which is polished "+
        "to a high shine. A small mirror stands on it. The dresser is "+
        "filled with women's clothes.\n");
    add_item("nightstand","The nightstand is small, and a single candle "+
        "is placed on it.\n");
    add_item("candle","The candle looks like it is almost melted away.\n");
    add_item("mirror","A little mirror that women use when doing some "+
        "make up.\n");
    INSIDE;
    
    add_exit(NOBLE(alexander/m16),"south",0,-1,0);
}
