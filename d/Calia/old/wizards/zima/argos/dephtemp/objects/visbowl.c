/*
** A ceremonial silver bowl needed to do the Vision Quest
**
** It is used to hold the blood of the lamb in the quest/rite
**
** Sitting on a pedestal in the sacristry (rooms/sacris)
** Player must be wearing the armours/visrobe, armours/vismedal
**    and have the lamb corpse (objects/lambbody) to take it.
**
** HISTORY
** Date       Coder     Action
** ---------- --------- ----------------------------------
** 1/1/95     Zima      Created
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define HOME_ROOM ROOM_DIR+"sacris"
#define OBJ_NUM 2
#include "../retrnobj.h"
 
void
create_object()
{
    set_name(({"silver bowl",VDQ_BOWL,"bowl"}));
    set_adj("silver");
    set_adj("ceremonial");
    set_short("silver bowl");
    set_long("@@exa_me");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(VDQ_BOWL_PROP,0);
}
 
string exa_me() {
   if (this_object()->query_prop(VDQ_BOWL_PROP))
      return
      "A silver bowl intricately engraved with daggers, used "+
      "for ceremonial purposes. It is filled with blood!\n";
   else
      return
      "A silver bowl intricately engraved with daggers, used "+
      "for ceremonial purposes. It is empty, but stained with "+
      "blood on the inside.\n";
}
