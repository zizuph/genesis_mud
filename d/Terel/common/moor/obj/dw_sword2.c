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
     set_short("steel sword");
     set_long("The sword is forged of steel and looks like it has "+
         "been well-sharpened.\n");
     set_adj(({"steel", "tomb", "dweller", "metal" }));

     set_hit(25);
     set_pen(25);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
