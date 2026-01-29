/* Brigandine armour for Jane the Mercenary, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("coat");
    set_adj("brigandine");
    set_short("brigandine coat");
    set_long("This is a coat of brigandine armour. It has two layers of " +
        "leather, and fairly large pieces of rectangular metal sandwiched " + 
        "and riveted in between. The metal pieces have slightly rounded " + 
        "edges, to prevent cutting through the leather. It looks like " + 
        "good protection against sharp weapons.\n");
    set_am(({1,1,-2}));
    set_ac(23);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 4000);
}

