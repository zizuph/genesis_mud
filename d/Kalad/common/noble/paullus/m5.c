inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In a hallway of the House of Paullus");
    set_long("You are now in a short hallway. There are candles on "+
      "the wall, lighting the way. A decorative fullplate of armour "+
      "stands here.\n");

    add_item("candles","They flicker in the slight breeze.\n");
    add_item(({"armour","fullplate","decorative fullplate"}),
      "An empty suit of fullplate armour is stood up here, made to "+
      "look like someone is in it. You open up the visor and find "+
      "no one in there, though. Clutched in its hands is an ancient "+
      "sword.\n");
    add_item(({"ancient sword","sword"}),"An old looking sword, "+
      "you notice some words written on the blade.\n");
    add_item("words","They read: Wistfellow the IV.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m8),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m1),"south",0,-1,-1);
}

