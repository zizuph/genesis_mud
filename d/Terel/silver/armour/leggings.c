/* File         : /d/Terel/silver_new/armour/leggings.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Rommenus Leggings
 * Related Files: 
 * Comments     : 
 * Modifications: 
 */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 15

void
create_armour()
{
    set_name("armour");
    add_name("leggings");

    set_adj("leather");

    set_short("pair of leggings");
    set_long("A simple leather leggings, giving basic protection " +
             "for your legs.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
