/* 
 *  /d/Gondor/std/drink/dwarfblood.c:  
 *
 *  Soft 100 ml, alco 50 ml, price 288 cc.
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
    set_name("dwarfblood");
    add_name("cup");
    add_pname(({"cups", "dwarfbloods", "cups of dwarfblood", }));
    set_short("cup of dwarfblood");
    set_pshort("cups of dwarfblood");
    set_long("A hot cup of Dwarfblood. The strong smell makes your head spin.\n");
    set_soft_amount(100);
    set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,    0);
}

