/*  common staff of argos
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
** Maniac         14/3/99  plurals updated
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>


void
create_weapon()
{
    set_name("staff");
    set_pname("staves"); 
    add_pname("staffs"); 
    set_adj("hardwood");
    set_short("hardwood staff");
    set_pshort("hardwood staves"); 
    set_long("It is a tall staff made of polished hardwood, probably "+
             "oak.\n");
    set_hit(15);
    set_pen(13);
 
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1200);
}
