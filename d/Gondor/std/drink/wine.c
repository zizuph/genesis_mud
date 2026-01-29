/* 
 *  /d/Gondor/std/drink/wine.c:  
 *
 *  Soft 100 ml, alco 16 ml, price 36 cc.
 *  Drink for The Restful Hearth Inn (common/guild/north/inn.c)
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_drink() 
{
    set_name("wine");
    set_pname("wines");
    set_adj("red");
    set_short("glass of red wine");
    set_pshort("glasses of red wine");
    set_long("The wine has a rich red colour and comes from "+
        "Merrydown in Shire.\n");
    set_soft_amount(100);
    set_alco_amount(16);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,    0);
}
