
/*
 * Holy Chalice
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
    set_name(({"holy chalice","chalice"}));
    add_name(CEREMONIAL_GARB);
    set_adj("holy");
    set_short("holy chalice");
    set_long("It is a holy chalice used for ceremonial purposes.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}

int
do_sip()
{
    write("You take a sip of clear water from holy chalice.\n");
    say(QCTNAME(TP)+" takes a sip from the holy chalice.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_sip,"sip");
    add_action(do_sip,"drink");
}
