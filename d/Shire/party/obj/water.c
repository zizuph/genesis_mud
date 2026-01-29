inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("water");
   set_adj(({"glass","glass of"}));
   set_short("glass of water");
   set_pshort("glasses of water");
   set_long("A refreshing glass of water.\n");
	set_soft_amount(60);
	add_prop(HEAP_I_UNIT_WEIGHT, 18);
	add_prop(HEAP_I_UNIT_VOLUME, 18);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_water");
}
