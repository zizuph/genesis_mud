 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
 
int times;
 
void
create_armour()
{
 
    set_name("shield");
    set_adj("huge");
    set_adj("steel");
    set_long("Huge black steel shield.\n");
 
    set_ac(27);
 
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_SHIELD);
}
 
 
 
