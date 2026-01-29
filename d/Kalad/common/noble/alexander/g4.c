inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    set_short("In the gardens of House Alexander");
    set_long("You have entered the begining of the beautiful gardens "+
      "of this estate. All around you, trees and flowers grow, giving "+
      "the air around you a sweet smell. The garden-yard extends to "+
      "north and northwest. There is large ivy growing on the walls "+
      "here.\n");
    add_item("ivy","The ivy looks strong, and you see it snakes up "+
      "the wall to a small open window.\n");
    add_item("window","A small window that looks open. The ivy leads "+
      "up to it, making you think you could get up there if you "+
      "tried.\n");
    add_item("flowers","They are of every kind and color, and dot the "+
      "yard in attractive patterns.\n");
    add_item("trees","The grow around the yard in clusters, providing "+
      "nice groves of shade.\n");
    add_item("estate","The grand estate lies off to your north.\n");
    add_item(({"entrance","grand entrance"}),"A pair of huge double "+
      "doors made of expensive oak mark the entrance to the grand estate "+
      "of this mansion. Flags hang over it.\n");
    add_item("flags","They are Black flags with the emblem of "+
      "the House of Alexander marked on them.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(alexander/g3),"north",0,-1,-1);
    add_exit(NOBLE(alexander/g1),"northwest",0,-1,-1);
}

void
init()
{
    ::init();
    AA(do_climb,climb);
}

int
do_climb(string str)
{
    NF("Climb what?\n");
    if(str != "ivy")
	return 0;
    write("You climb up the wall and pull yourself into the window.\n");
    say(QCTNAME(TP)+" climbs up the wall and into a window.\n");
    TP->move_living("M",NOBLE(alexander/m19));
    tell_room(E(TP),QCTNAME(TP)+" plops out of the window.\n",TP);
    return 1;
}

