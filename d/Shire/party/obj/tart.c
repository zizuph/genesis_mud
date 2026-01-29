inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("tart");
   set_adj(({"raspberry","sticky"}));
   set_short("sticky raspberry tart");
   set_long("A sticky mash of sugared raspberries wedged between "+
	"two layers of pastry, cut into neat squares.\n");
   set_amount(75);
	add_prop(HEAP_I_UNIT_WEIGHT, 70);
        add_prop(HEAP_I_UNIT_VOLUME, 70);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_tart");
}
