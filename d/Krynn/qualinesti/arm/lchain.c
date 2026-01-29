/* 
 * File: lchain.c
 * Elven chainmail, worn by elves in Qualinesti.
 *
 * Blizzard, 02/2003
 */
 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    add_name(({ "mail", "armour" }));
    add_pname(({ "mails", "armours" }));
    set_short("elven chainmail");
    set_pshort("elven chainmails");
    add_adj(({ "light", "elven" }));
    set_ac(30);
    set_am( ({-2,2,0}) );
    set_at(A_BODY);
    set_long("The chainmail is constructed of high-quality metal and, " +
        "like most things of elven make, is lightweight and of little " +
        "burden. However, it covers the entire torso quite well. The " +
        "chain links seem to be seamlessly linked, an indication of a " +
        "very well constructed piece of armour.\n");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
}
