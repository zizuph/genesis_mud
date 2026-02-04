/*  Workmens gloves for farm2 -- Tomas Jan 2000 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <ss_types.h>       
#include <tasks.h>  
#include <formulas.h>
    

void
create_terel_armour()
{
    set_name("gloves");
    set_short("pair of thick leather gloves");
    set_pshort("pairs of thick leather gloves");
    set_adj("leather");
    add_adj(({"worn", "thick", "grimy"}));
    set_long("The grimy gloves are covered in dirt stains. " +
       "The leather looks worn but still quite thick.\n");

    set_armour_size(ANY_SIZE);
    set_default_armour(10, A_HANDS, 0, 0);
    set_am(({ 2, -1, -1}));
    set_af(this_object());
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 100);
}


