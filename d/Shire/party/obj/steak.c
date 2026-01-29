inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
   set_name("steak");
   set_adj(({"sizzling","rump","juicy"}));
   set_short("sizzling slab of rump steak");
   set_long("A hefty slab of rump steak, nicely "+
	"seared on the outside, tender and juicy "+
	"on the inside.\n");
   set_amount(350);
	add_prop(HEAP_I_UNIT_WEIGHT, 400);
        add_prop(HEAP_I_UNIT_VOLUME, 450);
   
   add_prop(HEAP_S_UNIQUE_ID,"_party_steak");
}
