/*
 * Food for hunter's club
 * Coded by Finwe, December 2017
 */
#include </stdproperties.h>
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("strip");
    set_adj("jerky");
    set_short("jerky strip");
    set_long("This is a piece of jerky. It is a thick strip of venison that " +
        "has been smoked and dried over a hickory fire.\n");
    add_name("jerky");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE,35); 
}
