/* ARGOS - Temple of Pharos - Bottle of new wine
**
** Pharosian priests can bless bottle of grape juice and turn it
** into this object.
*/
inherit "/std/drink";
#include <stdproperties.h>
#include "defs.h"
 
create_drink() {
    set_name("wine");
    add_name(({"bottle","bottle of wine",ARGOS_NEW_WINE}));
    set_adj("new");
    set_short("bottle of new wine");
    set_pshort("bottles of new wine");
    set_long(
       "It is a bottle of new wine, a little sweet and not very strong.\n");
    set_soft_amount(400);
    set_alco_amount(20);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
