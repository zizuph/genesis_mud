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
     set_short("steel zombie knife");
     set_long("This knife is forged of steel and looks sharp.\n");
     set_adj(({"steel", "tomb", "dweller", "metal", "zombie" }));

     set_hit(20);
     set_pen(20);

     set_wt(W_KNIFE);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
