inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    set_short("In the gardens of House Paullus");
    set_long("You have entered the begining of the beautiful gardens "+
      "of this estate. All around you, trees and flowers grow, giving "+
      "the air around you a sweet smell. The garden-yard extends to "+
      "your north, northeast, and northwest, while you can see the "+
      "grand entrance to the estate further to the north.\n");
    add_item("flowers","They are of every kind and color, and dot the "+
      "yard in attractive patterns.\n");
    add_item("trees","The grow around the yard in clusters, providing "+
      "nice groves of shade.\n");
    add_item("estate","The grand estate lies off to your north.\n");
    add_item(({"entrance","grand entrance"}),"A pair of huge double "+
      "doors made of expensive oak mark the entrance to the grand estate "+
      "of this mansion. Flags hang over it.\n");
    add_item("flags","They are Red and Gold flags with the emblem of "+
      "the House of Paullus marked on them.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(paullus/g3),"north",0,-1,-1);
    add_exit(NOBLE(paullus/g2),"northeast",0,-1,-1);
    add_exit(NOBLE(paullus/g4),"northwest",0,-1,-1);
    add_exit(NOBLE(road/r10),"south",0,-1,-1);
}

