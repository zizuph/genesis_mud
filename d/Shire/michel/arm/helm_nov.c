inherit "/std/armour";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"
 
void
create_armour()
{
set_name("helmet");
set_short("novice smith helmet");
set_long("This is a brand-new helmet made by novice smith in Shire. \n"
       + "It is crafted from fine steel and decorated with some \n"
       + "golden ornament. It looks like a good protection from \n"
       + "orcish clubs. \n");
set_adj("novice");
set_ac(20);
set_at(A_HEAD);
set_am(({-5,-5,10}));
add_prop(OBJ_I_VALUE,500);
add_prop(OBJ_I_VOLUME,700);
add_prop(OBJ_I_WEIGHT,2000);
}
 
 
string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
 
 
void init_recover(string arg)
{
    init_arm_recover(arg);
}
