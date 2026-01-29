/* Antique knife. Used for kroad knife quest. Geraden March 1997

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
	set_name("knife");
	set_pname("knives");
	set_short("antique knife");
	set_pshort("antique knives");
        add_name("_jonah_knife");
	set_long("The knife is very old, perhaps hundreds of years. The "+
		"blade is small but very sharp. The hilt is decorated "+
		"with carvings and has an inscription which reads 'For "+
		"Jonas' on it.\n");
	set_adj("antique");
	set_hit(5);
	set_pen(5);
	set_wt(W_KNIFE);
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_ANYH);	
}
