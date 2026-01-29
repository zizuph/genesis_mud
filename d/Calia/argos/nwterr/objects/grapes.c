/* ARGOSIAN GRAPES
**
** Date     Coder     Action
** -------- --------- -------------------------
** 12/93    Zima      Created
** 8/25/95  Zima      Cleaned up/standardized argosian grapes
**                    May be taken to press in argos/metro/rooms/press
**                    and made into grape juice.
*/
inherit "/std/food";
#include <stdproperties.h>
#include "defs.h"
 
create_food() {
    set_name(({"bunch of red grapes","bunch of grapes","bunch","grapes"}));
    add_name(ARGOS_GRAPES);
    set_long("A bunch of red grapes.  They look delicious.\n");
    set_amount(200);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
