/*  Ceremonial Dagger of Dephonia
**
**  This dagger must be wielded to kill the Innocent One (protected
**       lamb in nwterr/rooms/pastfold) as part of the Vision Quest
**  Laying on a pedestal in the Sacristry (rooms/sacris)
**  Player must be wearing the Vision quest robe (armours/visrobe)
**     and the Medallion of Dephonia (armours/vismedal) to take this
**     (also must have invisible blessing object (objects/blessobj)
**     received in the chapel (rooms/chapel))
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95   Created
** Zima           9/15/96  Added mystic prop, so mystics can do the quest.
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"
 
#define HOME_ROOM ROOM_DIR+"sacris.c"
#define OBJ_NUM 1
#include "../retrnobj.h"
 
void
create_weapon()
{
   set_name(({"ceremonial dagger","dagger",VDQ_DAGGER}));
    set_adj("silver");
    set_adj("ceremonial");
    set_short("ceremonial dagger");
    set_long(break_string(
       "It is a silver dagger, encrusted with a large ruby "+
       "on the hilt. Its polished, dull edge makes you think that "+
       "it must be used only for ceremonial purposes. You feel "+
       "an intense evil emanating from it.\n",70));
 
    set_hit(1);
    set_pen(1);
 
    set_hands(W_RIGHT);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop("mystic_weapon",1);
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_M_NO_SELL, 1);
}
