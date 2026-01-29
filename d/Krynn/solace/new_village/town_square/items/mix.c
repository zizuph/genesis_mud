/*
*  Zahrtok's Dirtying Mix
*  Created By Leia
*  June 16, 2005
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
    set_name("_mix_for_dirtying");
    add_name("mix");
    set_adj("large");
    set_adj("bag of");
    set_short("large bag of mix");
    set_long("This is a large bag of mix. It was created by Zahrtok, the slave driver, to make the fountain of Solace dirty again. Perhaps you should dump it into the fountain.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 1000); 	
    add_prop(OBJ_I_VOLUME, 100);
}