/*
plain_stone.c

A plain stone, created for the Highbulp, looks like the magic stone, but does nothing.

Created by Arcturus
16.05.2005

*/

#include "/sys/macros.h"  
#include "/sys/stdproperties.h"   /* We want to use standard properties */
#include "/d/Ansalon/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Ansalon/kalaman/sewers/local.h"
#include <filter_funs.h>

inherit "/std/object";

void
create_object()
{
    set_name("stone");
    set_adj("small");
    add_adj("shiny");
    set_short("small shiny stone");
    set_pshort("small shiny stone");
    
    set_long("The stone looks like an ordinary stone.\n");
    
    add_prop(OBJ_M_NO_SELL, "The shopkeeper doesn't intend to buy a stone. ");
    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 40);

    seteuid(getuid(TO));
        
}

