/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("fungus");
 set_pname("funguses");
 set_adj("little");
 add_adj("silver");
 set_short("little silver fungus");
 set_pshort("little silver funguses");
 set_herb_name("Silfa");
 set_unid_long("This is a very small fungus that you found on the bark of a " +
  	"tree. You have never seen anything like it before but maybe it can be" +
	"worth money ? \n"); 
 set_id_long("This is the very poisonus fungus called silfa. It is very rare and " +
	"it is pretty hard to find. You know that it is used of assasins that want " +
	"to take care of their victims fast.\n");
	set_id_diff(20);
	set_find_diff(15);
	set_effect(HERB_POISONING,"herb",40);
}	

