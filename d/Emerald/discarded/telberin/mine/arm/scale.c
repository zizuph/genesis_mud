 
/* mine/arm/scale.c is cloned by mine/npc/dwarf?.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name(({"scale","scale leather","leather"}));
    add_name("armour");
    set_short("scale leather");
    set_long("Just some simple scale leather armor.\n");
    set_adj("leather");
    set_ac(7);
    set_at(A_BODY);
    set_am(({0,0,0 }));
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME,  400);
    add_prop(OBJ_I_VALUE, 150);
}
 
