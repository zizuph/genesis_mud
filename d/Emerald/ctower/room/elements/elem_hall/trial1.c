#include "../../ctower.h"

inherit ELEMSTD;

void
ctower_reset()
{
    object globe;
  
    if (!present("ctower_globe") && 
        (globe = clone_object(CTOWER_OBJ + "black_globe")))
    {
        globe->set_color("blue");
        globe->move(this_object(), 1);
    }
}

void
create_element()
{
    add_exit(CTOWER_ROOM_ELEM + "elem6", "east");
    ctower_reset();
}
