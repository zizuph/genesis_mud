 
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
 
int shield_ac;
 
void
create_armour()
{
    set_name("spider_shield");
    set_adj("magic");
    set_no_show();
 
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}
 
remove_object()
{
TP->remove_arm(this_object());
::remove_object();
return 1;
}
 
int power(int ac)
{
    shield_ac=ac;
}
 
int query_ac(int hid)
{
    return shield_ac;
}
 
int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}
 
