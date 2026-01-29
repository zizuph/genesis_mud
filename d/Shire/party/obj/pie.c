inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("pie");
   set_adj(({"piping-hot","tasty"}));
   set_short("piping-hot apple pie");
   set_long("A whole, round, piping-hot apple pie, sprinkled "+
	"with cinnamon and glazed to a honey-gold colour.\n");
   set_amount(270);
	add_prop(HEAP_I_UNIT_WEIGHT, 180);
        add_prop(HEAP_I_UNIT_VOLUME, 220);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_applepie");
}
