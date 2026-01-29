#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void reset_room();

object box;

void
create_room()
{
    set_short("A newly built warehouse");
    set_long("\n"+
        "This warehouse is modern and very well built.\n"+
        "It contains sacks of grain and flour.\n"+
        "A large blue charity box stands in a corner.\n"+
        "");

       add_item(({"sacks" }),"");
       add_item(({"box" }),"This is where charity and handouts are put.\n"+
        "Anything put in the box is free for anyone else to get.\n"+
        "");
       add_item(({"room" }),"It is quite modern.\n"+
        "");

    add_exit(TOWN_DIR + "pier5","north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);


    box = clone_object(OBJ_DIR + "box");
    box->set_long("This is where charity and handouts are put.\n"+
		 "Anything put in the box is free for anyone else to get.\n");
    box->move(this_object());

    reset_room();
}

void
reset_room()
{
    int i;

    if (!box || present("newbie knife", box))
        return;

    for(i = 0; i < 4; i++)
	clone_object(OBJ_DIR + "newbie_knife")->move(box);
}
