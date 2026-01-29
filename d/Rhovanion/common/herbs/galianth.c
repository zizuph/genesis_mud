/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/lib/herb_types.h"
void create_herb()
{
 set_name("flower");
 set_pname("flowers");
 set_adj("little");
 add_adj("pink");
 set_short("little pink flower");
 set_pshort("little pink flowers");
 set_herb_name("Galianthela");
 set_unid_long("This flower is very beutiful but you cant understand what\n" +
	"to do with it more then take it home to your mother\n");
 set_id_long("This tiny flower is one of the most beutiful flowers you have\n" +
	"seen. In the same moment when you are going to pick it up you remember\n" +
	"what you have learned. Take a real deep breath from this flower and you\n" +
        "are DEAD !!! .\n");
 set_id_diff(50);
 set_effect(HERB_POISONING,"hp",1000);
}	

