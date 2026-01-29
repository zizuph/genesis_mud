/* A chequered shirt - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("shirt");
    set_short("chequered shirt");
    add_pname("armours");
    set_long("A lumberjack would be proud of this.\n");
    add_adj("chequered");

    set_ac(2); /* It is only a shirt, after all. */

    set_am(({ 0, 1, -1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 400);

}
