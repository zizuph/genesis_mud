
/*
 * Ceremonial Bell
 * No value
 * Only used for ceremonies
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_object() 
{
    set_name(({"ceremonial bell","bell"}));
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
    say(QCTNAME(this_player())+" rings a ceremonial bell.\n");
    tell_room(environment(this_player()),"The sound of the ceremonial bell rings "+
        "pleasantly in your ears.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_ring,"ring");
}
