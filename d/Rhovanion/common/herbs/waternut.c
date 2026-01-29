/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("chestnut");
 set_pname("chestnuts");
 set_adj("wet");
 add_adj("slimy");
 set_short("wet slimy chestnut");
 set_pshort("wet slimy chestnuts");
 set_herb_name("waterchestnut");
 set_unid_long("This little nut looks like an ordinary chestnut that is wet.\n");
 set_id_long("You recognize this as an ordinary waterchestnut. You know that it " +
	"a fine and sweet taste. This nut is used by travellers to eat insted " +
	"of dinners.\n");
 set_id_diff(20);
 set_find_diff(25);
 set_amount(50);
}	

