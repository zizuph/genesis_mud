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
      "your south and southeast, while the "+
      "grand entrance to the estate is just off to the south.\n");
    add_item("flowers","They are of every kind and color, and dot the "+
      "yard in attractive patterns.\n");
    add_item("trees","The grow around the yard in clusters, providing "+
      "nice groves of shade.\n");
    add_item("estate","The grand estate lies off to your south.\n");
    add_item(({"entrance","grand entrance"}),"A pair of huge double "+
      "doors made of expensive oak mark the entrance to the grand estate "+
      "of this mansion. Flags hang over it.\n");
    add_item("flags","They are Red flags with the emblem of "+
      "the House of Aemilius marked on them.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(aemilius/g3),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/g1),"southeast",0,-1,-1);
}

