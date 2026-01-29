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
	set_long("   A dress, fashioned out of soft, tanned doe skin. " +
	"it is embroidered with pictures of forest animals and a few beads to make " +
	"the dress pretty.\n\n");
   set_at(A_BODY);
	set_ac(5);
}
