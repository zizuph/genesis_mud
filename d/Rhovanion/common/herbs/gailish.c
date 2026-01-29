/* Theobald */
/*  950124 */

inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void create_herb()
{
 set_name("root");
 set_pname("roots");
 set_adj("white");
 set_short("white root");
 set_pshort("white roots");
 set_herb_name("Gailish");
 set_unid_long("You can see an white root.\n");
 set_id_long("This is an medium sized root of the name Gailish. " +
	"You know that this root is not supposed to be eaten.\n "); 
 set_id_diff(9);
 set_find_diff(17);
}	

