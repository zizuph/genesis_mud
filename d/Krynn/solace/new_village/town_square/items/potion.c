/*
*  Thimah's Cleansing Potion
*  Created By Leia
*  June 10, 2005
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
    set_name("_potion_for_cleansing");
    add_name("potion");
    set_adj("small");
    set_adj("greenish");
    set_short("small greenish potion");
    set_long("This is a small greenish potion. It was created by Thimah, the shaman, to cleanse the fountain of Solace with. Perhaps you should empty it into the fountain.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 100); 	
    add_prop(OBJ_I_VOLUME, 10);
}