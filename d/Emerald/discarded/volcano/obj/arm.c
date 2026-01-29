inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

string
create_armour()
{
	set_name("armour");
	set_short("leather armour");
	set_adj("heavy");
	set_long("This is a leather armour, but has a remarkable feature " +
	"It seems to have been forged with volcanic lava mixed in it, adding a bit " +
	"weight and protection to it. You wonder how someone managed " +
	"to do this.\n");
	set_ac(30);
        add_prop(OBJ_I_WEIGHT, 5000);
        add_prop(OBJ_I_VOLUME, 4320);
	add_prop(OBJ_I_VALUE, 2000);
        set_at(A_TORSO);
}
