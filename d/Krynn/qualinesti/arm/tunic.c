/* 
 * File: tunic.c
 * Leather armour, worn by Jakey.
 *
 * Blizzard, 2/06/2003
 */
 
inherit "std/armour.c";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("tunic");
    set_short("studded leather tunic");
    add_adj(({ "studded", "leather" }));
    set_ac(20);
    set_at(A_BODY);
    set_long("This is a vest of thick leather studded with iron rivets. " +
        "It is a little heavy, but will provide good protection in combat.\n");

    add_item(({ "rivets", "studs", "rivet", "stud" }),
        "Metal studs has been set in hard leather, making the armour " +
        "a bit more resistant to hits.\n");
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}
