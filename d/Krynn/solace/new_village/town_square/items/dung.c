/*A Pile Of Dung
*Created by Leia
*June 04, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <std.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("_dung_for_dirtying");
    add_name("dung");
    add_name("pile");
    set_adj("pile");
    set_adj("of");
    set_short("pile of dung");
    set_long("This is a rather large pile of dung. The stench from this particular pile is extremely overwhelming and flies buzz about it contentedly.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 500); 	
    add_prop(OBJ_I_VOLUME, 1000);
}