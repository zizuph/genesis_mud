#include "/d/City/defs.h"

inherit "/std/room";

#define PATH "/d/City/chaos/library/"
object mon;

create_room()
{
	set_short("The Great Library entrance.");
        set_long("The ancient, pitted stone walls seem to wrap around the "+
           "massive steel doors that stand as the only entrance to this "+
           "repository of knowledge.  Worn statues, that now only vaguely "+
           "resemble lions stare down upon all who approach, ever watchful "+
           "for those unworthy to enter the library.\n");
        add_exit(PATH + "hall","enter");

	reset_room();
}

reset_room(arg)
{
	if(!mon)
{
mon = clone_object(PATH + "justin");
mon->move(this_object());
}
}
