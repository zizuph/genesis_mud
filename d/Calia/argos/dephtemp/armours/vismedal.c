/*  The Medallion of Dephonia
**
**  This medallion must be worn to do many things in the Vision Quest
**  Laying on a pedestal in the Sacristry (rooms/sacris)
**  Player must be wearing the Vision quest robe (armours/visrobe)
**     to take this
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95   Created
**
**/
inherit "std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define HOME_ROOM ROOM_DIR+"sacris.c"
#define OBJ_NUM 0
#include "../retrnobj.h"
 
void
create_armour()
{
    set_name(({"gold medallion","medallion",VDQ_MEDAL}));
    set_adj("gold");
    set_short("gold medallion");
    set_long(break_string(
       "It is an ancient gold medallion on a gold link chain. "+
       "There is the image of a raven encircled by twelve stars "+
       "crafted on the face.\n",70));
 
    set_ac(1);
    set_at(A_NECK);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_M_NO_SELL, 1);
}
