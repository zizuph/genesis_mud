inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("beer");
   set_adj(({"mug","frosty","cold"}));
   set_short("mug of beer");
   set_pshort("mugs of beer");
   set_long("A short glass mug filled to the top "+
	"with frosty, cold beer.\n");
	set_soft_amount(45);
	set_alco_amount(8);
	add_prop(HEAP_I_UNIT_WEIGHT, 10);
	add_prop(HEAP_I_UNIT_VOLUME, 10);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_beer");
}
