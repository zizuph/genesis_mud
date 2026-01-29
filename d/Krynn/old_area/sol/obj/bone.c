/* From solace goblin camp
 * Bone which can be used as a poor club, by Teth Feb 15,96
 * modified from Aridor's newports plank
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>

void
create_weapon()
{
    set_name("bone");
    set_adj("whitened");
    add_name("club");
    add_name("femur");
    set_long("This is the huge leg bone of some beast. This femur is " +
	     "whitened with age. By the feel of it, it might be a " +
             "decent club.\n");
    set_default_weapon(10,5,W_CLUB,W_BLUDGEON,W_BOTH);
}
