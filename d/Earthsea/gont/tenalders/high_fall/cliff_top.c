/*
 * coded by Amelia 7/26/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";
inherit "/d/Earthsea/gont/tenalders/high_fall/climb";

#include "caves/defs.h"

private object *kargs = allocate(4);

public void
reset_room()
{
    int i = 4;

    while(i--)
    {
        if(!objectp(kargs[i]))
        {
            kargs[i] = clone_object(KARGS[random(sizeof(KARGS))]);
            kargs[i]->move(this_object());
            kargs[i]->command("emote comes charging out of the cave.");
        }
    }
}

public void
create_earthsea_room()
{
    set_short("Limestone cliff");
    set_long("A ledge at the top of a limestone cliff. " +
        "White mist swirls all around you making it difficult to " +
        "see very far, however, you are able to make out an " +
        "entrance to a cave. For some reason, the cave gives " +
        "you a very bad feeling ...\n");
    set_next_up("on_top");
    set_next_down("/d/Earthsea/gont/tenalders/high_fall/cliff5");
    add_tell("You are surrounded by a cloud of mist.\n");
    add_tell("Mist gets into your eyes, making it difficult to "+
        "see where to put your hands and feet.\n");
    reset_room();
    set_tell_time(30);
    add_exit("caves/cave1", "enter", "@@karg_here");
    reset_room();
}

public int
karg_here()
{
    if(present("karg", this_object()))
    {
        write("The karg won't let you pass.\n");
        return 1;
    }

    write("You stoop down a bit to enter the cave.\n");

    return 0;
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
