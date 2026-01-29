/*
** common sword of Argos
**
** HISTORY
** Date      Coder       Action
** --------- ----------- -----------------------------------
** 1/30/95   Zima        Created
**
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name("sword");
    set_adj(({"steel","argosian","common"}));
    set_short("common steel sword");
    set_long("It is a common inornate sword made of steel. It has a "+
             "small winged horse engraved on the hilt.\n");
 
    set_hit(18); set_pen(20);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 1600);
}
