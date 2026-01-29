inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("robes");
    add_name("robe");
    set_pname("sets of robes");
    set_short("tattered, heavy robes");
    add_adj(({"tattered", "heavy"}));
    set_ac(10);
    set_at(A_ROBE);
    set_condition(3);
    set_long("These robes must have once been a simple, yet clean and "+
	"protecting, piece of clothing. Now they still hold together "+
	"due to the heaviness of the material, but they are definately "+
	"in poor shape.\n");
}
