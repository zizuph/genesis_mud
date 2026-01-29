/* Practice tunic for Gelnor the Gruff
 * of Wayreth Tower
 * Created by: Kentari 01/97
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

void
create_armour()
{
    set_name("tunic");
    set_ac(21);
    set_at(A_BODY);
    set_adj(({"gray","practice"}));
    set_short("gray practice tunic");
    set_pshort("gray practice tunics");
    set_long("Made of a comfortable gray material, these are " +     
             "perfect for hours of practicing and sweating. " +        
             "You notice an extremely light, yet strong mesh " +          
             "of metal on the inside of the tunic, which " +             
             "must provide wonderful protection against blades.\n");
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21) + 200);
}

