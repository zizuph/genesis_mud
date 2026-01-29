inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */
object obj;
object obj2;
void reset_room();

void
create_room()
{
    set_short("In the gardens of House Aemilius");
    set_long("You have entered the begining of the beautiful gardens "+
      "of this estate. All around you, trees and flowers grow, giving "+
      "the air around you a sweet smell. The entrance to the mansion "+
      "is right here in front of you.\n");
    add_item("flowers","They are of every kind and color, and dot the "+
      "yard in attractive patterns.\n");
    add_item("trees","The grow around the yard in clusters, providing "+
      "nice groves of shade.\n");
    add_item("estate","The grand estate lies here.\n");
    add_item(({"entrance","grand entrance"}),"A pair of huge double "+
      "doors made of expensive oak mark the entrance to the grand estate "+
      "of this mansion. Flags hang over it.\n");
    add_item("flags","They are Red flags with the emblem of "+
      "the House of Aemilius marked on them.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(aemilius/g4),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/g2),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m1),"west",0,-1,-1);
    add_exit(NOBLE(aemilius/g1),"east",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!obj)
    {
	obj = clone_object(NOBLE(npc/house_guard));
	obj->set_house_name("Aemilius");
	obj->set_color_name("red");
	obj->arm_me();
	obj->move_living("xxx",TO);
    }
    if(!obj2)
    {
	obj2 = clone_object(NOBLE(npc/house_guard));
	obj2->set_house_name("Aemilius");
	obj2->set_color_name("red");
	obj2->arm_me();
	obj2->move_living("xxx",TO);
    }  
    obj->team_join(obj2);
}

