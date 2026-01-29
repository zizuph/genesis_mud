inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("An intersection of the House of Aemilius");
    INSIDE;
    set_long("You now stand at an intersection of halls. To the "+
    "west, you see what appears to be a guards room, while to the "+
    "south and southwest, the halls continue. There are many "+
    "ornate decorations hanging from the wall next to a large "+
    "painting. The floor is warm and carpeted.\n");
    add_item(({"large painting","painting"}),"A large desert "+
    "spreads out before you, with the hot sun beating on your "+
    "back. The dust swirls around the feet of a tall, stout "+
    "warrior. He gazes off into the distance, where you can see "+
    "a ruined, stone arena.\nThere is an inscription on the "+
    "bottom.\n");
    add_cmd_item("inscription","read","ATHAS: The eternal warrior.\n");
    add_item("inscription","ATHAS: The eternal warrior.\n");
    add_item("decorations","The are jewels and candles.\n");
    add_item(({"floor","carpet"}),"It is made of fine wool.\n");
    add_exit(NOBLE(aemilius/m18),"west",0,-1,-1);
    add_exit(NOBLE(aemilius/m19),"southwest",0,-1,-1);
    add_exit(NOBLE(aemilius/m16),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/m12),"east",0,-1,-1);
}

