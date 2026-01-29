inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_armour()

{
	set_name("skirt");
	set_pname("skirts");
	set_adj("warm");
	set_short("skirt");
	set_long("A simple skirt make out of lightly tanned deer skin " +
	"and made by one of the local women.\n\n");
	set_at(A_LEGS);
	set_ac(5);
}
