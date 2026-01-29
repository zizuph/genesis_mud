
/*
 * Ceremonial Drum
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
    set_name(({"ceremonial drum","drum"}));
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
    say(QCTNAME(this_player())+" drums on a ceremonial drum.\n");
    tell_room(environment(this_player()),"The sound of the ceremonial drum penetrates "+
        "you to your very soul.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_drum,"drum");
}
