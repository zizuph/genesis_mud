/* Shield of a guard in the temple of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95    Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void
create_armour()
{
    set_name("shield");
    set_adj("silver");
    set_adj("dephonian");
    set_short("dephonian shield");
    set_long(break_string(
        "A round shield used by the guards of the Temple of Dephonia. " +
        "It is cast of silver with a large raven on the face, " +
        "encircled by a wreath of hemlock leaves.\n",70));
    set_ac(15);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}
