/*
 * Elf Steak - /d/Gondor/rhovanion/dolguldur/obj/steak.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name( ({"steak", "dinner", "steak dinner"}) );
    set_pname( ({"steaks", "dinners", "steak dinners"}) );
    set_short("steak dinner");
    set_pshort("steak dinners");
    set_long("This is a delicious looking serving of elf " +
        "steak, complete with all of the fixings!\n");
    set_amount(260);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE, 260);
}