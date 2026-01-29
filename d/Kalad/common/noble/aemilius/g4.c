inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object obj;
void reset_room();

void
create_room()
{
    set_short("In the gardens of House Aemilius");
    set_long("You have entered the begining of the beautiful gardens "+
      "of this estate. All around you, trees and flowers grow, giving "+
      "the air around you a sweet smell. The garden-yard extends to "+
      "your north and northeast, while the "+
      "grand entrance to the estate is just off to the north.\n");
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
    add_exit(NOBLE(aemilius/g3),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/g1),"northeast",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!obj)
    {
	obj = clone_object(NOBLE(npc/special_gardener));
	obj->arm_me();
	obj->move_living("xxx",TO);
    }
}

