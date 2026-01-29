inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("milk");
   set_adj(({"cup","cup of","creamy"}));
   set_short("cup of milk");
   set_pshort("cups of milk");
   set_long("A delicate pottery cup filled with fresh "+
	"creamy shire milk.\n");
	set_soft_amount(50);
	add_prop(HEAP_I_UNIT_WEIGHT, 16);
	add_prop(HEAP_I_UNIT_VOLUME, 16);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_milk");
}
