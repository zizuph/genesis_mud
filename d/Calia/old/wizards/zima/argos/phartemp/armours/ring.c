/*
** The ring of a Pharosian Priest or Priestess
**
** HISTORY
** Date       Coder    Action
** ---------- -------- -----------------------------------
** 8/27/95    Zima     Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("ring");
    set_adj("silver");
    set_short("silver ring");
    set_long(
       "It is a silver ring engraved with a dove. An inscription engraved "+
       "around it reads: Bathmos Pharos.\n");
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  50);
}
