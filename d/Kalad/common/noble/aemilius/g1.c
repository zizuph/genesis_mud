inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    set_short("In the gardens of House Aemilius");
    set_long("You have entered the begining of the beautiful gardens "+
      "of this estate. All around you, trees and flowers grow, giving "+
      "the air around you a sweet smell. The garden-yard extends to "+
      "your west, northwest, and southwest, while you can see the "+
      "grand entrance to the estate further to the west.\n");
    add_item("flowers","They are of every kind and color, and dot the "+
      "yard in attractive patterns.\n");
    add_item("trees","The grow around the yard in clusters, providing "+
      "nice groves of shade.\n");
    add_item("estate","The grand estate lies off to your west.\n");
    add_item(({"entrance","grand entrance"}),"A pair of huge double "+
      "doors made of expensive oak mark the entrance to the grand estate "+
      "of this mansion. Flags hang over it.\n");
    add_item("flags","They are Red flags with the emblem of "+
      "the House of Aemilius marked on them.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(aemilius/g3),"west",0,-1,-1);
    add_exit(NOBLE(aemilius/g2),"northwest",0,-1,-1);
    add_exit(NOBLE(aemilius/g4),"southwest",0,-1,-1);
    add_exit(NOBLE(road/r12),"east",0,-1,-1);
}

