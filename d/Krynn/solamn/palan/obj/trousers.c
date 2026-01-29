/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("trousers");
    set_short("pair of trousers");
    set_pshort("pairs of trousers");
    set_long("This is a pair of trousers made from fine wool. They are " +
	     "thick and protective.\n");
    set_ac(8);
    set_at(A_LEGS);
}
