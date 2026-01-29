inherit "/std/torch";
#include "../../khiraa.h"
#include "../../default.h"

#include <cmdparse.h>

void
create_torch()
{
    set_name("candle");
    set_adj(({"small","black"}));
    set_short("small black candle");
    
    set_long("A small candle completely black in color. Strange "+
    "designs are carved along its rounded sides. It @@longstat@@");

    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,4);
    set_value(12);
    set_strength(1);
    set_time(random(60) + 460);
}

string 
longstat()
{
    if(query_lit(0))
        return "burns with an eerie green light.\n";
    return "is not lighted.\n";
}


public void
burned_out()
{
    object ob = environment();
    string tmp = ::short();

    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);

    if (!objectp(ob))
        return;

    if (living(ob))
    {
        tell_object(ob, "The " + tmp + " flickers, and melts away.\n");
        tell_room(environment(ob), "The " + tmp + " that " +
                QTNAME(ob) + " is holding flickers, and melts away.\n", ob);
    }
    else if (ob->query_prop(ROOM_I_IS))
        tell_room(ob, "The " + tmp + " flickers, and melts away.\n");

    remove_object();
}
