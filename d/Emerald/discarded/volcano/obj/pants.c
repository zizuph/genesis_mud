inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
create_armour()

{
	set_name("pants");
	set_pname("pants");
	set_adj("warm");
	set_short("pants");
	set_pshort("pants");
	set_long("A set of warm tanned pants that appear to be made " +
	"from the hide of an animal.\n\n");
	set_at(A_LEGS);
	set_ac(5);
}
