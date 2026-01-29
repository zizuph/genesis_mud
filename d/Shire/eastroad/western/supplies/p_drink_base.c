/* Drink base file.--Raymundo, dec 2018
 * Drink messages are logged in 
 * 
 */
#include <stdproperties.h>
inherit "/std/drink";
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/sys/defs.h"


void
create_p_drink()
{

}

void
create_drink()
{
	add_name("drink");
	
	set_adj(this_player()->query_real_name());
	set_adj(this_player()->query_real_name() + "'s");
	set_adj(this_player()->query_real_name() + "s");
	
	create_p_drink();
}
 


