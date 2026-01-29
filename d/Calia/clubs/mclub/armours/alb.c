/* MCLUB - ceremonial alb
** - ceremonial garment only
** - obtained in rooms/shconsac.c in the cabinet (1 availabe)
** - no monetary or armour value
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
void
create_armour()
{
    set_name(({"black alb","alb"}));
    add_name(MCLUB_ALB);
    set_adj("black");
    set_short("black alb");
    set_long("It is a long vestment worn over the shoulders.\n");
    set_ac(1);
    set_at(A_NECK);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
