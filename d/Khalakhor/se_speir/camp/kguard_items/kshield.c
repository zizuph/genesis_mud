/* Mortis 02.2006
 *
 * Common shield worn by city guards in Palanthas.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>

#define SHIELDADJ ({"square", "oval", "rectangular",})
#define SHIELDADJ2 ({"worn", "new", "standard","large"})
#define SHIELDNAME ({"'FIRM'","'UNWAVERING'","'UNBROKEN'","'INDOMINATABLE'"})

public void
create_armour()
{
    string shieldadj = one_of_list(SHIELDADJ);
    string shieldadj2 = one_of_list(SHIELDADJ2);
	string shieldname = one_of_list(SHIELDNAME);
	
	set_name("shield");
	set_adj(shieldadj);
	add_adj(({shieldadj2}));
	set_short(shieldadj2+" "+shieldadj+" shield");
	set_long("This is a "+shieldadj2+" "+shieldadj+" shield, with a solitary "
		+"strap keeping it close to the wielder's forearm, and a leather "
		+"handle that he or she can use to maneuver it. The background is "
		+"checkered black and white, while in the center, a silver symbol "
		+"is engraved, creating a Quaternary Celtic Knot, insignia of the "
		+"clan Baran. Inscribed inside the shield is: "+shieldname+"\n");

	set_at(A_SHIELD);

    set_ac(20 + random(2));
    set_am(({0, 0, 0}));
    
}