inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("A short hall in the House of Aemilius");
    INSIDE;
    set_long("You are now in a short hall connecting to other "+
    "halls. To the east, you see the stairs. There is a bedroom "+
    "to the west, while the rest lead into more halls. There is "+
    "a table here.\n");
    add_item("table","The table is made of black oak, and on it, "+
    "you see a small statue.\n");
    add_item("statue","The statue is made of gold, and it is shaped "+
    "in the likeness of a nude man, with a large...er..well, you "+
    "know.\n");

    add_exit(NOBLE(aemilius/m16),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m19),"northwest",0,-1,-1);
    add_exit(NOBLE(aemilius/m14),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m20),"west",0,-1,-1);
}

