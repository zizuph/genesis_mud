inherit "/d/Shire/room";

#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"


create_room() {
    set_short("Dark room in the downs");
    set_long(
	  "You are inside the Barrow downs.\n"
	+ "It is wet, cold and gloomy.\n"
	+ "The pit continues to the north, south, and east.\n");

    add_item(({"pit",}), break_string(
	  "You are IN a pit."
	+ "It continues both north and south.\n",70));
	
	add_exit(DOWNS_DIR + "stone2_3", "north");
	add_exit(DOWNS_DIR + "stone2_1", "south");
	add_exit(DOWNS_DIR + "stone2", "east");
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    reset_room();       
}


reset_room() {
	object wight, torch;
    int i;


	if(!present("torch"))
        torch = clone_object(STAND_PARENT + "obj/shoptorch")->move(this_object());
    if (!present("wight"))
    {
        for (i=1; i<=3; i++ )
        wight = clone_object(DOWNS_DIR + "npc/g_wight")->move(this_object());
      tell_room(TO,"A grey barrow wight claws its way to the surface.\n");
    }
}
