inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
   set_name("ale");
   set_adj(({"pint","pint of","dark"}));
   set_short("pint of dark ale");
   set_pshort("pints of ale");
   set_long("A tall pint mug filled with a dark-brown ale from "+
	"West Farthing, topped with a creamy yellow head.\n");
	set_soft_amount(160);
	set_alco_amount(14);
	add_prop(HEAP_I_UNIT_WEIGHT, 25);
	add_prop(HEAP_I_UNIT_VOLUME, 25);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_ale");
}
