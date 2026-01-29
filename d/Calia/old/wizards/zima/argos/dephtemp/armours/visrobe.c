/*  Robe of the Hierophant, must be worn to do the Vision Quest
**  found in her chambers (room/hiercham)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95   Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
#define HOME_ROOM ROOM_DIR+"hiercham.c"
#define OBJ_NUM 0
#include "../retrnobj.h"
 
void
create_armour()
{
    set_name(({"black silk robe","robe",VDQ_ROBE}));
    set_adj("black");
    set_adj("silk");
    set_short("black silk robe");
    set_long(break_string(
       "It is a long black robe made of fine silk. There is a raven "+
       "embroidered on the front in silver thread, encircled by "+
       "twelve stars.\n",70));
 
    set_ac(1);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_SELL, 1);
}
