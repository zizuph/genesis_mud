/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/lib/herb_types.h"
void create_herb()
{
 set_name("flower");
 set_pname("flowers");
 set_adj("slimy");
 add_adj("yellow");
 set_short("slimy yellow flower");
 set_pshort("slimy yellow flowers");
 set_herb_name("Maroea");
 set_unid_long("This is a very unpleasant flower you think it is disguisting.\n" +
	"so you dont want to have it. You almost feel like you want to crush\n" +
 	"it under your heel. \n");
 set_id_long("This flower isnt so very nice looking but you know that this is one\n" +
	"the best to eat if you have been poisoned. This flower can cure all poisons\n");
 set_id_diff(50);
 set_effect(HERB_CURING,"all",100);
}	

