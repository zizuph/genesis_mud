/*
 * Glass of water - /d/Gondor/rhovanion/dolguldur/obj/water.c
 *
 * Varian - November 2020
 */

#pragma strict_types
#include <stdproperties.h>
#include <formulas.h>

inherit "/std/drink";

void
create_drink() 
{
	set_name("water");
    set_pname("waters");
    set_short("cool glass of water");
    set_pshort("cool glasses of water");
    set_adj( ({"cool", "glass"}) );
    set_long("This is just a cool glass of ordinary water, "
        + "perfect for quenching your thirst.\n");
    set_soft_amount(100);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 8);
}