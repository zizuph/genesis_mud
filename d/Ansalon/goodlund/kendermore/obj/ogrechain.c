/* Chainmail cuirass for Vincint the ogre, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cuirass");
    add_name("vest");
    set_adj("chainmail");
    set_short("chainmail vest");
    set_long("This is a vest of steel chainmail. It has interlocking rings " +
        "of steel, and a layer of leather underneath. This vest looks " + 
        "quite large, large enough to fit an ogre.\n");
    set_am(({1,1,-2}));
    set_ac(27);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 4000);
}

