/* golden mirror mail, for kargs of Gont */
/* Edit Ckrik August 29, 2003 - Added identify information
*/

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("plate");
    add_name("platemail");
    add_name("mail");
    set_adj("golden");
    set_short("golden platemail");
    set_long("A golden mirror platemail. Fashioned "+
        "from plate gold, this armour is as polished and bright as "+
        "a mirror. The chestplate is shaped to the pectoral "+
        "muscles. It glitters in the sun.\n");
    set_default_armour(45, A_TORSO);
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(MAGIC_I_RES_MAGIC, 10);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, 
	     "An enchanted platemail worn by Kargish leaders. " +
	     "The reflective surface resists magic spells slightly.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This armour protects its wearer from magic slightly.\n",
        10 }));
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    set_keep(1);
}
