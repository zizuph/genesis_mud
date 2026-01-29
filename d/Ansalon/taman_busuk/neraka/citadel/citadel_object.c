#include "/d/Ansalon/common/defs.h"
#include <macros.h>
inherit "/std/object";

#define CITDIR(x) "/d/Ansalon/taman_busuk/neraka/citadel/x"

object linked_room;

void
create_object()
{
    if(sizeof(object_clones(find_object(CITDIR(citadel_object)))) > 1)
    {
        tell_room(E(TO),"Sorry, there is already a citadel about.\n");
        write("Sorry, there is already a citadel about.\n");
        tell_object(previous_object(),"Sorry, there is already a citadel "+
         "about.\n");
        remove_object();
        return;
    }
    set_name("citadel");
    set_adj("floating");
    set_short("floating citadel");
    set_long("You gaze upon a fearsome sight. Above you in the sky, is a "+
    "castle ripped from its foundations and suspended in mid-air. You see "+
    "lights and figures moving around, just like you would if this castle "+
    "was on the ground.\n");
    add_prop(OBJ_M_NO_GET,"Are you insane?\n");
}

object
query_linked()
{
    return linked_room;
}

void
link_citadel(object ob)
{
    if(MASTER_OB(ob) == CITDIR(pioletr))
        linked_room = ob;
}

