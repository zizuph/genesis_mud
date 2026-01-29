/* ARGOSIAN OLIVES
**
** Date     Coder     Action
** -------- --------- -------------------------
** 12/93    Zima      Created
** 8/25/95  Zima      Cleaned up/standardized argosian olives
**                    May be taken to press in argos/metro/rooms/press
**                    and made into olive oil.
*/
inherit "/std/food";
#include <stdproperties.h>
#include "defs.h"
 
create_food() {
    set_name(({"handful of olives","olives"}));
    set_adj(({"green","argosian"}));
    add_name(ARGOS_OLIVES);
    set_short("handful of olives");
    set_pshort("handfuls of olives");
    set_long("It is a handful of green argosian olives.\n");
    set_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
