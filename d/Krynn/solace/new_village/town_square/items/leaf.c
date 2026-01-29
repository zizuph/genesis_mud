/*
*A Vallenwood Leaf
*Created By Leia
*June 03, 2005
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
    set_name("_leaf_for_cleansing");
    add_name("leaf");
    set_adj("large");
    set_adj("vallenwood");
    set_short("large vallenwood leaf");
    set_long("This is a large vallenwood leaf. It is dark green in color and has pointed edges. The vallenwood leaves are regarded highly by certain tribes of plainsmen as a cleansing ingredient.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 5); 	
    add_prop(OBJ_I_VOLUME, 1);
}