/*
 * OBJ + nuts.c
 *
 * Varian - Jan 2020
 */

#pragma strict_types

#include <stdproperties.h>
#include <formulas.h>

inherit "/std/object";
inherit "/lib/keep";

void
create_object() 
{
    set_name("bree_h1_deed");
    add_name("deed");
    add_adj( ({"house", "paper"}) );

    set_short("paper house deed");
    set_long("This paper is the deed for your house " +
    	"in Bree. Don't lose this, or else you won't " +
    	"be able to get into your own house!");

    set_keep(1);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VALUE,   0);
}