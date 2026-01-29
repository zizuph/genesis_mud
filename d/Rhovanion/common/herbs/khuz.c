/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("root");
 set_pname("roots");
 set_adj("humanshaped");
 add_adj("black");
 set_short("humanshaped black root");
 set_pshort("humanshaped black roots");
 set_herb_name("Khuz");
 set_unid_long("This black root is formed like a human.\n");
 set_id_long("This is the humanshaped root called Khuz. It is used by lots of races " +
	"to gain courage in combat. You know that it taste awful but can be good in " +
	"hard combats.\n");
 set_id_diff(15);
 set_find_diff(13);
 set_effect(HERB_ENHANCING,"dis",20);
}	

