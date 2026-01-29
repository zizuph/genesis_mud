/* Theobald */
/*  950124 */

inherit"/std/herb";

#include "/sys/stdproperties.h"
#include "/d/Gondor/elessar/open/herb_types.h"
void create_herb()
{
 set_name("leaf");
 set_pname("leafs");
 set_adj("big");
 add_adj("green");
 set_short("big green leaf");
 set_pshort("big green leafs");
 set_herb_name("Khazad");
 set_unid_long("You can see that this huge green leaf is very thin " +
	"but you dont know if it can be used for any good.\n");
 set_id_long("You can recognize this leaf as a Khazad leaf a very " +
	"thin leaf and big. You know that if you get a wound you " +
	"can eat this to regain your health.\n");
	set_id_diff(20);
	set_effect(HERB_HEALING,"hp",20);
        set_find_diff(10);
}	

