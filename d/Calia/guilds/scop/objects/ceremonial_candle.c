
/*
 * Ceremonial Candle
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
    set_name(({"ceremonial candle","candle"}));
    add_name(CEREMONIAL_GARB);
    set_adj("ceremonial");
    set_short("ceremonial candle");
    set_long("This is a small candle used for ceremonial purposes.\n"+
        "You could probably light it and raise it above your head "+
        "if you wanted. <light candle> <raise candle>\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_light(string str)
{
    if (!str && str != "candle")
        return 0;
    
    if (TO->query_prop(OBJ_I_LIGHT))
    {
        write("The candle is already lit.\n");
        return 1;
    }

    write("You light the ceremonial candle. You can douse it at "+
        "any time. <douse candle>\n");
    say(QCTNAME(TP)+" lights a ceremonial candle.\n");
    TO->add_prop(OBJ_I_LIGHT,1);
    return 1;
}

int
do_douse(string str)
{
    if (!str && str != "candle")
        return 0;

    if (!TO->query_prop(OBJ_I_LIGHT))
    {
        write("The candle is not lit.\n");
        return 1;
    }

    write("You douse the ceremonial candle.\n");
    say(QCTNAME(TP)+" douses "+HIS+" ceremonial candle.\n");
    TO->remove_prop(OBJ_I_LIGHT);
    return 1;
}

int
do_raise(string str)
{
    if (!str && str != "candle")
    {
        NF("Raise what? The candle? <raise candle>\n");
        return 0;
    }

    if (!TO->query_prop(OBJ_I_LIGHT))
    {
        write("You should light it first.\n");
        return 1;
    }

    write("You raise the ceremonial candle above your head for a few "+
        "moments.\n");
    say(QCTNAME(TP)+" raises "+HIS+" ceremonial candle above "+HIS+
        " head for a few moments.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_light,"light");
    add_action(do_douse,"extinguish");
    add_action(do_douse,"unlight");
    add_action(do_douse,"douse");
    add_action(do_douse,"dowse");
    add_action(do_raise,"raise");
}
