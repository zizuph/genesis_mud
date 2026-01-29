/* 
 *  /d/Gondor/std/drink/whiskey.c:  
 *
 *  Soft 120 ml, alco 36 ml, price 144 cc.
 *  Drink for the Restful Hearth Inn (common/guild/north/inn.c)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_drink() 
{
    set_name("whiskey");
    set_adj("dry");
    set_short("glass of whiskey");
    set_pshort("glasses of whiskey");
    set_long(BS("The dry whiskey is of a golden-brownish colour and "+
    "has a strong smell to it. It was distilled by Brandybucks of the "+
    "West-farthing.\n"));
    set_soft_amount(120);
    set_alco_amount(36);
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 120);
    add_prop(OBJ_I_VALUE,    0);
}

