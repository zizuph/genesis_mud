/*
 * a piece of coal for the holidays
 * -- Finwe December 2005
 */

#pragma save_binary
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";


create_object()
{
    set_name(({"coal","_shire_coal", "lump of coal"}));
    set_pshort("lumps of coal");
    set_adj(({"large", "lump"}));
    set_short("large lump of coal");
    set_pshort("large lumps of coal");
    set_long("This is a large lump of dark coal. It's give out at the holidays to people who are undeserving of gifts.\n");

 /* Some properties of this hammer */
   add_prop(OBJ_I_WEIGHT, 400); 
   add_prop(OBJ_I_VALUE, 7);  
   add_prop(OBJ_I_VOLUME, 90); 
}
