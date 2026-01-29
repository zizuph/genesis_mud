/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"

void create_herb()
{
 set_name("flower");
 set_pname("flowers");
 set_adj("good-smelling");
 add_adj("violet");
 set_short("good-smelling violet flower");
 set_pshort("good-smelling violet flowers");
 set_herb_name("porin");
 set_unid_long("You cant recognize this good-smelling flower " +
	"but it is very beutiful.\n"); 
 set_id_long("This flower is a beutiful example of the flower " +
	"called porin. You know that it doesnt give any effect " +
	"but it smells very good.\n");
	set_id_diff(10);
	set_find_diff(5);
}	

