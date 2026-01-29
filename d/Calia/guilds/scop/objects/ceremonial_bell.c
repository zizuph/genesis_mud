
/*
 * Ceremonial Bell
 * No value, can't be taken outside of the temple
 * Only used for ceremonies in the temple
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER
 
void create_object() 
{
    set_name(({"ceremonial bell","bell"}));
    add_name(CEREMONIAL_GARB);
    set_adj("ceremonial");
    set_short("ceremonial bell");
    set_long("This is a small golden bell used for ceremonial purposes.\n"+
        "You could probably ring it. <ring bell>\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_ring(string str)
{
    if (!str && str != "bell")
    {
        return 0;
    }

    write("You ring the ceremonial bell.\n");
    say(QCTNAME(TP)+" rings a ceremonial bell.\n");
    tell_room(environment(TP),"The sound of the ceremonial bell rings "+
        "pleasantly in your ears.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_ring,"ring");
}
