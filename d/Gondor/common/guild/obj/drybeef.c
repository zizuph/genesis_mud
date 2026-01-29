/*
 * drybeef.c - dried beef for the Rangers
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";

#include <stdproperties.h>

public void
create_food() 
{
    set_name( ({ "beef", "piece", }) );
    set_pname( ({ "pieces of beef", "beef", "pieces", "beeves", }) );
    set_adj( ({ "dried", "piece", "of", }) );
    set_short("piece of dried beef");
    set_pshort("pieces of dried beef");
    set_long("This is a piece of dried beef, a delicacy for the traveller.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME,  80);
}
