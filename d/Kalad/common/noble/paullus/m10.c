inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("On the balcony of House Paullus");
    set_long("You are now on a balcony overlooking the entrance "+
    "of this grand house. A short hallway leads to a central room "+
    "just off to your north, where you see many doors. Off to your "+
    "west, you see a room. There are two beautiful statues here, "+
   "each depicting a beautiful woman holding a candle that burns "+
    "and illuminates the way. The stairs lead back down.\n");

    add_item("statues","They are of two beautiful tall women with "+
    "very shapely figures. They wear only a skirt and they are bent "+
    "slightly with their hands clasp together holding a candle. They "+
    "are set on either side of the hallway that leads to the central "+
    "room in the north.\n");
    add_item("candles","They burn brightly.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m14),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m12),"west",0,-1,-1);
    add_exit(NOBLE(paullus/m1),"stairs",0,-1,-1);
}
