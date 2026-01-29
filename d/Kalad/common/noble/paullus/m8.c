inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In a washroom of the House of Paullus");
    set_long("You find yourself in a large wash room. Here, many "+
    "poor peasants labor at wooden buckets washing the clothes "+
    "of the royal family. There are lines of clothes everywhere, "+
    "drip drying in the hot Kalad sun that beams through the "+
    "many windows in this room. To the east, you can hear "+
    "cooking noises, while to the south and west, you see "+
    "hallways.\n");
  
    add_item("peasants","Dirty peasents scrubbing clothes clean.\n");
    add_item("buckets","Large wooden buckets filled with soapy water.\n");
    add_item("windows","You see many windows that let the sun in.\n");
    add_item("lines","Strings with clothes haning from them.\n");
    add_item("clothes","Clothes that are dripping wet from every line "+
    "in the room.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m7),"east",0,-1,-1);
    add_exit(NOBLE(paullus/m9),"west",0,-1,-1);
    add_exit(NOBLE(paullus/m5),"south",0,-1,-1);
}
