/*
 * Scalemail worn by the haradrim captains
 * -- Finwe, July 2005
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_armour() 
{
    FIX_EUID
    set_name(({"scalemail","scale mail","mail"}));
    set_pname("scalemails");
    add_pname("mails");
    set_short("steel scalemail");
    set_pshort("steel scalemails");
    set_adj("steel");
    add_adj("scale");
    set_long("This is a steel scalemail common to the elite soldiers of " +
        "Harad. It is made of overlapping scales of steel and riveted to " +
        "a hard leather backing. It is polished and shines in the light.\n");
    add_item(({"scales"}),
        "Theu are rounded and made of steel. They overlap each other " +
        "and are secured to a leather back.\n");
    add_item(({"back", "leather back", "leather"}),
        "This is a piece of tanned leather. It is hardened and has " +
        "the scales attached to it\n");

    set_default_armour(35,A_BODY,0,0);
    add_prop(OBJ_I_WEIGHT,9500);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(200)-100);
}
