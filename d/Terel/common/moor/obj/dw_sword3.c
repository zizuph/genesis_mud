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
     set_short("alloy sword");
     set_long("The sword is forged of an unfamiliar alloy " +
        "and looks very sharp. It appears to have been "+
        "made by the tomb dwellers.\n");
     set_adj(({"alloy", "metal", "tomb", "dweller" }));

     set_hit(30);
     set_pen(30);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
