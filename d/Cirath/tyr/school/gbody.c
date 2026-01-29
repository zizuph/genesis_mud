/*This is the standard armour for the guards in the jail of Tyr. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_armour()
{
	set_name("chainmail");
    set_short("light glossy chainmail");
   set_long("This suit of chainmail looks to have been made "
	+"from carefully crafted links of both bone and chitin "
	+"so that it is almost one solid piece.  It has been "
	+"coated with some clear fluid to further join "
	+"the mail together and make it strong.\n");
    set_adj("light");
    add_adj("glossy");


	set_ac(35);
	set_at(A_BODY);

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 3000);
}
