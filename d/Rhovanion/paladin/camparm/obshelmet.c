 
inherit "/std/armour";
#include "/sys/wa_types.h"
 
void
create_armour()
{
    set_name("helmet");
    set_short("obsidian helmet");
 
    set_adj("obsidian");
    set_long("This is a piece of full plate armour. It practically "+
             "protects your body from any hit, which can be "+
             "done by living creature!\n"+
             "You see some runes on it and you are sure that "+
             "this armour is enchanted.\n");
    set_ac(45);
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_HEAD);
 
}
 
