inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("mutton");
   set_adj(({"roast","leg", "juicy"}));
   set_short("juicy roast leg of mutton");
   set_long("A tender, juicy roast leg of mutton "+
	"cooked to perfection. It looks like it "+
	"will melt in your mouth.\n");
   set_amount(200);
	add_prop(HEAP_I_UNIT_WEIGHT, 250);
        add_prop(HEAP_I_UNIT_VOLUME, 280);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_mutton");
}
