inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("wine");
   set_adj(({"fine","white","glass"}));
   set_short("fine white wine");
   set_long("A chilled tall glass of fine Tookland "+
	"white wine.\n");
	set_soft_amount(80);
	set_alco_amount(20);
	add_prop(HEAP_I_UNIT_WEIGHT, 18);
	add_prop(HEAP_I_UNIT_VOLUME, 18);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_wine");
}
