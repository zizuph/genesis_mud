/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("straw");
 set_pname("straws");
 set_adj("green");
 set_short("green straw");
 set_pshort("green straws");
 set_herb_name("myntha");
 set_unid_long("This looks like an ordinary green straw but you " +
	"can feel the strong smell of mint.\n"); 
 set_id_long("This is a little straw that you recognize on the smell " +
	"of mint. It is called myntha and some people use it in their " +
	"tea. It is refreshing to smell on and if you got the flue " +
	"you should drink some tea made of this straw.\n");
 	set_id_diff(15);
	set_find_diff(8);
	set_effect(HERB_HEALING,"fatigue",20);
}	

