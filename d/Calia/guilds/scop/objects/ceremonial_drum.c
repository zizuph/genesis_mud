
/*
 * Ceremonial Drum
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
    set_name(({"ceremonial drum","drum"}));
    add_name(CEREMONIAL_GARB);
    set_adj("ceremonial");
    set_short("ceremonial drum");
    set_long("It is a small drum used for ceremonial purposes.\n"+
        "You could probably drum on it. <drum drum>\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_drum(string str)
{
    if (!str && str != "drum")
    {
        return 0;
    }

    write("You drum on the ceremonial drum.\n");
    say(QCTNAME(TP)+" drums on a ceremonial drum.\n");
    tell_room(environment(TP),"The sound of the ceremonial drum penetrates "+
        "you to your very soul.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_drum,"drum");
}
