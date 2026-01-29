 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
 
int times;
 
void
create_armour()
{
 
    set_name("leggings");
    set_adj("obsidian");
    set_long("This is a piece of full plate armour. It practically "+
             "protects your body from any hit, which can be "+
             "done by living creature!\n"+
             "You see some runes on it and you are sure that "+
             "this armour is enchanted.\n");
 
    set_ac(40);
 
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_LEGS);
}
