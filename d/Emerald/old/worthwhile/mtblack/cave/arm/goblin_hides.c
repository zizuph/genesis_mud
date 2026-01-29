/* A animal hide - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("hide");
    set_pname("hides");
    add_pname("armours");
    set_short("animal hide");
    set_pshort("animal hides");
    set_long(
        "It is a very simple animal hide. It must have been quite a " +
        "tough beast that had this for it's skin.\n");

    set_adj("animal");

    set_ac(10);
    set_am(({ -1, 0, 1}));
    set_at(A_TORSO);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2000);

}
