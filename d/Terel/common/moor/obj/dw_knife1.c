/*
 * Knife for tomb dwellers
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include <stdproperties.h>
#include <wa_types.h>

void create_weapon()
{
     set_name("knife");
     set_short("iron zombie knife");
     set_long("This dagger is forged of iron and looks sharp.\n");
     set_adj(({"iron", "tomb", "dweller", "zombie"}));
     set_hit(15);
     set_pen(15);

     set_wt(W_KNIFE);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
