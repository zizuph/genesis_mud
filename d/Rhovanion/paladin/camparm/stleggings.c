 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
 
int times;
 
void
create_armour()
{
 
    set_name("leggings");
    set_adj("steel");
    set_long("This is the leggings made of very good steel. "+
             "You have never seen such armour before and you "+
             "wonder which land it comes from.\n"+
             "You have strong feeling that this armour will "+
             "ideally fit your body!\n");
 
    set_ac(25);
 
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_LEGS);
}
 
 
 
