inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("shortcake");
   set_adj(({"strawberry","cream-topped"}));
   set_short("cream-topped strawberry shortcake");
   set_long("A three-inch diameter shortcake, buried under "+
	"a mound of fresh strawberries and whipped cream.\n");
   set_amount(150);
	add_prop(HEAP_I_UNIT_WEIGHT, 110);
        add_prop(HEAP_I_UNIT_VOLUME, 130);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_shortcake");
}
