/*  Sword of Priests of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           2/03/94  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"silver sword","sword"}));
    set_adj("silver");
    set_short("silver sword");
    set_long("A rune-covered silver sword engraved with a raven on the hilt.\n");
 
    set_hit(40);
    set_pen(40);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}
