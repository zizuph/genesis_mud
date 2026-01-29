

inherit "/std/room";
#include <stdproperties.h>

#define NUM 1

reset_room(arg)
{
    object *dwolf;
    int i;
    dwolf = allocate(NUM);
    if(present("wolf"))
	return;
    for(i = 0; i < NUM; i++)
    {
	dwolf[i]=clone_object("/d/Terel/mountains/obj/dwolf");
	dwolf[i]->move(this_object());
    }
}

create_room(){
    set_short("Cave");
    set_long(
 "This dark cavern is filled with long icicles that hang from the ceiling\n"
+"down to the cavern floor. A large mat of weeds is strewn about. Fragments\n"
+"of bone are littered throughout.\n"
	     );
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Terel/mountains/ice3", "southeast", 0);
    reset_room();
}
