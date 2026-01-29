inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("tiara");
    set_short("dazzling coral tiara");
    add_adj(({"dazzling", "coral"}));
    set_long("This dazzling piece of jewelry is made of a thin, "+
	"but beautifully polished piece of deep amber coral. It "+
	"doesn't seem to provide much protection, if any, but "+
	"it's worth as an ornament is justified"+
	".\n");
    add_prop(OBJ_I_VALUE, 600);
    set_ac(2);
    set_at(A_HEAD);
}
