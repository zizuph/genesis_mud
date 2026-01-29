 
/* mine/arm/plate.c is cloned by mine/npc/dewarlord.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
string
create_armour()
{
    set_name("platemail");
    set_short("dewar platemail");
    add_name("armour");
    set_long("This platemail is not of he best quality but has the tell-tale" +
             " dwarven marks on it.\n");
    set_adj("dewar");
 
    set_ac(24);
    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_WEIGHT, 2452);
    add_prop(OBJ_I_VOLUME, 3039);
    set_at(A_TORSO);
    set_am(({ 2,      1,      -3 }));
}
