inherit "/std/armour";
 
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
 
#define ARMOUR_CLASS 35
 
void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");
 
    set_adj("steel");
 
    set_short("steel platemail");
    set_pshort("steel platemails");
    set_long("This is the platemail made of very good steel. "+
             "You have never seen such armour before and you "+
             "wonder which land it comes from.\n"+
             "You have strong feeling that this armour will "+
             "ideally fit your body!\n");
 
 
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 1, 1, 1 }) );
 
    add_prop(OBJ_I_WEIGHT, 8400);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}
 
