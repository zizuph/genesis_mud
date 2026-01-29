/*
 * Plain cotton pants
 * -- Finwe, December 2015
 */

inherit "/std/armour";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("pants");
    set_short("pair of cotton pants");
    set_pshort("pairs of cotton pants");
    add_adj("plain");
    add_adj("cotton");
    set_long("This is a pair of plain cotton pants. They are of clean but well worn.\n");

    set_ac(8);
    set_am(({0,0,0,}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
}
