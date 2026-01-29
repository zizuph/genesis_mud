/* Theobald */
/*  950124 */

inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void create_herb()
{
 set_name("fruit");
 set_pname("fruits");
 set_adj("orange");
 set_adj("round");
 set_short("orange round fruit");
 set_pshort("orange round fruits");
 set_herb_name("bella");
 set_unid_long("This is a round orange fruit that smells very nice.\n");
 set_id_long("This is a fruit that helps you on long adventures. " +
	"You are going to feel refreshed when you eat this \n "); 
 set_id_diff(12);
 set_find_diff(20);
 set_effect(HERB_HEALING,"fatigue",25);
}	

