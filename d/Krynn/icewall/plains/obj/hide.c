/* 
 * 2005-01-05 - Cotillion
 * - Made it decay if left in a room.
 */ 

inherit "/std/object.c";
#include "/d/Krynn/common/defs.h"
#include <macros.h>

static int decay_alarm;

void
create_object()
{
    set_short("thanoi hide");
    set_name("hide");
    add_name("thanoi_hide");
    set_pname("hides");
    set_long("This is a hide from one of the walrus-men called " +
        "Thanoi. It is very thick, and perhaps after some drastic " +
        "perfuming, it would make a good sleeping fur, coat, or tent "+
        "for someone who lives in a very cold climate.\n");
    
    add_prop(OBJ_I_VALUE, 43);    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 1000);
}

void
decay()
{
    tell_room(environment(),
        "The " + short() + " decays.\n");
    remove_object();
}

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (ob->query_prop(ROOM_I_IS))
    {
        if (!get_alarm(decay_alarm))
        {
            decay_alarm = set_alarm(3600.0 * rnd(), 0.0,
                &decay());
        }
    }
    else
    {
        remove_alarm(decay_alarm);
    }
    
}



