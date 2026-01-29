 
inherit "/std/armour";
#include "/sys/wa_types.h"
 
void
create_armour()
{
    set_name("helmet");
    set_short("steel helmet");
 
    set_adj("steel");
    set_long("This is the helmet made of very good steel. "+
             "You have never seen such armour before and you "+
             "wonder which land it comes from.\n"+
             "You have strong feeling that this armour will "+
             "ideally fit your body!\n");
 
    set_ac(25);
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_HEAD);
 
}
 
