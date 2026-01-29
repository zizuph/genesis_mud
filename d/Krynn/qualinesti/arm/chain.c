/* 
 * File: lchain.c
 * An elven chain mail, worn by scouts in Qualinesti.
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
    add_name(({ "mail", "chain", "armour" }));
    add_pname(({ "mails", "chains", "armours" }));
    set_short("elven chain mail");
    set_pshort("elven chain mails");
    add_adj(({ "chain", "light", "elven" }));
    set_ac(33);
    set_am( ({-2,2,0}) );
    set_at(A_BODY);
    set_long("The delicate yet sturdy craftsmanship of the elven " +
        "races allows them to design many beautiful yet utilitarian " +
        "goods. Among these is elven chain mail, which is so finely " +
        "wrought that can be worn under normal clothing without " +
        "revealing its presence. The chain links seem to be seamlessly " +
        "linked; an indication of a very well constructed piece of " +
        "armour.\n");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31));
}
