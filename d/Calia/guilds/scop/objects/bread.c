
/*
 * Ceremonial Bread
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
 
int fed = 0;

void create_object() 
{
    set_name(({"ceremonial bread","bread"}));
    add_name(CEREMONIAL_GARB);
    set_adj("ceremonial");
    set_short("ceremonial bread");
    set_long("It is ceremonial bread used for ceremonial purposes.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_feed(string str)
{
    if (!str)
    {
        NF("Feed whom the ceremonial bread?\n");
        return 0;
    }

    if (!present(lower_case(str),environment(TP)))
    {
        NF("That person is not here!\n");
        return 0;
    }

    if (fed == 1)    // You can only feed twice
    {
        write("You feed "+capitalize(str)+" the last piece of ceremonial "+
            "bread.\n");
        say(QCTNAME(TP)+" feeds "+capitalize(str)+" the last piece of "+
            "ceremonial bread.\n");
        TO->remove_object();
        return 1;
    }

    else     
    {
        write("You feed "+capitalize(str)+" a piece of ceremonial bread.\n");
        say(QCTNAME(TP)+" feeds "+capitalize(str)+" a piece of ceremonial "+
            "bread.\n");
        fed += 1;
    }
    
    return 1;
}

void
init()
{
    ::init();
    add_action(do_feed,"feed");
}
