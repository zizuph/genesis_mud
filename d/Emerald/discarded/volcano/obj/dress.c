inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_armour()

{
   set_name("dress");
	set_adj("long");
	add_adj("colourful");
	set_short("dress");
	set_long("A dress, fashioned out of doe skin. " +
	"It is adorned by embroidred pictures depicting aspects of the tribe's life, and colourful beads " +
	"to make the simple dress look stunning.\n\n");
   set_at(A_BODY);
	set_ac(5);
}
