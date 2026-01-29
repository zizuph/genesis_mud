/* ARGOS - Metro - bottle of grape juice
**
** This bottle of grape juice is obtained in rooms/press when a player
** presses grapes into grape juice. It can be blessed by a Pharosian
** priest/ess and turned into new wine
**
** Date     Coder     Action
** -------- --------- -----------------------------------
** 8/25/95  Zim       Created
*1997/1/26  ?         Last update?
*2010/9/02  Lavellan  Fixed "an a bottle...", why was HEAP_I_IS removed anyway?
**
**/
inherit "/std/drink";
#include <stdproperties.h>
#include "defs.h"
 
create_drink() {
    set_name("bottle of grape juice");
    add_name(({"juice","grape juice","bottle of juice","bottle",
               "bottle of grape juice",ARGOS_GRAPE_JUICE}));
    set_short("bottle of grape juice");
    set_pshort("bottles of grape juice");
    set_long(
       "It is a bottle of freshly pressed grape juice.\n");
    set_soft_amount(200);
    set_alco_amount(0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
//    remove_prop(HEAP_I_IS);
}
