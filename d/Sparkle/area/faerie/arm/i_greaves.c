/*
 * Iron greaves for faerie npcs
 * By Finwe, April 2005
 */

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 7+random(5)
create_armour()
{
    set_name("greaves");
    add_name("pair of sturdy iron greaves");
    set_name("sturdy iron greaves");
    set_pname("pairs of sturdy iron greaves");
    set_pname("pairs of sturdy iron greaveses");
    set_adj("sturdy");
    set_adj("iron");
    set_short("pair of sturdy iron greaves");
    set_pshort("pairs of sturdy iron greaves");
    set_pshort("pairs of sturdy iron greaveses");

    set_long("These are a pair of sturdy iron greaves. They are forged " +
        "from iron and look strong. The iron greaves fit over the legs " +
        "and protect them during battle. \n");
    	
    set_ac(AC);
    set_at( A_LEGS);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1500);
    
}
