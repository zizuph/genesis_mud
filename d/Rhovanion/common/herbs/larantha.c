/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("berry");
 set_pname("berries");
 set_adj("small");
 add_adj("sticky");
 set_short("small green sticky berry");
 set_pshort("small green sticky berries");
 set_herb_name("Laranthas");
 set_unid_long("This is a litle green berry and you cant understand what it " +
	"can be. You must have been asleep on your herbalism lessons.\n");
 set_id_long("Directly when you saw this berry you knew that you had found one " +
	"of the very rare laranthas berries. You can remember from the herbalism " +
	"lessons that this berry can make you stronger for a little while.\n");
 set_id_diff(20);
 set_effect(HERB_ENHANCING,"str",10);
}	

