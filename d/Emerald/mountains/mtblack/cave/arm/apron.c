/* A leather apron - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("apron");
    set_pname("aprons");
    add_pname("armours");
    set_short("leather apron");
    set_pshort("leather aprons");
    set_long(
        "Its an ordinary looking leather apron. All good cooks have one.\n");

    add_adj("leather");

    set_ac(6); /* Not much good */

    set_am(({ 0, 1, -1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 400);

}
