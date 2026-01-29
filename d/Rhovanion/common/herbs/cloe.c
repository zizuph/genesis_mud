/* Theobald */ 
/*  950124 */

inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void create_herb()
{
 set_name("flower");
 set_pname("flowers");
 set_adj("blue");
 add_adj("yellow");
 set_short("blue and yellow flower");
 set_pshort("blue and yellow flowers");
 set_herb_name("cloe");
 set_unid_long("This flower is blue and yellow with a little green stalk.\n");
 set_id_long("What a little flower is your first thought, because this flower " +
	"is really small. Maybe thats why it is so hard to find. The name " +
 	"(cloe) comes from the first person that discovered it. A little " +
	"girl that got lost in the wood was so charmed of it that she couldnt " +
	"leave it nor could she rip it of the ground so she fell asleep staring " +
	"at it.\n");
 set_id_diff(23);
 set_find_diff(27);
}	



