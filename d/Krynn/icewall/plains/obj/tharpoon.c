/* Created by Macker 10/23/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("harpoon");
    set_adj("thanoi");
    add_adj("light");
    set_short("light thanoi harpoon");
    set_pshort("light thanoi harpoons");
    set_long("This harpoon has a thick shaft " +
	     "and a barbed pointy tip that makes you cringe. " +
	     "You can't be certain what it was made to harpoon, " +
	     "but let's just hope it's not you!\n");
    set_default_weapon(18, 27, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
}
