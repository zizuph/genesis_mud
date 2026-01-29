/* Standard helmet for the guards in the jail of Tyr */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
        ::create_armour();
	set_name("helmet");
	set_short("ribbed scale helmet");
	set_long("This is a standard helmet for the guards in the jail of "
		+"Tyr. In the front just above and between the eyes you can "
		+"see the mark that shows you that the helmet is a property "
		+"of the jail in Tyr. The helmet is constructed of plates of "
		+"chitin attached to rib-bones. The helmet isn't very "
		+"beautiful but it fulfills its purpose, to protect the "
		+"head.\n");

	set_adj("scale");
	add_adj("ribbed");

	set_ac(30);
        set_am(({1,1,-2}));
	set_at(A_HEAD);

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 800);
}
