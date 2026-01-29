/* Boots of a kretan sentry
**
** HISTORY
** Date       Coder      Action
** ---------- ---------- ----------------------------------
** 1/25/96    Zima       Created
** 8/22/21    Greneth    Changed AC to 15
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("boots");
    add_name(({"pair","pair of boots"}));
    set_adj(({"black","leather","kretan"}));
    set_short("pair of black leather boots");
    set_pshort("pairs of black leather boots");
    set_long(
       "It is a pair of black leather boots with a high military cut.\n");
    set_ac(15);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT,  700);
    add_prop(OBJ_I_VOLUME,  600);
}
