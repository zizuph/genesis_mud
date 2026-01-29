inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("gloves");
    set_short("supple blue leather gloves");
    add_adj(({"supple", "leather", "blue"}));
    set_long("These gloves seem to be fairly gaudy armour. They seem to "+
	"be double-layered with silk on the inside and supple leather on "+
	"the outside. They are dyed a very bright blue.\n");
    set_ac(9);
    set_am( ({-1,0,1}) );
    set_at(A_R_ARM);
    set_at(A_L_ARM);
}
