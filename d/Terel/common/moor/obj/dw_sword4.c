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
     set_short("shiny tempered sword");
     set_long("The shiny sword is forged of a tempered alloy and "+
         "looks very sharp. It appears to have been "+
         "made by the tomb dwellers.\n");
     set_adj("tempered");
     add_adj(({"shiny", "alloy", "metal", "tomb", "dweller"}));
     set_hit(35);
     set_pen(35);
     add_prop(OBJ_I_WEIGHT, 8000);
     add_prop(OBJ_I_VOLUME, 9000);

     set_wt(W_SWORD);
     set_dt(W_SLASH | W_IMPALE);

     set_hands(W_ANYH);
}
