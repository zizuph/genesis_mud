/*
 * Filename:        wstaff.c
 * Description:     A staff the mage can earn somehow
 *                  Maybe by bringing a powerful magic weapon.
 */
inherit "/std/weapon.c";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
	set_name(({ "staff", "polearm" }));
	set_pname(({ "staffs", "polearms", }));
	set_adj(({ "polished", "oak"}));
	set_short("polished oak staff");
	set_pshort("polished oak staffs");
	set_long("This stout polearm is made of oak, a hardwood of " 
             + "high durability. Polished and obviously well cared "
             + "for, this staff is quite lean despite this you "
             + "have a sense; it would take quite a lot to break.\n");

	set_default_weapon(16, 12, W_POLEARM, W_BLUDGEON, W_BOTH);

	update_prop_settings();
	set_wf(TO);

    add_prop(OBJ_I_VOLUME, 750);
	add_prop(OBJ_I_WEIGHT, 750);
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16,12) + 200);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); // We are magic!
    add_prop(MAGIC_AM_MAGIC, ({ 33, "earth" }));

    add_prop(MAGIC_AM_ID_INFO, 
                 ({"Something about this staff makes you feel certain magi is "
                        + "involved", 5,
                   ", you somehow know it comes out of The Tower of Wayreth.\n", 15,
                   "The staff got a strange sensation of divination...", 25,
                   " and certainty falls upon you as you realize power is hidden"
                        + "within the staff.\n", 30,
                   "TODO ADD SPELL DESCS", 100}) );

    add_prop(OBJ_S_WIZINFO, "ADD INFO to inform wizards about the special "
                    + "properties of the weapon. This should also contain "
                    + "where it is cloned and what order it belongs to.\n");


}




// Todo:
// Add a few spells to this staff.
