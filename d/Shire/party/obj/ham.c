inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("ham");
   set_adj(({"honey","tasty"}));
   set_short("tasty honey-glazed ham");
   set_long("A succulent piece of ham that has been glazed "+
      "over with a coating of honey.\n");
   set_amount(50);
	add_prop(HEAP_I_UNIT_WEIGHT, 80);
        add_prop(HEAP_I_UNIT_VOLUME, 80);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_ham");
}
