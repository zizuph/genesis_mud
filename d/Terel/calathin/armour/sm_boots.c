/* 
 *  A pair of boots for Calathin citizens.
 *  By Shinto 11-2-98
 *  Added adj. small  -- Tomas  Jan. 2000
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>
#include <stdproperties.h>

public void
create_terel_armour()
{
    set_name("boots");
    add_name("small boots");
    set_short("pair of small black boots");
    set_pshort("pairs of small black boots");
    set_adj(({"small","black"}));
    set_long("A "+short()+" mostly worn by halflings.\n");

    set_default_armour(20, A_FEET, 0, 0);
    set_armour_size(SMALL);


    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,   50);
}


