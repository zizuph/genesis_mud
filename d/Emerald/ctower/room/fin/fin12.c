#include "../../ctower.h"

inherit FINSTD;

#include <language.h>

void
ctower_reset()
{
    object globe;
    if (globe = clone_object(CTOWER_OBJ + "black_globe"))
    {
    	globe->set_color("yellow");
    	globe->move(this_object(), 1);

        tell_room(this_object(), LANG_ASHORT(globe) + " floats in.\n");
    }
}
 
void
create_fin()
{
    add_exit(CTOWER_ROOM_FIN + "fin11", "west");
    ctower_reset();
}
