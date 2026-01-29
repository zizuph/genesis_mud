/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("nut");
 set_pname("nuts");
 set_adj("hard");
 add_adj("brown");
 set_short("hard brown nut");
 set_pshort("hard brown nuts");
 set_herb_name("acorn");
 set_unid_long("This is just a little brown nut.\n");
 set_id_long("You can see directly that this is a little nut from an oak. " +
	"It is very hard.\n ");
 set_id_diff(6);
 set_find_diff(5);
}	

