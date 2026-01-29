inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("brandy");
   set_adj(({"glass","glass of"}));
   set_short("glass of Brandywine brandy");
   set_pshort("glasses of brandy");
   set_long("A very large sniffer of the Shire's best brandy, "+
	"more like a fishbowl of firewater.\n");
	set_soft_amount(80);
	set_alco_amount(35);
	add_prop(HEAP_I_UNIT_WEIGHT, 20);
	add_prop(HEAP_I_UNIT_VOLUME, 20);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_brandy");
}
