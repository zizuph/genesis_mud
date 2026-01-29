/*
	*Leather cap for the woodsmen of Archet
	*Altrus, June 2005
*/

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("hood");
    add_adj(({"long","leather"}));
    set_short("long leather hood");
    set_pshort("long leather hoods");
    set_long("This leather hood fits loosely over the head, and drapes slightly, front and back, to cover the neck.\n");
    set_ac(20 + random(10));
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD | A_NECK);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 100 + random(50));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
}
