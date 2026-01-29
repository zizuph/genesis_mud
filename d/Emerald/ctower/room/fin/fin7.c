#include "../../ctower.h"

inherit FINSTD;

#include <language.h>

void
ctower_reset()
{
    object globe;
    if (globe = clone_object(CTOWER_OBJ + "black_globe"))
    {
    	globe->set_color("red");
    	globe->move(this_object(), 1);

        tell_room(this_object(), LANG_ASHORT(globe) + " floats in.\n");
    }
}
 
void create_fin()
{
    add_exit(CTOWER_ROOM_FIN + "fin8", "east");
    ctower_reset();
}
