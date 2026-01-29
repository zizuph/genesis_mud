/* 
 * File: stud_arm.c
 * Leather armour, worn by elves in Qualinesti.
 *
 * Blizzard, 02/2003
 */
 
inherit "std/armour.c";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("armour");
    set_pname("armours");
    set_short("studded elven armour");
    set_pshort("studded elven armours");
    add_adj(({ "studded", "elven", "leather" }));
    set_ac(27);
    set_am( ({-1,2,-1}) );
    set_at(A_BODY);
    set_long("This studded leather armour has little in common with " +
        "normal leather armour. Instead of a hardened shell, studded " +
        "leather offers hundreds of metal rivets affixed to a supple " +
        "backing. The numerous studs form a flexible coat of metal " +
        "that helps to turn aside slashing and cutting attacks, while " +
        "the leather is little more than a means of securing rivets " +
        "in place.\n");
    add_item(({ "rivets", "studs", "rivet", "stud" }),
        "Metal studs has been set in hard leather, making the armour " +
        "a bit more resistant to hits.\n");
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 8500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}
