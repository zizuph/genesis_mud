/*
 * Based on Mortricia's plain sword
 */
#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include <stdproperties.h>
#include <wa_types.h>

void create_weapon()
{
     set_name("sword");
     set_short("iron sword");
     set_long("The sword is forged of iron and looks sharp enough "+
        "especially at the pointy end.\n");
     set_adj(({"iron", "tomb", "dweller"}));
     set_hit(20);
     set_pen(20);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
