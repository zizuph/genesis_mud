/* Theobald */
/*  950124 */

inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"

void create_herb()
{
 set_name("plant");
 set_pname("plants");
 set_adj("sticky");
 set_short("sticky plant");
 set_pshort("sticky plants");
 set_herb_name("Gadiem");
 set_unid_long("This is a green sticky plant.\n");
 set_id_long("You know that if you are going to a warm place " +
	"this plant can be a fine choice to bring with you. \n "); 
 set_id_diff(12);
 set_find_diff(20);
 set_effect(HERB_ENHANCING,"FIRE",15);
}	

