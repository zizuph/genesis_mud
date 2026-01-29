inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_armour()

{
	set_name("shirt");
	set_adj("bright");
	set_short("shirt");
	set_long("  A brightly coloured multi-hued shirt. It is handwoven " +
	"by one of the members of the tribe. Despite its simplicity, it " +
	"is very attractive.\n\n");
		set_at(A_TORSO);
	set_ac(5);
}
