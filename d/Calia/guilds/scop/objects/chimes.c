
/*
 * Ceremonial Chimes
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
    set_name(({"ceremonial chimes","chimes"}));
    set_pname(({"ceremonial chimes","chimes"}));
    add_name(CEREMONIAL_GARB);
    set_adj("ceremonial");
    set_short("ceremonial chimes");
    set_pshort("ceremonial chimes");
    set_long("They are a small set of chimes used for ceremonial purposes.\n"+
        "You could probably sound them. <sound chimes>\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_sound(string str)
{
    if (!str && str != "chimes")
    {
        return 0;
    }

    write("You sound the ceremonial chimes.\n");
    say(QCTNAME(TP)+" sounds some ceremonial chimes.\n");
    tell_room(environment(TP),"The sound of the ceremonial chimes echoes "+
        "throughout the area leaving you feeling peaceful.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_sound,"sound");
}
