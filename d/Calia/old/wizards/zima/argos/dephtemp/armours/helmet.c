/* Helmet of a guard in the temple of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95    Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void
create_armour()
{
    set_name(({"helmet","silver helmet","dephonian helmet"}));
    set_adj("silver");
    set_adj("dephonian");
    set_short("dephonian helmet");
    set_long(break_string(
       "It is a silver helmet worn by the guards of the Temple of " +
       "Dephonia. A raven with wings outspread is cast on the helm.\n",70));
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
