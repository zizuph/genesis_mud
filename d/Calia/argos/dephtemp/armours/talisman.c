/*  The Talisman of Dephonia
**
**  According to legend it gives a dephonian priest/ess the power to
**  poison food, but this object is just for decoration
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
 
void
create_armour()
{
    set_name("talisman");
    set_adj("silver");
   set_short("silver talisman");
    set_long(break_string(
       "It is silver talisman on a chain made in the form of "+
       "a snake twisted about a wreath of hemlock leaves.\n",70));
 
    set_ac(1);
    set_at(A_NECK);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
}
