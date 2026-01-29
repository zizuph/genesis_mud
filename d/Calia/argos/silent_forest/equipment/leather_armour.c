/*   leather_armour.c
 *
 *  Just a standard leather armour.
 *
 * Baldacin@Genesis, Sep 2003
 */
inherit "/std/armour";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() 
{
    set_name("armour");
    set_adj(({"hardened","leather"}));
    set_short("hardened leather armour");
    set_long("This piece of leather armour has been hardened to "+
      "enhance its defensive properties. Alas, it does not seem "+
      "to protect you very well.\n");
    set_ac(15);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}
