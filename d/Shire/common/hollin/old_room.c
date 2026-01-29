inherit "/std/room";
/* inherit "near_lake"; */

#include "defs.h"

create_room() {
		set_short("Steep mountain path");
		set_long(
        "You're climbing a steep north-south mountain path.\n"+
        "   It winds up towards a peak under a greater mountain.\n"+
        "It looks like there might be a wonderful view up there, but\n"+
        "it is hard to tell whether it is possible to get there from\n"+
        "here.\n");
		add_item("path","It is rather steep.\n");
		add_item(({"peak","mountain"}),"You might try further up to the north.\n");
		EXIT("rom5","north");
		EXIT("rom3","south");
}
