/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("uniform");
    set_adj("bright");
    add_adj("red and green");
    add_adj("red");
    add_adj("green");
    set_short("bright red and green uniform");
    set_pshort("bright red and green uniforms");
    set_long("This is the uniform of the city guards of Palanthas. It " +
	     "covers the full body, legs, arms and is in one piece. There " +
	     "are red vertical stripes down the front and back and also " +
	     "along the seams. You notice it is inlaid with pieces of metal " +
	     "between layers of cotton and leather, giving good " +
	     "protection.\n");
    set_ac(20);
    set_at(A_BODY | A_LEGS | A_ARMS);
}
