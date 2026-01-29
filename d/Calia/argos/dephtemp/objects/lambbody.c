/*
** The bloody corpse of a lamb
**
** In the Vision of Dephonia Quest, the questor must kill a lamb
** in nwterr/rooms/pastfold. This lamb can not be attacked unless
** the questor wears the robe and medallion, and is wielding the
** ceremonial dagger from the sacristry (room/sacris). This corpse
** is then needed for the rest of the rite/quest.
** SEE: dephtemp/rooms/sacris and sanctum
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
 
void
create_object()
{
    set_name(({"bloody corpse of a lamb","lamb","corpse",
               "bloody corpse","lamb corpse",VDQ_LAMBCORPSE}));
    set_short("bloody corpse of a lamb");
    set_long("It is the corpse of a recently slain lamb, the blood "+
             "from its slit throat soaking its snow white fleece.\n");
 
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 0);
}
