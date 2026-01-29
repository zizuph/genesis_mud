inherit "/std/armour";
 
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
 
#define ARMOUR_CLASS 50
 
void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");
 
    set_adj("obsidian");
 
    set_short("obsidian platemail");
    set_pshort("obsidian platemails");
    set_long("This is a piece of full plate armour. It practically "+
             "protects your body from any hit, which can be "+
             "done by living creature!\n"+
             "You see some runes on it and you are sure that "+
             "this armour is enchanted.\n");
 
 
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ 1, 1, 1 }) );
 
    add_prop(OBJ_I_WEIGHT, 8400);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}
 
