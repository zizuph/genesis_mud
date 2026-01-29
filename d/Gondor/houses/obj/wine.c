/*
 * OBJ + wine.c
 *
 * Varian - Feb 2020
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/defs.h"
#include "defs.h"

inherit "/std/drink";

int do_sip(string str);

void
create_drink() 
{
    set_name("bottle_of_wine");
    add_name( ({"wine", "bottle of wine", "bottle of red wine", 
        "red wine", "bottle"}) );
    set_pname( ({"wines", "bottles of wine", "bottles of red wine", 
        "red wines", "bottles"}) );

    set_short("bottle of red wine");
    set_pshort("bottles of red wine");
    set_adj("red");
    set_long("This is a bottle of the finest red wine, you " +
        "might want to take a sip to test the flavour.\n");

    set_soft_amount(100);
    set_alco_amount(50);

    add_prop(OBJ_I_WEIGHT, 54);
    add_prop(OBJ_I_VOLUME, 54);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(50));
}

init()
{
    ::init();
    add_action("do_sip", "sip");
}

int
do_sip(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Sip what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Sip what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("Bringing the bottle of red wine up to your " +
            "lips, you take a small tip to tase the robust " +
            "flavour.\n");
        SAYBB(" takes a sip of red wine.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("But... you don't have anything to sip?\n");
        return 1;
    }

    notify_fail("Sadly, you failed to sip the bottle of wine.\n");
    return 0;
}