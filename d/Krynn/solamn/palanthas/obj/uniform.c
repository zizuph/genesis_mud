/* Created by Aridor, 09/06/94 
 *
 * Changed by Mortis 02.2006
 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("uniform");
    set_adj("marbled");
    add_adj("white");
    set_short("marbled white uniform");
    set_pshort("marbled white uniforms");
    set_long("This is the uniform of the chief constable of Palanthas. It "
	+ "covers the full body, legs, arms and is in one piece. The hardened "
	+ "leather of the breastplates, bracers, and greaves is marbled white "
	+ "with gray like the translucent white marble of the city and pieced "
	+ "together with soft, flexible leather for complete coverage.\n");

	set_ac(20);
	set_at(A_BODY | A_LEGS | A_ARMS);
}
