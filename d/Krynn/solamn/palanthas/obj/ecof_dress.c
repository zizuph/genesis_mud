/* 
 * Created by Mortis 09.2005
 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("dress");
    set_adj("long");
	set_adj("collared");
    set_short("long collared dress");
    set_long("This dress has a pattern of grey and brown sections from its "
	+ "buttoned up chest and black-ribboned collar, to its hem which is "
	+ "designed to hang an inch from the flooor.  It is tight fitting for "
	+ "a trim, average woman of average height around the waist and "
	+ "collar.\n");
    set_ac(1);
    set_at(A_CHEST | A_LEGS | A_ARMS);
}
